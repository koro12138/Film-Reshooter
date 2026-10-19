"""Original M3 base filter plus a desktop port of Monopan's default kernels.

Monopan mode 0: limited-range Y -> SimulateResize -> Gaussian(3,.2) ->
OutputMix(.3) -> full-range gray. At 8-bit precision Gaussian(3,.2) rounds
exactly to its input (maximum possible change is below .004 code values).
"""
from functools import lru_cache
import time
import os
import native_lib
import numpy as np
from PIL import Image
from engine import ROOT,Cancelled,blend_original


@lru_cache(maxsize=1)
def tables():
    with np.load(ROOT/'assets/monopan_tables.npz',allow_pickle=False) as archive:
        return {key:archive[key].squeeze() for key in archive.files}


def grain_cpu(rgb,cancelled=None):
    t=tables()
    p,b,lut,rand=(t[k] for k in ('m_pixel_map','m_batch_map','m_lut_map','m_rand_map_pixel'))
    lut=lut.reshape(-1)
    h,w=rgb.shape[:2]
    out=np.empty_like(rgb)
    for top in range(0,h,128):
        if cancelled and cancelled():raise Cancelled()
        a=rgb[top:top+128].astype(np.uint32)
        luminance=(((a[...,0]*66+a[...,1]*129+a[...,2]*25+128)>>8)+16).astype(np.uint8)
        ys=np.arange(top,min(top+128,h))[:,None];xs=np.arange(w)[None,:]
        first=rand[ys%4096,xs%3072]
        second=rand[(h-1-ys)%4096,(w-1-xs)%3072]
        pixel=p[luminance,first]
        batch=b[pixel,second]
        value=np.minimum(255,np.floor(lut[batch].astype(np.float32)*np.sqrt(luminance.astype(np.float32)/255)*16+.5)).astype(np.uint8)
        mixed=np.clip(value.astype(np.float32)*np.float32(.3)+luminance.astype(np.float32)*np.float32(.7),0,255).astype(np.uint8)
        gray=np.clip((mixed.astype(np.int32)*298-4640)>>8,0,255).astype(np.uint8)
        out[top:top+128]=gray[...,None]
    return out


SHADER=r'''
#version 430
layout(local_size_x=256) in;
layout(std430,binding=0) readonly buffer Input { vec4 src[]; };
layout(std430,binding=1) writeonly buffer Output { uint dst[]; };
layout(std430,binding=3) readonly buffer Pixel { uint pixels[]; };
layout(std430,binding=4) readonly buffer Batch { uint batches[]; };
layout(std430,binding=5) readonly buffer Lut { uint luts[]; };
layout(std430,binding=6) readonly buffer Random { uint randoms[]; };
uniform int width,height,count;
uint bytePixel(uint i){ return (pixels[i/4u]>>((i%4u)*8u))&255u; }
uint byteLut(uint i){ return (luts[i/4u]>>((i%4u)*8u))&255u; }
uint byteRandom(uint i){ return (randoms[i/4u]>>((i%4u)*8u))&255u; }
void main(){
 uint i=gl_GlobalInvocationID.x;if(i>=uint(count))return;
 uint x=i%uint(width),y=i/uint(width);
 uvec3 rgb=uvec3(floor(clamp(src[i].rgb,0.,1.)*255.+.5));
 uint lum=((rgb.r*66u+rgb.g*129u+rgb.b*25u+128u)>>8u)+16u;
 uint r1=byteRandom((y%4096u)*3072u+x%3072u);
 uint r2=byteRandom(((uint(height)-1u-y)%4096u)*3072u+(uint(width)-1u-x)%3072u);
 uint p=bytePixel(lum*256u+r1),j=p*256u+r2;
 uint b=(batches[j/2u]>>((j%2u)*16u))&65535u;
 float simulated=floor(min(255.,float(byteLut(b))*sqrt(float(lum)/255.)*16.+.5));
 int mixed=int(simulated*.3+float(lum)*.7);
 float value=float(clamp((mixed*298-4640)>>8,0,255))/255.;
 uint v=uint(floor(clamp(value,0.,1.)*255.+.5));
 dst[i]=v|(v<<8u)|(v<<16u)|0xFF000000u;
}
'''


# Byte input: the caller already holds RGBA8, so the grain pass no longer has to
# upload a float32 copy that the shader immediately rounds back to bytes.
SHADER_U8=SHADER.replace('readonly buffer Input { vec4 src[]; };',
                         'readonly buffer Input { uint src[]; };').replace(
    'uvec3 rgb=uvec3(floor(clamp(src[i].rgb,0.,1.)*255.+.5));',
    'uint word=src[i];uvec3 rgb=uvec3(word&255u,(word>>8u)&255u,(word>>16u)&255u);')


