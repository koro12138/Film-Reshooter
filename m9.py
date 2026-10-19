"""M9 networks, recovered Frame protocol, scene LUT and original ARM post stages."""
from pathlib import Path
from functools import lru_cache
import hashlib
import json
import os
import sys
import time
import numpy as np
from PIL import Image
from engine import ROOT, Cancelled

EXPERIMENTS = [
    {'id':23,'name':'M9 完整影调 · High','model':'high'},
    {'id':24,'name':'M9 完整影调 · Low','model':'low'},
    {'id':25,'name':'M3 · 银盐黑白','model':'m3'},
    {'id':26,'name':'M9 · 自动模型','model':'auto'},
]
MODEL_HASHES = {
    'high':'61eedf9d72141c0f5262a2b2d7791ea27d36b77cfb63a8312b007e447b14da73',
    'low':'89f7e4e515467a6f47c9d74538a08d25ed7e148474fca2e3713db5e9259cf406',
    'colorfix':'381e0c48c241b3a1eaf09843ab9cb43610a96eae7708c0316b17a8661620b74f',
    'colorfix_b2':'d67ba56b0b42c738705f4730fc61721a6054fc2340430d0576a5e2fe5e30b207',
    'colorfix_b4':'d67ba56b0b42c738705f4730fc61721a6054fc2340430d0576a5e2fe5e30b207',
}


def reflection101(coords, length):
    if length<=1:
        return np.zeros_like(coords)
    period = 2*(length-1)
    values = np.mod(coords,period)
    return np.where(values<length,values,period-values)


def normalized(rgb):
    return (rgb.astype(np.float32)-np.float32(128))/np.float32(127.5)


def decoded(tensor):
    if not np.isfinite(tensor).all():
        raise RuntimeError('M9 网络输出出现非有限值')
    return np.rint(np.clip(tensor*np.float32(127.5)+np.float32(128),0,255)).astype(np.uint8)


