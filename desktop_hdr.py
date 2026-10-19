"""Windows x64 HDR gain-map sample, with the ARM interpreter as reference fallback."""
import ctypes
import native_lib
from functools import lru_cache
import numpy as np
from engine import ROOT

@lru_cache(maxsize=1)
def library():
    lib=native_lib.load('cameralook_hdr')
    lib.cl_hdr_version.restype=ctypes.c_int
    if lib.cl_hdr_version() not in (1,2):raise OSError('HDR sample library version mismatch')
    lib.cl_hdr_sample.argtypes=[ctypes.c_void_p,ctypes.c_int,ctypes.c_int,ctypes.c_int,
                               ctypes.c_int,ctypes.c_int,ctypes.c_int,ctypes.c_void_p]
    lib.cl_hdr_sample.restype=ctypes.c_int
    return lib

def available():
    try:
        library()
        return True
    except (OSError,AttributeError):
        return False

def sample(rgb,width,height):
    """Area-weighted Rec.709 luma downscale; returns a (height,width) uint8 plane."""
    src=np.asarray(rgb)
    if src.dtype!=np.uint8 or src.ndim!=3 or src.shape[2] not in (3,4):raise ValueError('Expected uint8 RGB/RGBA image')
    src=np.ascontiguousarray(src)
    h,w=src.shape[:2]
    if width<1 or height<1 or width>384 or height>384 or w<width or h<height:
        raise ValueError('Unsupported HDR sample geometry')
    step=src.shape[2]
    out=np.zeros((height,width),np.uint8)
    if not library().cl_hdr_sample(src.ctypes.data,w,h,w*step,step,width,height,out.ctypes.data):
        raise RuntimeError('Desktop HDR sample failed')
    return out


def pack(rgb,gain,linear_table):
    """Exact sRGB-LUT/float32 multiply/binary16 pack, without full float RGB copies."""
    source=np.asarray(rgb)
    if source.dtype!=np.uint8 or source.ndim!=3 or source.shape[2] not in (3,4):raise ValueError('Expected uint8 RGB/RGBA')
    source=np.ascontiguousarray(source)
    field=np.ascontiguousarray(gain,dtype=np.float32);table=np.ascontiguousarray(linear_table,dtype=np.float32)
    if field.shape!=source.shape[:2] or table.shape!=(256,):raise ValueError('HDR pack dimensions')
    h,w=field.shape;out=np.empty((h,w,4),np.float16)
    function=library().cl_hdr_pack_u8
    function.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,ctypes.c_int,ctypes.c_int,ctypes.c_void_p]
    function.restype=ctypes.c_int
    if not function(source.ctypes.data,field.ctypes.data,table.ctypes.data,w,h,source.shape[2],out.ctypes.data):raise RuntimeError('HDR native pack failed')
    return out


def protect_rgb(rgb):
    """Night-highlight shoulder for an 8-bit HxWx3 array; returns a new array.

    Same float32 arithmetic as the Python reference in `hdr.protect`, so the
    result is bit-identical; raises if the native core is unavailable so the
    caller can fall back to the reference implementation.
    """
    rgb = np.ascontiguousarray(rgb)
    if rgb.ndim != 3 or rgb.shape[2] != 3 or rgb.dtype != np.uint8:
        raise ValueError('protect_rgb expects uint8 HxWx3')
    height, width = rgb.shape[:2]
    dst = np.empty_like(rgb)
    lib = library()
    if not hasattr(lib,'cl_hdr_protect'):
        raise OSError('Native highlight protection is unavailable')
    lib.cl_hdr_protect.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,ctypes.c_int,ctypes.c_int]
    lib.cl_hdr_protect.restype=ctypes.c_int
    ok = lib.cl_hdr_protect(rgb.ctypes.data_as(ctypes.c_void_p),
                            dst.ctypes.data_as(ctypes.c_void_p),
                            width, height, width * 3)
    if not ok:
        raise OSError('cl_hdr_protect rejected the frame')
    return dst
