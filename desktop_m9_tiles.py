"""Optional M9 native frame packing with NumPy fallback at the call site."""
import ctypes
import native_lib
from functools import lru_cache
from engine import ROOT

@lru_cache(maxsize=1)
def library():
    lib=native_lib.load('cameralook_m9_tiles')
    lib.cl_m9_tiles_version.restype=ctypes.c_int
    if lib.cl_m9_tiles_version()!=2:raise OSError('M9 tile library version mismatch')
    lib.cl_m9_pack.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,ctypes.c_void_p]
    lib.cl_m9_pack.restype=ctypes.c_int
    lib.cl_m9_unpack.argtypes=[ctypes.c_void_p,ctypes.c_int,ctypes.c_void_p]
    lib.cl_m9_unpack.restype=ctypes.c_int
    lib.cl_m9_frame.argtypes=[ctypes.c_void_p,ctypes.c_int,ctypes.c_int,ctypes.c_void_p,
                              ctypes.c_void_p,ctypes.c_void_p]
    lib.cl_m9_frame.restype=ctypes.c_int
    lib.cl_m9_reduce.argtypes=[ctypes.c_void_p,ctypes.c_void_p]
    lib.cl_m9_reduce.restype=ctypes.c_int
    return lib