class FrameProtocol:
    """4096x3072 reflection frame; 4x downsample; 48/16 pixel network halos."""
    def __init__(self, rgb):
        if rgb.dtype!=np.uint8 or rgb.ndim!=3 or rgb.shape[2]!=3:
            raise ValueError('M9 frame expects uint8 RGB')
        self.height,self.width = rgb.shape[:2]
        if not (1<=self.width<=4096 and 1<=self.height<=3072):
            raise ValueError('M9 工作图范围为 4096×3072')
        self.left,self.top = (4096-self.width)//2,(3072-self.height)//2
        xs = reflection101(np.arange(4096,dtype=np.int32)-self.left,self.width)
        ys = reflection101(np.arange(3072,dtype=np.int32)-self.top,self.height)
        self.tile_library=None
        self.tile_fallback=''
        if os.environ.get('CAMERALOOK_M9_NUMPY_TILES')!='1':
            try:
                from desktop_m9_tiles import library
                self.tile_library=library()
            except (OSError,AttributeError) as exc:self.tile_fallback=str(exc)
        self.xs=np.ascontiguousarray(xs.astype(np.int32))
        self.ys=np.ascontiguousarray(ys.astype(np.int32))
        self.original=self.frame(np.ascontiguousarray(rgb))
        self.reduced = None
        self.styled = None
        self.output = np.zeros_like(self.original)

    def frame(self,rgb):
        """Reflection-101 canvas: native row gather, NumPy fallback."""
        source=np.ascontiguousarray(rgb)
        if self.tile_library:
            out=np.empty((3072,4096,3),np.uint8)
            if self.tile_library.cl_m9_frame(source.ctypes.data,source.shape[1],source.shape[0],
                                             out.ctypes.data,self.xs.ctypes.data,self.ys.ctypes.data):
                return out
        return np.ascontiguousarray(source[self.ys[:,None],self.xs[None,:]])

    def prepare(self):
        if self.tile_library:
            reduced=np.empty((768,1024,3),np.uint8)
            if self.tile_library.cl_m9_reduce(self.original.ctypes.data,reduced.ctypes.data):
                self.reduced=reduced
                return reduced
        self.reduced = np.rint(self.original.reshape(768,4,1024,4,3).sum(axis=(1,3),dtype=np.uint32).astype(np.float32)/16).astype(np.uint8)
        return self.reduced

    def style_input(self,out=None):
        # Unlike the outer frame's reflect101, the style halo repeats the edge.
        source = np.pad(self.reduced,((48,48),(48,48),(0,0)),mode='symmetric')
        tensor = np.empty((1,4,864,1120),np.float32) if out is None else out
        if tensor.shape!=(1,4,864,1120) or tensor.dtype!=np.float32 or not tensor.flags.c_contiguous or not tensor.flags.writeable:
            raise ValueError('M9 style buffer shape/layout')
        tensor[0,3].fill(np.float32(-128)/np.float32(127.5))
        np.subtract(source.transpose(2,0,1),np.float32(128),out=tensor[0,:3])
        np.divide(tensor[0,:3],np.float32(127.5),out=tensor[0,:3])
        return tensor

    def style_output(self,tensor):
        if tensor.shape != (1,3,864,1120):
            raise ValueError(f'M9 style 输出尺寸错误：{tensor.shape}')
        self.styled = np.ascontiguousarray(decoded(tensor[0,:,48:816,48:1072]).transpose(1,2,0))

    def visible_tiles(self):
        return [y*8+x for y in range(self.top//512,(self.top+self.height-1)//512+1)
                for x in range(self.left//512,(self.left+self.width-1)//512+1)]

    def tile_input(self,index,out=None):
        if not 0<=index<48:raise ValueError('M9 tile index')
        if out is None:out=np.empty((1,6,544,544),np.float32)
        if out.shape!=(1,6,544,544) or out.dtype!=np.float32 or not out.flags.c_contiguous or not out.flags.writeable:
            raise ValueError('M9 tile buffer shape/layout')
        if self.styled is None:raise ValueError('M9 style output is not ready')
        if self.tile_library:
            if not self.tile_library.cl_m9_pack(self.original.ctypes.data,self.styled.ctypes.data,index,out.ctypes.data):
                raise RuntimeError('M9 tile pack failed')
            return out
        x0,y0 = (index%8)*512-16,(index//8)*512-16
        xs,ys = np.arange(x0,x0+544),np.arange(y0,y0+544)
        valid = (ys[:,None]>=0)&(ys[:,None]<3072)&(xs[None,:]>=0)&(xs[None,:]<4096)
        cx,cy = np.clip(xs,0,4095),np.clip(ys,0,3071)
        styled = self.styled[(cy//4)[:,None],(cx//4)[None,:]]
        original = self.original[cy[:,None],cx[None,:]]
        pair = np.concatenate([styled,original],axis=-1)
        pair[~valid] = 0
        np.subtract(pair.transpose(2,0,1)[None],np.float32(128),out=out)
        np.divide(out,np.float32(127.5),out=out)
        return out

    def tile_output(self,index,tensor):
        if tensor.shape != (1,3,544,544):
            raise ValueError(f'M9 colorfix 输出尺寸错误：{tensor.shape}')
        if not 0<=index<48:raise ValueError('M9 tile index')
        if self.tile_library:
            tensor=np.ascontiguousarray(tensor,dtype=np.float32)
            if not self.tile_library.cl_m9_unpack(tensor.ctypes.data,index,self.output.ctypes.data):
                raise RuntimeError('M9 网络输出出现非有限值')
            return
        x0,y0 = (index%8)*512,(index//8)*512
        self.output[y0:y0+512,x0:x0+512] = decoded(tensor[0,:,16:528,16:528]).transpose(1,2,0)

    def recover(self):
        return Image.fromarray(self.output[self.top:self.top+self.height,self.left:self.left+self.width].copy())


@lru_cache(maxsize=16)
def _verified_model(path,identity,expected):
    digest=hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda:stream.read(1024*1024),b''):digest.update(block)
    if digest.hexdigest()!=expected:raise RuntimeError('M9 模型哈希不匹配')
    stat=path.stat()
    if (stat.st_size,stat.st_mtime_ns,stat.st_ctime_ns,stat.st_ino)!=identity:
        raise RuntimeError('M9 模型在校验时被修改，请重试')
    return path


def model_path(name):
    filename='colorfix_batch' if name in ('colorfix_b2','colorfix_b4') else name
    candidates = [ROOT/'assets/m9_models'/f'{filename}.onnx',ROOT/'research/models'/f'{filename}.onnx']
    path = next((p for p in candidates if p.exists()),None)
    if path is None:
        raise RuntimeError('缺少 M9 模型文件')
    stat=path.stat()
    return _verified_model(path.resolve(),(stat.st_size,stat.st_mtime_ns,stat.st_ctime_ns,stat.st_ino),MODEL_HASHES[name])


def prepare_frame(image,model,denoise,post=None,cancelled=None):
    """CPU prefix with an explicitly owned denoiser; no renderer state is mutated."""
    started=time.perf_counter();checkpoint=started;stages={}
    def mark(name):
        nonlocal checkpoint
        now=time.perf_counter();stages[name]=round(now-checkpoint,4);checkpoint=now
    original = image if image.mode=='RGB' else image.convert('RGB')
    from desktop_post import DenoiseRuntime,ImageRuntime
    from leica_params import parameters, settings
    lux,cct,zoom = settings(image.info.get('photo_info'))
    if model=='auto':model='high' if lux<=260 or cct>=4692 else 'low'
    gpu_prepare=bool(post and os.environ.get('CAMERALOOK_GPU_PREPARE')=='1')
    original_rgb=np.asarray(original)
    prepared_rgb=post.prepare(original_rgb,cancelled) if gpu_prepare else denoise.denoise(original_rgb,False,cancelled)
    prepared = Image.fromarray(prepared_rgb)
    mark('denoise_prepare')
    rotated = original.height>original.width
    work = prepared.transpose(Image.Transpose.ROTATE_270) if rotated else prepared.copy()
    scale = min(1,4096/work.width,3072/work.height)
    if scale<1:
        work = work.resize((max(1,int(np.float32(work.width)*np.float32(scale))),max(1,int(np.float32(work.height)*np.float32(scale)))),Image.Resampling.BILINEAR)
    if cancelled and cancelled():
        raise Cancelled()
    frame = FrameProtocol(np.asarray(work))
    frame.prepare()
    mark('frame_prepare')
    return dict(started=started,stages=stages,original=original,prepared=prepared,
                rotated=rotated,work=work,scale=scale,frame=frame,model=model,
                lux=lux,cct=cct,zoom=zoom,gpu_prepare=gpu_prepare,post=post,
                original_rgb=original_rgb,prepared_rgb=prepared_rgb)


def prepare_cpu_frame(image,index,cancelled=None):
    from desktop_post import DenoiseRuntime
    runtime=DenoiseRuntime()
    try:return prepare_frame(image,EXPERIMENTS[index-23]['model'],runtime,cancelled=cancelled)
    finally:runtime.close()


class M9Renderer:
    def __init__(self,backend='cpu',device_id=None,gpu=None):
        from edition import nvidia_supported
        if backend=='nvidia' and not nvidia_supported():raise RuntimeError('标准版不包含 NVIDIA 专用实验后端，请使用 DirectML 或全量版')
        import onnxruntime as ort
        self.ort = ort
        from dxgi_devices import adapters
        available_adapters = [a for a in adapters() if not a['software']]
        selected = max(available_adapters,key=lambda a:a['dedicated_bytes']) if available_adapters else {'id':0,'name':'DirectML adapter 0'}
        self.backend,self.device_id = backend,int(selected['id'] if device_id is None else device_id)
        self.sessions = {}
        self._shared_entries={}
        self.bindings={}
        self.io_fallback={}
        self._tile_tensor=np.empty((1,6,544,544),np.float32)
        self._tile_tensor_next=np.empty_like(self._tile_tensor)
        self._style_tensor=None
        self._tile_pool=None
        self.inference_timings={}
        self.context_cache_hits={}
        available = ort.get_available_providers()
        self.provider = 'DmlExecutionProvider' if backend!='cpu' and 'DmlExecutionProvider' in available else 'CPUExecutionProvider'
        if sys.platform=='darwin':
            coreml=backend!='cpu' and 'CoreMLExecutionProvider' in available and os.environ.get('CAMERALOOK_M9_COREML','1')!='0'
            self.provider='CoreMLExecutionProvider' if coreml else 'CPUExecutionProvider'
        self.inference_fallback=''
        # NVIDIA is experimental and requires an explicit backend selection.
        if backend=='nvidia':
            try:
                from nvidia_backend import device
                device(ort);self.provider='nv_tensorrt_rtx'
            except Exception as exc:
                if backend=='nvidia':raise RuntimeError(f'NVIDIA 加速组件不可用：{exc}') from exc
                self.inference_fallback=str(exc)
        if backend=='gpu' and self.provider=='CPUExecutionProvider' and sys.platform!='darwin':
            raise RuntimeError('没有可用的 DirectML GPU 推理提供程序')
        self.name = f'GPU · M9 DirectML · {selected["name"]}' if self.provider=='DmlExecutionProvider' else 'CPU · M9 ONNX'
        if self.provider=='nv_tensorrt_rtx':self.name=f'GPU · M9 NVIDIA TensorRT RTX · {selected["name"]}'
        if self.provider=='CoreMLExecutionProvider':self.name='M9 · CoreML (CPU/GPU/ANE)'
        self.last_report = {}
        self._texture = None
        self._denoise = None
        self.gpu=gpu
        self._owns_gpu=False
        self._post_fallback=''
        self._resident=None
        self._resident_fallback=''
        self._resident_unavailable=False
        self._batch_disabled={}

    def postprocessor(self):
        if self.backend=='cpu' or os.environ.get('CAMERALOOK_CPU_POST')=='1' or os.environ.get('CAMERALOOK_ARM_REFERENCE')=='1':return None
        try:
            if self.gpu is None:
                if sys.platform=='darwin':
                    from metal_renderer import MetalRenderer
                    self.gpu=MetalRenderer()
                else:
                    from gpu import GpuRenderer
                    self.gpu=GpuRenderer()
                self._owns_gpu=True
            return self.gpu.postprocessor()
        except Exception as exc:
            self._post_fallback=str(exc)
            return None

    @staticmethod
    def coreml_cache_dir():
        """Persistent ModelCacheDirectory so the CoreML compile happens once.

        Measured for the 864x1120 style model: first session 7.7 s with no cache,
        0.9 s once the 31 MB compiled artifact is on disk. Falls back to the temp
        directory on a sandboxed/read-only home so the option is always honoured.
        """
        import tempfile
        override = os.environ.get('CAMERALOOK_COREML_CACHE')
        candidates = ([Path(override).expanduser()] if override else []) + [
            Path.home()/'Library'/'Caches'/'FilmReshooter'/'coreml',
            Path(tempfile.gettempdir())/'FilmReshooter-coreml',
        ]
        for base in candidates:
            try:
                base.mkdir(parents=True, exist_ok=True)
                return base
            except OSError:
                continue
        return None

    def session(self,name):
        if name in self.sessions:
            entry=self._shared_entries.get(name)
            if entry is None or not entry.invalid:return self.sessions[name]
            self.sessions.pop(name,None);self._shared_entries.pop(name,None)
        if self.provider=='nv_tensorrt_rtx':
            # CUDA graphs capture per-renderer binding addresses; never share these.
            from inference_cache import SESSIONS
            SESSIONS.clear()
            return self._create_session(name)
        from inference_cache import SESSIONS
        key=(self.provider,self.device_id,name,MODEL_HASHES[name],'fp32-shapes-v1')
        entry=SESSIONS.acquire(key,lambda:self._create_session(name))
        self.sessions[name]=entry.session
        self._shared_entries[name]=entry
        return entry.session

    def _create_session(self,name):
        if name not in self.sessions:
            options = self.ort.SessionOptions()
            options.intra_op_num_threads = min(8,os.cpu_count() or 4)
            options.inter_op_num_threads = 1
            options.enable_mem_pattern = False
            options.execution_mode = self.ort.ExecutionMode.ORT_SEQUENTIAL
            # Fix shapes before optimization, matching the APK's session setup.
            batch=int(name[-1]) if name in ('colorfix_b2','colorfix_b4') else 1
            height,width = (544,544) if name.startswith('colorfix') else (864,1120)
            if batch>1:options.add_free_dimension_override_by_name('batch',batch)
            options.add_free_dimension_override_by_name('height',height)
            options.add_free_dimension_override_by_name('width',width)
            providers = [('DmlExecutionProvider',{'device_id':self.device_id}),'CPUExecutionProvider'] if self.provider=='DmlExecutionProvider' else ['CPUExecutionProvider']
            if self.provider=='CoreMLExecutionProvider':
                coreml_options={'MLComputeUnits':'ALL'}
                cache=self.coreml_cache_dir()
                if cache is not None:coreml_options['ModelCacheDirectory']=str(cache)
                providers=[('CoreMLExecutionProvider',coreml_options),'CPUExecutionProvider']
            if self.provider=='nv_tensorrt_rtx':
                from nvidia_backend import configure,create_session
                self.nvidia_cache=configure(self.ort,options,workspace_megabytes=1024 if batch==4 else 512)
                original_path=model_path(name)
                workspace_tag='-ws1024' if batch==4 else ''
                context_path=self.nvidia_cache/f'{name}-{MODEL_HASHES[name][:16]}-544-864{workspace_tag}-context.onnx'
                # Passing providers here would override the plugin device options.
                try:
                    self.sessions[name],cached,note=create_session(self.ort,options,original_path,context_path)
                    if note:self.inference_fallback=note
                except Exception as exc:
                    if batch>1:raise  # Batch failure is handled locally without changing providers.
                    if self.backend!='auto':raise
                    self.inference_fallback=f'NVIDIA 不可用，改用 DirectML：{exc}'
                    self.bindings.clear();self.sessions.clear()
                    self.provider='DmlExecutionProvider' if 'DmlExecutionProvider' in self.ort.get_available_providers() else 'CPUExecutionProvider'
                    self.name='GPU · M9 DirectML' if self.provider=='DmlExecutionProvider' else 'CPU · M9 ONNX'
                    return self.session(name)
                self.context_cache_hits[name]=cached
            else:
                self.sessions[name] = self.ort.InferenceSession(str(model_path(name)),sess_options=options,providers=providers)
        return self.sessions[name]

    def device_binding(self,name):
        if name not in self.bindings:
            session=self.session(name)
            batch=int(name[-1]) if name in ('colorfix_b2','colorfix_b4') else 1
            channels,height,width=(6,544,544) if name.startswith('colorfix') else (4,864,1120)
            inp=self.ort.OrtValue.ortvalue_from_shape_and_type((batch,channels,height,width),np.float32,'gpu',0,0x10de)
            out=self.ort.OrtValue.ortvalue_from_shape_and_type((batch,3,height,width),np.float32,'gpu',0,0x10de)
            binding=session.io_binding();binding.bind_ortvalue_input('input',inp)
            binding.bind_ortvalue_output(session.get_outputs()[0].name,out)
            self.bindings[name]=(binding,inp,out)
        return self.bindings[name]

    def infer(self,name,tensor,return_device=False,input_on_device=False):
        stats=self.inference_timings.setdefault(name,{'calls':0,'binding_setup_seconds':0.,
            'upload_and_wait_seconds':0.,'run_and_wait_seconds':0.,'readback_seconds':0.})
        stats['calls']+=1
        session=self.session(name)
        if self.provider!='nv_tensorrt_rtx':
            if return_device or input_on_device:raise RuntimeError('Resident tiles require NVIDIA')
            from inference_cache import SESSIONS
            started=time.perf_counter()
            entry=self._shared_entries[name]
            try:
                with SESSIONS.running(entry):
                    result=session.run(None,{'input':tensor})[0]
            except Exception:
                SESSIONS.invalidate(entry)
                self.sessions.pop(name,None);self._shared_entries.pop(name,None)
                raise
            stats['run_and_wait_seconds']+=time.perf_counter()-started
            return result
        started=time.perf_counter()
        if name not in self.bindings:
            try:
                self.device_binding(name)
            except Exception as exc:
                self.bindings[name]=None;self.io_fallback[name]=str(exc)
        stats['binding_setup_seconds']+=time.perf_counter()-started
        state=self.bindings[name]
        if state is None:
            if return_device or input_on_device:raise RuntimeError('NVIDIA device binding unavailable')
            started=time.perf_counter();result=session.run(None,{'input':tensor})[0]
            stats['run_and_wait_seconds']+=time.perf_counter()-started
            return result
        binding,inp,out=state
        started=time.perf_counter()
        if not input_on_device:inp.update_inplace(tensor)
        binding.synchronize_inputs()
        stats['upload_and_wait_seconds']+=time.perf_counter()-started
        started=time.perf_counter()
        session.run_with_iobinding(binding)
        binding.synchronize_outputs()
        stats['run_and_wait_seconds']+=time.perf_counter()-started
        started=time.perf_counter();result=out if return_device else out.numpy()
        stats['readback_seconds']+=time.perf_counter()-started
        return result

    def resident_tiles(self,frame,tiles,style,progress=None,cancelled=None,batch=1):
        """Keep style decoding, tile packing and output assembly on CUDA."""
        import time
        from cuda_tiles import CudaTiles
        if self._resident is None:self._resident=CudaTiles()
        runtime=self._resident
        name=f'colorfix_b{batch}' if batch>1 else 'colorfix'
        free_before,total_memory=runtime.free_memory();free_low=free_before
        started=time.perf_counter();runtime.begin(frame,style)
        upload_seconds=time.perf_counter()-started
        binding,inp,out=self.device_binding(name)
        packing=stitching=0.
        for start in range(0,len(tiles),batch):
            if cancelled and cancelled():raise Cancelled()
            group=tiles[start:start+batch]
            started=time.perf_counter();runtime.pack(group,batch,inp)
            packing+=time.perf_counter()-started
            out=self.infer(name,None,return_device=True,input_on_device=True)
            free_low=min(free_low,runtime.free_memory()[0])
            started=time.perf_counter();runtime.unpack(group,out)
            stitching+=time.perf_counter()-started
            if progress:progress(.15+.8*min(start+batch,len(tiles))/len(tiles))
        if cancelled and cancelled():raise Cancelled()
        started=time.perf_counter();result=Image.fromarray(runtime.recover(frame))
        readback_seconds=time.perf_counter()-started
        stats={'pipeline':False,'resident':True,'batch_size':batch,'inference_calls':(len(tiles)+batch-1)//batch,
               'upload_seconds':round(upload_seconds,6),'pack_and_wait_seconds':round(packing,6),
               'stitch_dispatch_seconds':round(stitching,6),'merged_readback_seconds':round(readback_seconds,6),
               'per_tile_host_transfers':0,'merged_host_readbacks':1,'style_host_readbacks':0,
               'retained_megabytes':round(sum(s for _,s in runtime.buffers.values())/1024**2,2),
               'device_total_megabytes':round(total_memory/1024**2,1),
               'device_used_high_megabytes':round((total_memory-free_low)/1024**2,1),
               'device_memory_scope':'whole device sampled after each group; includes other processes, not exact allocation peak',
               'scope':'CUDA style/packing/crop/stitch; one merged readback before existing resize/OpenGL post'}
        return result,stats

    def colorfix_tiles(self,frame,tiles,progress=None,cancelled=None):
        """Two host slots; prepare N+1 while the owning render thread runs N.

        GPU bindings deliberately stay at fixed addresses for CUDA graph replay.
        The producer never calls ORT/OpenGL or modifies the active host slot.
        Transfers retain the provider's required synchronization.
        """
        from concurrent.futures import ThreadPoolExecutor
        pipeline=os.environ.get('CAMERALOOK_M9_SERIAL_TILES')!='1' and len(tiles)>1
        stats={'pipeline':pipeline,'pack_seconds':0.,'unpack_seconds':0.,'producer_wait_seconds':0.,
               'host_slots':2 if pipeline else 1,'device_bindings':'fixed addresses',
               'timing_scope':'CPU wall times; packing overlaps inference; transfer timers include waits'}
        def pack(index,buffer):
            if cancelled and cancelled():raise Cancelled()
            started=time.perf_counter();frame.tile_input(index,buffer)
            return time.perf_counter()-started
        def consume(position,index,buffer):
            if cancelled and cancelled():raise Cancelled()
            out=self.infer('colorfix',buffer)
            if cancelled and cancelled():raise Cancelled()
            started=time.perf_counter();frame.tile_output(index,out)
            stats['unpack_seconds']+=time.perf_counter()-started
            if progress:progress(.15+.8*(position+1)/len(tiles))
        if not pipeline:
            for pos,index in enumerate(tiles):
                stats['pack_seconds']+=pack(index,self._tile_tensor)
                consume(pos,index,self._tile_tensor)
        else:
            if self._tile_pool is None:self._tile_pool=ThreadPoolExecutor(max_workers=1,thread_name_prefix='M9-pack')
            buffers=(self._tile_tensor,self._tile_tensor_next)
            future=self._tile_pool.submit(pack,tiles[0],buffers[0])
            try:
                for pos,index in enumerate(tiles):
                    started=time.perf_counter();duration=future.result()
                    stats['producer_wait_seconds']+=time.perf_counter()-started
                    stats['pack_seconds']+=duration
                    if pos+1<len(tiles):future=self._tile_pool.submit(pack,tiles[pos+1],buffers[(pos+1)%2])
                    consume(pos,index,buffers[pos%2])
            finally:
                # Drain the producer before the frame/host slots can be reused.
                if not future.cancel():
                    try:future.result()
                    except Exception:pass
        return {key:round(value,6) if isinstance(value,float) else value for key,value in stats.items()}

    def prepare(self,image,model='high',cancelled=None):
        from desktop_post import DenoiseRuntime
        if self._denoise is None:self._denoise=DenoiseRuntime()
        return prepare_frame(image,model,self._denoise,self.postprocessor(),cancelled)

    def render_prepared(self,prep,strength=1,progress=None,cancelled=None):
        from desktop_post import DenoiseRuntime,ImageRuntime
        from leica_params import parameters
        if self._denoise is None:self._denoise=DenoiseRuntime()
        if self._texture is None:self._texture=ImageRuntime()
        self.inference_timings={}
        started=prep['started'];owner_started=checkpoint=time.perf_counter()
        stages=dict(prep['stages'])
        def mark(name):
            nonlocal checkpoint
            now=time.perf_counter();stages[name]=round(now-checkpoint,4);checkpoint=now
        original,prepared,work=prep['original'],prep['prepared'],prep['work']
        rotated,scale,frame=prep['rotated'],prep['scale'],prep['frame']
        model,lux,cct,zoom=prep['model'],prep['lux'],prep['cct'],prep['zoom']
        gpu_prepare=prep['gpu_prepare']
        post=prep['post'] if prep['post'] is not None else self.postprocessor()
        if progress:
            progress(.03)
        style_session = self.session(model)
        if cancelled and cancelled():raise Cancelled()
        mark('style_session')
        resident=self.provider=='nv_tensorrt_rtx' and os.environ.get('CAMERALOOK_M9_RESIDENT','auto')!='0' and not self._resident_unavailable
        if resident and self._resident is None:
            try:
                from cuda_tiles import CudaTiles
                self._resident=CudaTiles()
            except (OSError,RuntimeError,AttributeError) as exc:
                self._resident_fallback=str(exc);self._resident_unavailable=True;resident=False
        requested_batch=int(os.environ.get('CAMERALOOK_M9_BATCH_SIZE','1')) if resident else 1
        if requested_batch not in (1,2,4):raise ValueError('M9 batch size must be 1, 2 or 4')
        from inference_cache import STYLES
        # Reduced pixels determine style input. A path alone is never an identity.
        style_key=(hashlib.sha256(memoryview(frame.reduced)).hexdigest(),MODEL_HASHES[model],
                   self.provider,self.device_id,os.environ.get('NVIDIA_TF32_OVERRIDE','0'),'style-v1')
        cache_enabled=not resident and os.environ.get('CAMERALOOK_M9_STYLE_CACHE')!='0'
        cached=STYLES.get(style_key) if cache_enabled else None
        style_cache_hit=cached is not None
        style=None
        if style_cache_hit:frame.styled=cached
        else:
            if self._style_tensor is None:self._style_tensor=np.empty((1,4,864,1120),np.float32)
            tensor=frame.style_input(self._style_tensor)
            style=self.infer(model,tensor,return_device=resident)
            if not resident:
                frame.style_output(style)
                if cache_enabled:STYLES.store(style_key,frame.styled)
            del tensor
        mark('style_inference')
        if progress:
            progress(.15)
        tiles = frame.visible_tiles()
        actual_batch=requested_batch
        if requested_batch in self._batch_disabled:actual_batch=1
        try:self.session(f'colorfix_b{actual_batch}' if actual_batch>1 else 'colorfix')
        except Exception as exc:
            if actual_batch==1:raise
            self._batch_disabled[actual_batch]=str(exc);actual_batch=1
            self.session('colorfix')
        if cancelled and cancelled():raise Cancelled()
        mark('colorfix_session')
        if resident:
            try:result,tile_timings=self.resident_tiles(frame,tiles,style,progress,cancelled,actual_batch)
            except Cancelled:raise
            except Exception as exc:
                # A failed optional path must not leave a partially stitched image.
                self._resident_fallback=str(exc);self._resident_unavailable=True
                if self._resident:self._resident.close();self._resident=None
                frame.style_output(style.numpy());resident=False
                tile_timings=self.colorfix_tiles(frame,tiles,progress,cancelled);result=frame.recover()
        else:
            tile_timings=self.colorfix_tiles(frame,tiles,progress,cancelled)
            result=frame.recover()
        del style
        mark('colorfix_tiles')
        if scale<1:
            result = result.resize((original.height,original.width) if rotated else original.size,Image.Resampling.BILINEAR)
        if rotated:
            result = result.transpose(Image.Transpose.ROTATE_90)
        mark('restore_size')
        params = parameters()
        if post:
            result=Image.fromarray(post.finish(np.asarray(result),prep['prepared_rgb'],prep['original_rgb'],
                params.lut(lux,cct),params.shading(zoom,lux,cct),strength,cancelled,reuse_prepared=gpu_prepare))
            mark('gpu_post_chain')
        else:
            result = self._denoise.scene(result,params.lut(lux,cct),params.shading(zoom,lux,cct),cancelled)
            mark('scene_lut_shading')
            if progress: progress(.96)
            result = Image.fromarray(self._denoise.denoise(np.asarray(result),True,cancelled))
            mark('denoise_finish')
            result = Image.fromarray(self._texture.texture(np.asarray(prepared),np.asarray(result),cancelled))
            mark('texture')
            if strength!=1:
                src = np.array(original,np.float32)
                result = Image.fromarray(np.clip(src+(np.array(result,np.float32)-src)*strength,0,255).astype(np.uint8))
            mark('blend')
        self.last_report = {'provider':self.name,'model':model,'tiles':len(tiles),'work_size':work.size,
            'output_size':result.size,'seconds':round(time.perf_counter()-started,3),
            'lux':lux,'cct':cct,'zoom':zoom,
            'stages':stages,'style_cache_hit':style_cache_hit,
            'prefix_seconds':sum(prep['stages'].values()),'owner_seconds':round(time.perf_counter()-owner_started,4),
            'timing_scope':'seconds spans preparation and queue delay; owner_seconds excludes both; pipeline wall stages overlap',
            'tile_backend':'CUDA resident' if resident else 'native C' if frame.tile_library else 'NumPy',
            'tile_fallback':frame.tile_fallback,'tile_timings':tile_timings,
            'resident_fallback':self._resident_fallback,
            'requested_batch_size':requested_batch,'batch_fallback':self._batch_disabled.get(requested_batch,''),
            'inference_timings':{name:{k:round(v,6) if isinstance(v,float) else v for k,v in row.items()}
                                 for name,row in self.inference_timings.items()},
            'post_backend':'GPU OpenGL' if post else self._denoise.name,
            'texture_backend':'GPU OpenGL' if post else self._texture.name,
            'gpu_post':post.last_report if post else None,
            'post_fallback':self._post_fallback,
            'prepare_backend':'GPU OpenGL' if gpu_prepare else self._denoise.name,
            'inference_fallback':self.inference_fallback,
            'gpu_io_binding':bool(self.bindings) and all(v is not None for v in self.bindings.values()),
            'io_fallback':self.io_fallback,
            'context_cache_hits':self.context_cache_hits,
            'nvidia_cache_path':str(self.nvidia_cache) if hasattr(self,'nvidia_cache') else None,
            'scope':'Frame + original networks + GPU scene/denoise/texture/blend' if post else f'Frame + original networks + {self._denoise.name} scene/denoise + {self._texture.name} texture'}
        if progress:
            progress(1)
        return result


    def render(self,image,model='high',strength=1,progress=None,cancelled=None):
        return self.render_prepared(self.prepare(image,model,cancelled),strength,progress,cancelled)

    def close(self):
        self._style_tensor=None
        if self._tile_pool is not None:self._tile_pool.shutdown(wait=True,cancel_futures=True)
        self._tile_pool=None
        if self._resident:self._resident.close();self._resident=None
        self.bindings.clear()
        self.sessions.clear()
        self._shared_entries.clear()
        for runtime in (self._texture,self._denoise):
            if runtime:runtime.close()
        self._texture = self._denoise = None
        if self._owns_gpu and self.gpu:self.gpu.close()
        self.gpu=None;self._owns_gpu=False
