"""CameraLook LUT and film math ported from the supplied APK's ToneMath/ToneTable.

CPU: bounded NumPy stripes. GPU: OpenGL 4.3 compute, same tetrahedral math.
Native postprocessing has independently validated desktop implementations.
"""
from pathlib import Path
from functools import lru_cache
import json
import struct
import sys
import time
import numpy as np

ROOT = Path(getattr(sys, '_MEIPASS', Path(__file__).resolve().parent))
CATALOG = json.loads((ROOT / 'assets/catalog.json').read_text('utf-8'))
LUMA = np.array([.2126, .7152, .0722], np.float32)


def cpu_workers():
    import os
    from portable_paths import available_memory
    default=max(1,min(8,(os.cpu_count() or 1)//2))
    try:requested=max(1,min(16,int(os.environ.get('CAMERALOOK_CPU_WORKERS',default))))
    except ValueError:requested=default
    free=available_memory()
    if free is None:return 1
    return min(requested,max(1,(free-1024**3)//(64*1024**2)))


def blend_original(result, original, strength=1.0, round_half=True):
    """Lerp a rendered result back toward the source in place, one buffer at a time.

    `strength` blending used to allocate six full-size temporaries per stripe
    (astype x2, subtract, multiply, add, clip, astype). Every step here reuses the
    same float32 scratch, so a 27MP blend no longer costs ~0.9s in allocator churn.
    """
    scratch = result.astype(np.float32)
    np.subtract(scratch, original, out=scratch)
    scratch *= np.float32(strength)
    np.add(scratch, original, out=scratch)
    np.clip(scratch, 0, 255, out=scratch)
    if round_half:
        scratch += np.float32(.5)
    np.floor(scratch, out=scratch)
    return scratch.astype(np.uint8)


def quantize(x):
    return np.floor(np.clip(x, 0, 1) * np.float32(255) + np.float32(.5)).astype(np.uint8)


@lru_cache(maxsize=23)
def load_lut(index):
    data = (ROOT / f'assets/cameralook/tone-{index}.lut').read_bytes()
    magic, n = struct.unpack_from('>II', data)
    if magic != 1129076017 or not 2 <= n <= 65 or len(data) != 32 + n**3 * 12:
        raise ValueError('滤镜数据无效')
    domain = np.frombuffer(data, '>f4', count=6, offset=8).astype(np.float32).reshape(2, 3)
    lut = np.frombuffer(data, '>f4', offset=32).astype(np.float32).reshape(-1, 3)
    if not np.isfinite(lut).all() or np.any(domain[1] <= domain[0]):
        raise ValueError('滤镜数据范围无效')
    return n, domain, lut


def tetrahedral(rgb, n, domain, lut):
    coords = np.clip((rgb - domain[0]) / (domain[1] - domain[0]), 0, 1) * np.float32(n - 1)
    base = np.minimum(coords.astype(np.int32), n - 2)
    # Cast before subtracting: float32 - int32 promotes to float64.
    fract = coords - base.astype(np.float32)
    # Sort fractional R/G/B, then walk the tetrahedron's four vertices.
    order = np.argsort(-fract, axis=-1, kind='stable')
    weights = np.take_along_axis(fract, order, axis=-1).astype(np.float32)
    strides = np.array([1, n, n*n], np.int32)
    offsets = strides[order]
    # Written out instead of (base*strides).sum(-1): same integer arithmetic and
    # summation order, but one fewer 3-channel temporary per stripe.
    i0 = base[..., 0] + base[..., 1] * strides[1] + base[..., 2] * strides[2]
    i1 = i0 + offsets[..., 0]
    i2 = i1 + offsets[..., 1]
    i3 = i0 + 1 + n + n*n
    c0, c1, c2, c3 = lut[i0], lut[i1], lut[i2], lut[i3]
    # In-place accumulation: identical rounding order to the previous expression
    # (c0 + (c1-c0)*w0 + (c2-c1)*w1 + (c3-c2)*w2), without six full-size temporaries.
    out = c0
    tmp = np.subtract(c1, c0)
    tmp *= weights[..., 0, None]
    out += tmp
    np.subtract(c2, c1, out=tmp)
    tmp *= weights[..., 1, None]
    out += tmp
    np.subtract(c3, c2, out=tmp)
    tmp *= weights[..., 2, None]
    out += tmp
    np.clip(out, 0, 1, out=out)
    return out


def _identity_curve(points):
    """True for the 0/0 -> 255/255 ramp, where curve() is the identity."""
    return bool(points.shape[0] == 2 and points[0, 0] == 0 and points[0, 1] == 0
                and points[1, 0] == 255 and points[1, 1] == 255)


def curve(rgb, points):
    points = np.asarray(points, np.float32).reshape(-1, 2)
    # Most filters ship the identity ramp; np.interp would still touch 27M pixels.
    if _identity_curve(points):
        return rgb
    points = points / np.float32(255)
    return np.interp(np.clip(rgb, 0, 1), points[:, 0], points[:, 1]).astype(np.float32)


def tone_cpu(rgb, index, high_precision=False):
    p = CATALOG[index]
    out = curve(tetrahedral(rgb, *load_lut(index)), p['rgb'])
    lum = out @ LUMA
    mapped = curve(lum, p['luma'])
    out = np.where(lum[..., None] > 1e-6,
                   out * mapped[..., None] / np.maximum(lum[..., None], 1e-12), mapped[..., None])
    out = np.clip(out, 0, 1)
    change = np.float32(np.clip(p['strength'], 1, 1.8) - 1) * (out - rgb)
    room = np.where(change >= 0, 1 - out, out)
    result = out + np.where(room > 0, change * room / np.maximum(room + abs(change), 1e-12), 0)
    return np.clip(result,0,1) if high_precision else quantize(result)


def hash_noise(x, y, seed):
    with np.errstate(over='ignore'):
        v = x.astype(np.uint32) * np.uint32(521288629) + y.astype(np.uint32) * np.uint32(1597334677) + np.uint32((seed * 1821285621) & 0xffffffff)
        v = (v ^ (v >> 16)) * np.uint32(2146121005)
        v = (v ^ (v >> 15)) * np.uint32(2221713035)
    return ((v ^ (v >> 16)) & np.uint32(16777215)).astype(np.float32) / np.float32(8388607.5) - np.float32(1)


def noise(x, y, seed, size, roughness):
    scale = np.float32(max(0, size)/25 + 1)
    px, py = x / scale, y / scale
    ix, iy = px.astype(np.int32), py.astype(np.int32)
    fx, fy = px - ix, py - iy
    fx, fy = fx.astype(np.float32), fy.astype(np.float32)
    smooth = (hash_noise(ix, iy, seed)*(1-fx) + hash_noise(ix+1, iy, seed)*fx)*(1-fy)
    smooth += (hash_noise(ix, iy+1, seed)*(1-fx) + hash_noise(ix+1, iy+1, seed)*fx)*fy
    rough = np.float32(np.clip(roughness/100, 0, .7))
    return smooth * (1-rough) + hash_noise(x, y, seed+83)*rough


def film_cpu(padded, index, y0, height, high_precision=False):
    p = CATALOG[index]
    divisor = np.float32(1 if high_precision else 255)
    rgb = padded[1:-1].astype(np.float32) / divisor
    lum_all = padded.astype(np.float32) @ LUMA / divisor
    # [1 2 1] outer product, replicate edge, exactly the APK's 3x3 blur.
    vertical = (lum_all[:-2] + 2*lum_all[1:-1] + lum_all[2:]) / np.float32(4)
    edge = np.pad(vertical, ((0, 0), (1, 1)), mode='edge')
    blurred = (edge[:, :-2] + 2*edge[:, 1:-1] + edge[:, 2:]) / np.float32(4)
    lum = rgb @ LUMA
    clarity = (lum - blurred) * np.float32(np.clip(p['clarity'], -20, 0)/100)
    width = rgb.shape[1]
    x = np.arange(width, dtype=np.float32)[None, :]
    y = np.arange(y0, y0+rgb.shape[0], dtype=np.float32)[:, None]
    nx, ny = ((2*x+1)-width)/max(1, width), ((2*y+1)-height)/max(1, height)
    mid = np.float32(np.clip(p['midpoint']/100, 0, .85))
    radius = np.clip(((nx*nx+ny*ny)*.5-mid)/(1-mid), 0, 1)
    vignette = np.power(np.float32(2), np.float32(np.clip(p['vignette']/100, -1.25, 1.25))*radius*radius*(3-2*radius))
    level = np.where(lum < .5, p['shadows']+(p['midtones']-p['shadows'])*lum*2,
                     p['midtones']+(p['highlights']-p['midtones'])*(lum*2-1))
    amp = np.float32(np.clip(p['grain'], 0, 100)/100) * np.maximum(0, level)/100*np.float32(.06)
    grain = noise(x, y, index, p['grainSize'], p['roughness'])*amp
    out = (rgb + clarity[..., None])*vignette[..., None] + grain[..., None]
    if p['colorVariation']:
        for c in range(3):
            out[..., c] += noise(x, y, index+c+1, p['grainSize'], p['roughness'])*amp*np.float32(np.clip(p['colorVariation']/100, 0, 1))
    return np.clip(out,0,1) if high_precision else quantize(out)


class Cancelled(Exception):
    pass


class Renderer:
    def __init__(self, backend='auto'):
        self.backend = backend
        self.gpu = None
        self.m9 = None
        self.m3 = None
        self.input_quality = None
        self._photo = None
        self._prepared_input = None
        self._cpu_pool=None
        self._cpu_pool_size=0
        self.last_report = {}
        self._defer_protect=False
        self._preview_reference=None
        self.fallback_reason = ''
        if backend != 'cpu':
            try:
                if sys.platform == 'darwin':
                    import os
                    if os.environ.get('CAMERALOOK_METAL', '1') == '0':
                        raise RuntimeError('Metal 已通过 CAMERALOOK_METAL=0 关闭')
                    from metal_renderer import MetalRenderer
                    self.gpu = MetalRenderer()
                else:
                    from gpu import GpuRenderer
                    self.gpu = GpuRenderer()
            except Exception as exc:
                self.fallback_reason = str(exc)
                if backend == 'gpu':
                    raise RuntimeError(f'GPU 初始化失败：{exc}。可选择 CPU 模式。') from exc
        self.name = f'GPU · {self.gpu.name}' if self.gpu else 'CPU · NumPy'

    def close(self):
        if self._cpu_pool is not None:
            self._cpu_pool.shutdown(wait=True,cancel_futures=True)
            self._cpu_pool=None;self._cpu_pool_size=0
        self.end_photo()
        if self.gpu:
            self.gpu.close()
            self.gpu = None
        if self.m9:
            self.m9.close()
            self.m9 = None
        if self.m3:
            self.m3.close()
            self.m3 = None
        if self.input_quality:self.input_quality.close()
        self.input_quality = None

    def begin_photo(self,image):
        """Bound the shared input preparation cache to one batch photo."""
        self._photo=image
        self._prepared_input=None
        if self.gpu:self.gpu.clear_photo()

    def end_photo(self):
        self._prepared_input=None
        self._photo=None
        if self.gpu:self.gpu.clear_photo()

    def render(self, image, index, strength=1.0, progress=None, cancelled=None):
        scope=getattr(self.gpu,'render_scope',None)
        if scope:
            with scope():
                return self._render_photo(image,index,strength,progress,cancelled)
        return self._render_photo(image,index,strength,progress,cancelled)

    def _render_photo(self, image, index, strength=1.0, progress=None, cancelled=None):
        if index<0 or strength<=0:return image.copy()
        started=time.perf_counter();cache_hit=False
        source=image
        if 0<=index<23:
            from desktop_post import ImageRuntime
            from PIL import Image
            if self._photo is source and self._prepared_input is not None:
                cache_hit=True
                image=self._prepared_input
            else:
                if self.input_quality is None:self.input_quality=ImageRuntime()
                rgb=np.asarray(image.convert('RGB'))
                denoise=getattr(self.gpu,'input_denoise',None)
                denoised=denoise(rgb,2,cancelled) if denoise else self.input_quality.output_denoise(rgb,2,cancelled)
                image=Image.fromarray(denoised)
                image.info.update(source.info)
                if 'rgb_float' in source.info:
                    delta=(denoised.astype(np.float32)-rgb.astype(np.float32))/255
                    image.info['rgb_float']=np.clip(source.info['rgb_float']+delta,0,1)
                if self._photo is source:self._prepared_input=image
        quality_backend=(self.gpu.name if getattr(self.gpu,'input_denoise',None) else self.input_quality.name) if 0<=index<23 else ''
        prepared_at=time.perf_counter()
        if self._defer_protect:self._preview_reference=image
        result=self._render_selected(image,index,strength,progress,cancelled)
        result.info['hdr_max']=1.8 if index==25 else 2.
        result.info['is_raw']=bool(source.info.get('is_raw'))
        from hdr import protect
        if not self._defer_protect:result=protect(result,result.info['is_raw'])
        if 0<=index<23:
            finished=time.perf_counter()
            self.last_report={'seconds':round(finished-started,4),'input_seconds':round(prepared_at-started,4),
                              'filter_seconds':round(finished-prepared_at,4),'input_backend':quality_backend,
                              'input_cache_hit':cache_hit,
                              'gpu_resident':bool(self.gpu and __import__('os').environ.get('CAMERALOOK_LEGACY_GPU')!='1'),
                              'gpu_photo_cache_hit':bool(self.gpu and self.gpu.photo_cache_hit and 'rgb_float' not in image.info and not image.info.get('high_precision')),
                              'gpu_photo_uploads':self.gpu.photo_uploads if self.gpu else 0}
        return result

    def preview_base(self,image,index,cancelled=None):
        """Retain the pre-protection, pre-strength result and its exact reference."""
        self._defer_protect=True
        try:
            base=self.render(image,index,1.,cancelled=cancelled)
            reference=self._preview_reference or image
            return base,reference,index,self.name
        finally:self._defer_protect=False;self._preview_reference=None

    @staticmethod
    def compose_preview(payload,strength):
        from PIL import Image
        from hdr import protect
        base,reference,index,_=payload
        if strength==1:result=base.copy()
        elif 'rgb_float' in base.info:
            source=reference.info.get('rgb_float')
            if source is None:source=np.asarray(reference,np.float32)/255
            values=np.clip(source+(base.info['rgb_float']-source)*np.float32(strength),0,1)
            result=Image.fromarray(np.rint(values*255).astype(np.uint8))
            result.info.update(base.info);result.info['rgb_float']=values
        else:
            pixels=blend_original(np.asarray(base),np.asarray(reference),strength,round_half=index<23)
            result=Image.fromarray(pixels);result.info.update(base.info)
        return protect(result,bool(base.info.get('is_raw')))

    def can_prepare(self,index,image=None):
        if index not in (23,24,26) or self.gpu is None:return False
        import os
        if os.environ.get('CAMERALOOK_PIPELINE_PREPARE')=='0':return False
        if os.environ.get('CAMERALOOK_GPU_PREPARE')=='1' or os.environ.get('CAMERALOOK_ARM_REFERENCE')=='1':return False
        if image is not None and 'rgb_float' in image.info:return False
        return True

    def prepare_photo(self,image,index,cancelled=None):
        # The worker owns its CPU runtime. It never creates/uses self.m9 or GL.
        from m9 import prepare_cpu_frame
        prep=prepare_cpu_frame(image,index,cancelled)
        prep.update(image=image,index=index)
        return prep

    def render_prepared(self,prep,strength=1.0,progress=None,cancelled=None):
        from m9 import M9Renderer
        if strength<=0:return prep['image'].copy()
        if self.m9 is None:self.m9=M9Renderer(self.backend,gpu=self.gpu)
        try:
            result=self.m9.render_prepared(prep,strength,progress,cancelled)
        except Cancelled:raise
        except Exception:
            if self.backend!='auto':raise
            # Re-enter the existing provider fallback, preserving its diagnostics.
            return self.render(prep['image'],prep['index'],strength,progress,cancelled)
        self.name=self.m9.name
        result.info.update(hdr_max=2.,is_raw=bool(prep['image'].info.get('is_raw')))
        from hdr import protect
        return protect(result,result.info['is_raw'])

    def _render_selected(self, image, index, strength=1.0, progress=None, cancelled=None):
        if index==25:
            from m3 import M3Renderer
            if strength<=0:return image.convert('RGB').copy()
            if self.m3 is None:self.m3=M3Renderer()
            try:
                result=self.m3.render(image,strength,self.gpu,progress,cancelled)
            except Cancelled:raise
            except Exception as exc:
                if self.backend!='auto' or self.gpu is None:raise
                self.fallback_reason=f'M3 GPU 失败，回退 CPU：{exc}'
                self.gpu.close();self.gpu=None
                result=self.m3.render(image,strength,None,progress,cancelled)
            self.name=('GPU · Monopan Metal ＋ CPU 原生 M3' if getattr(self.gpu,'monopan_grain',None) else 'GPU · Monopan OpenGL ＋ CPU 原生 M3' if self.gpu else 'CPU · 原生 M3 ＋ Monopan NumPy')
            return result
        if index>=23:
            from m9 import M9Renderer,EXPERIMENTS
            if index not in (23,24,26):
                raise ValueError('未知滤镜')
            if strength<=0:
                return image.convert('RGB').copy()
            try:
                if self.m9 is None:
                    self.m9 = M9Renderer(self.backend,gpu=self.gpu)
                result = self.m9.render(image,EXPERIMENTS[index-23]['model'],strength,progress,cancelled)
            except Cancelled:
                raise
            except Exception as exc:
                if self.backend!='auto' or (self.m9 and self.m9.provider=='CPUExecutionProvider'):
                    raise
                retry_directml=bool(self.m9 and self.m9.provider=='nv_tensorrt_rtx')
                self.fallback_reason = f'M9 GPU 失败，改用 '+('DirectML' if retry_directml else 'CPU')+f'：{exc}'
                if self.m9:
                    self.m9.close()
                self.m9 = M9Renderer('gpu' if retry_directml else 'cpu',gpu=self.gpu)
                try:result = self.m9.render(image,EXPERIMENTS[index-23]['model'],strength,progress,cancelled)
                except Cancelled:raise
                except Exception as fallback_exc:
                    if not retry_directml:raise
                    self.fallback_reason+=f'；DirectML 失败，回退 CPU：{fallback_exc}'
                    self.m9.close();self.m9=M9Renderer('cpu')
                    result=self.m9.render(image,EXPERIMENTS[index-23]['model'],strength,progress,cancelled)
            self.name = self.m9.name
            return result
        try:
            if 'rgb_float' in image.info or image.info.get('high_precision'):
                from precision import render_float
                return render_float(self,image,index,strength,progress,cancelled)
            return self._render(image, index, strength, progress, cancelled)
        except Cancelled:
            raise
        except Exception as exc:
            if self.backend != 'auto' or self.gpu is None:
                raise
            self.fallback_reason = f'GPU 运行失败，改用 CPU：{exc}'
            self.close()
            self.name = 'CPU · NumPy'
            if 'rgb_float' in image.info or image.info.get('high_precision'):
                from precision import render_float
                return render_float(self,image,index,strength,progress,cancelled)
            return self._render(image, index, strength, progress, cancelled)

    def _render(self, image, index, strength=1.0, progress=None, cancelled=None):
        self.name = f'GPU · {self.gpu.name}' if self.gpu else 'CPU · NumPy'
        original = np.asarray(image.convert('RGB'))
        if index < 0 or strength <= 0:
            return image.convert('RGB').copy()
        h, w = original.shape[:2]
        if self.gpu and __import__('os').environ.get('CAMERALOOK_LEGACY_GPU')!='1':
            result=np.empty_like(original)
            rows=h if getattr(self.gpu,'whole_image',False) else max(1,min(256,750000//max(1,w)))
            cached=self.gpu.cache_photo(original,image)
            for y0 in range(0,h,rows):
                if cancelled and cancelled():raise Cancelled()
                y1=min(h,y0+rows)
                padded=None if cached else original[np.clip(np.arange(y0-1,y1+1),0,h-1)].astype(np.float32)/np.float32(255)
                result[y0:y1]=self.gpu.tone_film(padded,index,y0,h,cached=cached,out_rows=y1-y0)
                if strength!=1:
                    result[y0:y1]=blend_original(result[y0:y1],original[y0:y1],strength)
                if progress:progress(y1/h)
            from PIL import Image
            return Image.fromarray(result)
        toned = np.empty_like(original)
        result = np.empty_like(original)
        # Bound temporary arrays for 48/100 megapixel input.
        rows = max(1, min(256, (750000 if self.gpu else 150000) // max(1, w)))
        bands=[(y,min(h,y+rows)) for y in range(0,h,rows)]
        workers=min(cpu_workers(),len(bands)) if self.gpu is None else 1
        if workers>1:
            from concurrent.futures import ThreadPoolExecutor,wait,FIRST_COMPLETED
            if self._cpu_pool_size!=workers:
                if self._cpu_pool is not None:self._cpu_pool.shutdown(wait=True,cancel_futures=True)
                self._cpu_pool=ThreadPoolExecutor(workers,thread_name_prefix='LUT-cpu')
                self._cpu_pool_size=workers
            def execute(fn,offset):
                iterator=iter(bands);pending={};completed=0
                def submit():
                    band=next(iterator,None)
                    if band is not None:pending[self._cpu_pool.submit(fn,band)]=band
                for _ in range(workers):submit()
                try:
                    while pending:
                        if cancelled and cancelled():raise Cancelled()
                        ready,_=wait(pending,return_when=FIRST_COMPLETED)
                        for future in ready:
                            y0,y1=pending.pop(future);future.result();completed+=y1-y0
                            if progress:progress(offset+.5*completed/h)
                            submit()
                finally:
                    for future in pending:future.cancel()
                    if pending:wait(pending)
            def tone_band(band):
                if cancelled and cancelled():raise Cancelled()
                y0,y1=band
                toned[y0:y1]=tone_cpu(original[y0:y1].astype(np.float32)/np.float32(255),index)
            def film_band(band):
                if cancelled and cancelled():raise Cancelled()
                y0,y1=band
                result[y0:y1]=film_cpu(toned[np.clip(np.arange(y0-1,y1+1),0,h-1)],index,y0,h)
                if strength!=1:result[y0:y1]=blend_original(result[y0:y1],original[y0:y1],strength)
            execute(tone_band,0.)
            execute(film_band,.5)
            from PIL import Image
            return Image.fromarray(result)
        for y0 in range(0, h, rows):
            if cancelled and cancelled():
                raise Cancelled()
            strip = original[y0:y0+rows].astype(np.float32)/np.float32(255)
            toned[y0:y0+rows] = self.gpu.tone(strip, index) if self.gpu else tone_cpu(strip, index)
            if progress:
                progress(.5*min(h, y0+rows)/h)
        for y0 in range(0, h, rows):
            if cancelled and cancelled():
                raise Cancelled()
            y1 = min(h, y0+rows)
            padded = toned[np.clip(np.arange(y0-1, y1+1), 0, h-1)]
            result[y0:y1] = self.gpu.film(padded, index, y0, h) if self.gpu else film_cpu(padded, index, y0, h)
            if strength != 1:
                result[y0:y1] = blend_original(result[y0:y1],original[y0:y1],strength)
            if progress:
                progress(.5+.5*y1/h)
        from PIL import Image
        return Image.fromarray(result)