def grain_gpu(gpu,rgb):
    if not getattr(gpu,'m3_program',None):
        gpu.m3_program=gpu.ctx.compute_shader(SHADER_U8)
        gpu.m3_buffers=[gpu.ctx.buffer(np.ascontiguousarray(tables()[key]).tobytes()) for key in
            ('m_pixel_map','m_batch_map','m_lut_map','m_rand_map_pixel')]
    for binding,buffer in enumerate(gpu.m3_buffers,3):buffer.bind_to_storage_buffer(binding)
    h,w=rgb.shape[:2]
    rgba=np.empty((h,w,4),np.uint8);rgba[...,:3]=rgb;rgba[...,3]=255
    gpu.m3_program['height'].value=h
    return gpu.dispatch(gpu.m3_program,rgba.view(np.uint32).reshape(h,w),(h,w),packed_output=True)


class M3Renderer:
    def __init__(self):
        from native_runtime import NativeImageRuntime
        from desktop_post import DenoiseRuntime,ImageRuntime
        from desktop_m3 import GuardRuntime
        from desktop_m3_core import CoreRuntime
        self.base=None
        # The native core preserves NEON operation order before hard guards.
        self.core=CoreRuntime()
        self.input_denoise=None
        self.prepare_backend='';self.base_backend=''
        self.denoise=DenoiseRuntime()
        self.output=ImageRuntime()
        self.guard=GuardRuntime()
        self.last_report={}
        self.base_workers=1
        self.base_pool=None
        self.base_pool_size=0
        self.base_runtimes={}
        self.base_worker_reports=[]

    def close_base_pool(self):
        if self.base_pool is not None:
            self.base_pool.shutdown(wait=True,cancel_futures=True)
            self.base_pool=None
        for runtime in self.base_runtimes.values():runtime.close()
        self.base_runtimes.clear();self.base_pool_size=0

    def runtime(self,attribute,library,heap_bytes):
        from native_runtime import NativeImageRuntime
        runtime=getattr(self,attribute)
        if runtime is None or runtime.heap_capacity<heap_bytes:
            if runtime is not None:runtime.close()
            runtime=NativeImageRuntime(library,heap_bytes=heap_bytes)
            setattr(self,attribute,runtime)
        return runtime

    def render_base(self,prepared,cancelled=None):
        if self.core.available and os.environ.get('CAMERALOOK_ARM_M3_BASE')!='1':
            self.base_backend=native_lib.backend_name()
            out=self.core.base(prepared,cancelled)
            self.base_workers=self.core.workers
            self.base_worker_reports=self.core.worker_reports
            return out
        self.base_backend='original zxbase ARM64'
        h,w=prepared.shape[:2]
        workers=min(4,max(1,(os.cpu_count() or 1)//2),max(1,h//128))
        if (w*h<2000000 and os.environ.get('CAMERALOOK_PARALLEL_M3')!='1') or os.environ.get('CAMERALOOK_SERIAL_M3')=='1':workers=1
        self.base_workers=workers
        heap_bytes=w*h*4+16*1024*1024
        workers=min(workers,max(1,(512*1024*1024)//heap_bytes))
        self.base_workers=workers
        if workers==1:
            self.close_base_pool();self.base_worker_reports=[]
            return self.runtime('base','libzxbase.so',heap_bytes).m3_filter(prepared,cancelled)
        from concurrent.futures import ThreadPoolExecutor
        from threading import get_ident
        from native_runtime import NativeImageRuntime
        if self.base is not None:self.base.close();self.base=None
        if self.base_pool_size!=workers:
            self.close_base_pool()
            self.base_pool=ThreadPoolExecutor(max_workers=workers,thread_name_prefix='M3-base')
            self.base_pool_size=workers
        def rows(index):
            started=time.perf_counter();ident=get_ident();runtime=self.base_runtimes.get(ident)
            if runtime is None or runtime.heap_capacity<heap_bytes:
                if runtime is not None:runtime.close()
                runtime=NativeImageRuntime('libzxbase.so',heap_bytes=heap_bytes)
                self.base_runtimes[ident]=runtime
            ready=time.perf_counter()
            out=runtime.m3_filter(prepared,cancelled,(h*index//workers,h*(index+1)//workers))
            return out,{'setup_seconds':round(ready-started,4),'render_seconds':round(time.perf_counter()-ready,4),
                        'heap_megabytes':round(runtime.heap_capacity/1024**2,1)}
        # Each worker owns its ARM engine and memory; image coordinates are global.
        pieces=list(self.base_pool.map(rows,range(workers)))
        self.base_worker_reports=[p[1] for p in pieces]
        return np.concatenate([p[0] for p in pieces],axis=0)

    def render(self,image,strength=1,gpu=None,progress=None,cancelled=None):
        started=time.perf_counter()
        stages={};checkpoint=started
        def mark(name):
            nonlocal checkpoint
            now=time.perf_counter();stages[name]=round(now-checkpoint,4);checkpoint=now
        original=np.asarray(image.convert('RGB'))
        height,width=original.shape[:2]
        gpu_denoise=bool(gpu and not getattr(gpu,'whole_image',False) and os.environ.get('CAMERALOOK_M3_GPU_DENOISE','1')!='0'
                         and os.environ.get('CAMERALOOK_ARM_REFERENCE')!='1')
        prepared=None;gpu_denoise_fallback='';gpu_denoise_reports={}
        if gpu_denoise and os.environ.get('CAMERALOOK_ARM_M3_PREPARE')!='1':
            try:
                prepared=gpu.postprocessor().denoise(original,False,cancelled,m3_prepare=True)
                gpu_denoise_reports['prepare']=dict(gpu.postprocessor().last_report)
                self.prepare_backend='GPU OpenGL · exact M3'
            except Cancelled:raise
            except Exception as exc:gpu_denoise_fallback=str(exc);gpu_denoise=False
        if prepared is not None:pass
        elif self.core.available and os.environ.get('CAMERALOOK_ARM_M3_PREPARE')!='1':
            self.prepare_backend=native_lib.backend_name()
            prepared=self.core.prepare(original,cancelled)
        else:
            self.prepare_backend='original ARM64'
            self.runtime('input_denoise','libleicadenoise.so',width*height*4+width*192+8*1024*1024)
            prepared=self.input_denoise.denoise(original,False,cancelled)
        mark('denoise_prepare')
        base=self.render_base(prepared,cancelled)
        mark('base')
        base=self.guard.quality_guard(prepared,base,False,cancelled,inplace=True)
        guard_before_report=dict(self.guard.last_report)
        mark('guard_before')
        if progress:progress(.5)
        h,w=base.shape[:2]
        pad=np.pad(base,((0,h%2),(0,(-w)%8),(0,0)),mode='edge')
        mono=(gpu.monopan_grain(pad,cancelled) if getattr(gpu,'monopan_grain',None) else grain_gpu(gpu,pad) if gpu else grain_cpu(pad,cancelled))
        mono=mono[:h,:w]
        mark('monopan')
        mono=self.guard.quality_guard(base,mono,True,cancelled,inplace=True)
        mark('grade_guard')
        if gpu_denoise:
            try:
                mono=gpu.postprocessor().denoise(mono,True,cancelled,exact_divisions=True)
                gpu_denoise_reports['finish']=dict(gpu.postprocessor().last_report)
            except Cancelled:raise
            except Exception as exc:
                gpu_denoise_fallback=str(exc);gpu_denoise=False
                mono=self.denoise.denoise(mono,True,cancelled)
        else:mono=self.denoise.denoise(mono,True,cancelled)
        mark('denoise_finish')
        mono=self.output.output_denoise(mono,1,cancelled)
        mark('output_denoise')
        if strength!=1:mono=blend_original(mono,original,strength,round_half=False)
        self.last_report={'seconds':round(time.perf_counter()-started,3),'monopan':'original mode 0 tables + ported kernels',
            'base':self.base_backend,'quality':'original M3 grade/guard/denoise','grain_backend':'Metal' if getattr(gpu,'monopan_grain',None) else 'GPU OpenGL' if gpu else 'CPU NumPy'}
        self.last_report.update(stages=stages,denoise_backend=self.denoise.name,output_backend=self.output.name)
        self.last_report['denoise_finish_backend']='GPU OpenGL' if gpu_denoise else self.denoise.name
        self.last_report['gpu_denoise_fallback']=gpu_denoise_fallback
        self.last_report['gpu_denoise']=gpu_denoise_reports
        self.last_report['base_workers']=self.base_workers
        self.last_report['prepare_backend']=self.prepare_backend
        self.last_report['base_backend']=self.base_backend
        self.last_report['core_fallback_reason']=self.core.fallback_reason
        self.last_report['arm_engines']=int(self.input_denoise is not None)+int(self.base is not None)+len(self.base_runtimes)+sum(int(getattr(r,'reference',None) is not None) for r in (self.denoise,self.output,self.guard))
        self.last_report['guard_heap_megabytes']=round(self.guard.heap_capacity/1024**2,1)
        self.last_report['guard_backend']=self.guard.name
        self.last_report['guard_before_report']=guard_before_report
        self.last_report['guard_after_report']=dict(self.guard.last_report)
        self.last_report['base_worker_timings']=self.base_worker_reports
        if progress:progress(1)
        return Image.fromarray(mono)

    def close(self):
        self.core.close()
        self.close_base_pool()
        for runtime in (self.base,self.input_denoise,self.denoise,self.output,self.guard):
            if runtime:runtime.close()
        self.base=self.input_denoise=self.denoise=self.output=self.guard=None
