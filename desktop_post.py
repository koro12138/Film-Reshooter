"""Windows x64 implementations, with ARM reference fallback if unavailable."""
import ctypes
import native_lib
import os
from functools import lru_cache
import numpy as np
from engine import ROOT,Cancelled

@lru_cache(maxsize=1)
def library():
    lib=native_lib.load('cameralook_post')
    lib.cl_denoise.argtypes=[ctypes.c_void_p,ctypes.c_int,ctypes.c_int,ctypes.c_int]
    lib.cl_denoise.restype=ctypes.c_int
    lib.cl_scene.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,ctypes.c_int,
                          ctypes.c_int,ctypes.c_int,ctypes.c_void_p,ctypes.c_void_p]
    lib.cl_scene.restype=None
    lib.cl_texture.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,ctypes.c_int]
    lib.cl_texture.restype=ctypes.c_int
    lib.cl_output_denoise.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,ctypes.c_int,ctypes.c_int]
    lib.cl_output_denoise.restype=ctypes.c_int
    return lib

def denoise(image,finish=False,cancelled=None):
    if cancelled and cancelled():raise Cancelled()
    out=np.array(image,dtype=np.uint8,order='C',copy=True)
    h,w=out.shape[:2]
    if out.ndim!=3 or out.shape[2]!=3:raise ValueError('Expected RGB image')
    # The original library leaves unsupported dimensions unchanged.
    if w<2 or h<2 or w>16384 or h>16384:return out
    if not library().cl_denoise(out.ctypes.data,w,h,int(finish)):
        raise RuntimeError('Desktop denoise failed')
    if cancelled and cancelled():raise Cancelled()
    return out

def scene(image,lut,shade,cancelled=None):
    from PIL import Image
    src=np.ascontiguousarray(image,dtype=np.uint8)
    lut=np.ascontiguousarray(lut,dtype=np.uint8)
    shade=np.ascontiguousarray(shade,dtype=np.float32)
    if src.ndim!=3 or src.shape[2]!=3 or lut.shape!=(17,17,17,3) or shade.shape!=(8,):
        raise ValueError('Invalid scene inputs')
    out=np.empty_like(src);h,w=src.shape[:2]
    fn=library().cl_scene
    for top in range(0,h,128):
        if cancelled and cancelled():raise Cancelled()
        fn(src.ctypes.data,out.ctypes.data,w,h,top,min(h,top+128),lut.ctypes.data,shade.ctypes.data)
    return Image.fromarray(out)

def texture(source,processed,cancelled=None):
    if cancelled and cancelled():raise Cancelled()
    src=np.ascontiguousarray(source,dtype=np.uint8)
    out=np.array(processed,dtype=np.uint8,order='C',copy=True)
    if src.ndim!=3 or src.shape[2]!=3 or out.shape!=src.shape:raise ValueError('Texture dimensions')
    h,w=src.shape[:2]
    if not library().cl_texture(src.ctypes.data,out.ctypes.data,w,h):raise RuntimeError('Desktop texture failed')
    if cancelled and cancelled():raise Cancelled()
    return out

def output_denoise(image,style=2,cancelled=None):
    if cancelled and cancelled():raise Cancelled()
    src=np.ascontiguousarray(image,dtype=np.uint8)
    if src.ndim!=3 or src.shape[2]!=3:raise ValueError('Expected RGB image')
    out=src.copy();h,w=src.shape[:2]
    if not library().cl_output_denoise(src.ctypes.data,out.ctypes.data,w,h,int(style)):
        raise RuntimeError('Desktop output denoise failed')
    if cancelled and cancelled():raise Cancelled()
    return out

class DenoiseRuntime:
    def __init__(self):
        self.reference=None
        try:
            if os.environ.get('CAMERALOOK_ARM_REFERENCE')=='1':raise OSError('Reference requested')
            library()
            self.name=native_lib.backend_name()
        except OSError:
            from native_runtime import NativeImageRuntime
            self.reference=NativeImageRuntime('libleicadenoise.so')
            self.name='ARM reference'

    def denoise(self,image,finish=False,cancelled=None):
        if self.reference:return self.reference.denoise(image,finish,cancelled)
        return denoise(image,finish,cancelled)

    def scene(self,image,lut,shade,cancelled=None):
        if self.reference:
            from leica_params import apply
            return apply(image,lut,shade,cancelled)
        return scene(image,lut,shade,cancelled)

    def close(self):
        if self.reference:self.reference.close()

class ImageRuntime:
    """Shared desktop texture/output routines with the original ARM fallback."""
    def __init__(self):
        self.reference=None
        try:
            if os.environ.get('CAMERALOOK_ARM_REFERENCE')=='1':raise OSError('Reference requested')
            library();self.name=native_lib.backend_name()
        except OSError:
            from native_runtime import NativeImageRuntime
            self.reference=NativeImageRuntime();self.name='ARM reference'

    def texture(self,source,processed,cancelled=None):
        if self.reference:return self.reference.texture(source,processed,cancelled)
        return texture(source,processed,cancelled)

    def output_denoise(self,image,style=2,cancelled=None):
        if self.reference:
            r=self.reference;r.reset();b=r.bitmap(image)
            r.call('Java_com_codex_fullm9_NativeM9_outputDenoise',r.env,0,b,style,cancelled=cancelled)
            return r.read_bitmap(b)
        return output_denoise(image,style,cancelled)

    def close(self):
        if self.reference:self.reference.close()
