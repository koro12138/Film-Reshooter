"""Windows x64 M3 guard, retaining the original ARM implementation as an oracle."""
import ctypes
import native_lib
from functools import lru_cache
import os
import numpy as np
from engine import ROOT,Cancelled

@lru_cache(maxsize=1)
def library():
    lib=native_lib.load('cameralook_m3')
    lib.cl_m3_guard.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,
                             ctypes.c_int,ctypes.c_int,ctypes.c_void_p]
    lib.cl_m3_guard.restype=ctypes.c_int
    try:
        lib.cl_m3_guard_step.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,
                                      ctypes.c_int,ctypes.c_int,ctypes.c_void_p,ctypes.c_int]
        lib.cl_m3_guard_step.restype=ctypes.c_int
    except AttributeError:
        pass
    if hasattr(lib,'cl_m3_guard_rgb'):
        lib.cl_m3_guard_rgb.argtypes=lib.cl_m3_guard.argtypes
        lib.cl_m3_guard_rgb.restype=ctypes.c_int
    return lib

class GuardRuntime:
    def __init__(self):
        self.reference=None
        self.last_report={}
        try:
            if os.environ.get('CAMERALOOK_ARM_REFERENCE')=='1' or os.environ.get('CAMERALOOK_ARM_M3_GUARD')=='1':
                raise OSError('ARM guard requested')
            library();self.name=native_lib.backend_name()
        except (OSError,AttributeError):
            self.name='ARM reference'

    @property
    def heap_capacity(self):
        return self.reference.heap_capacity if self.reference else 0

    def quality_guard(self,source,processed,grade=False,cancelled=None,*,inplace=False):
        if cancelled and cancelled():raise Cancelled()
        src=np.asarray(source)
        dst=np.asarray(processed)
        if src.dtype!=np.uint8 or dst.dtype!=np.uint8 or src.ndim!=3 or src.shape[2]!=3 or src.shape!=dst.shape:
            raise ValueError('M3 guard expects matching uint8 RGB images')
        h,w=src.shape[:2]
        if w<1 or h<1 or w>32768 or h>32768 or w*h>80000000:
            raise ValueError('M3 guard dimensions exceed original limits')
        if self.name=='ARM reference':
            required=w*h*8+min(w*h,2048*2048)*32+32*1024*1024
            if self.reference is None or self.reference.heap_capacity<required:
                self.close()
                from native_runtime import NativeImageRuntime
                self.reference=NativeImageRuntime('libzxicamodelembed.so',heap_bytes=required)
            self.last_report={'backend':self.name}
            return self.reference.quality_guard(src,dst,grade,cancelled)
        if getattr(library(),'cl_m3_guard_step',None) is not None:
            out=dst if inplace and dst.flags.c_contiguous and dst.flags.writeable else np.array(dst,copy=True,order='C')
            counts=np.zeros(2,np.uint64)
            if not library().cl_m3_guard_step(np.ascontiguousarray(src).ctypes.data,out.ctypes.data,
                                              w,h,int(grade),counts.ctypes.data,3):
                raise RuntimeError('M3 desktop guard failed')
            if cancelled and cancelled():raise Cancelled()
            self.last_report={'backend':self.name,'detected_pixels':int(counts[0]),'active_pixels':int(counts[1]),
                              'staging':'packed RGB'}
            return out
        if hasattr(library(),'cl_m3_guard_rgb'):
            out=dst if inplace and dst.flags.c_contiguous and dst.flags.writeable else np.array(dst,copy=True,order='C')
            counts=np.zeros(2,np.uint64)
            if not library().cl_m3_guard_rgb(np.ascontiguousarray(src).ctypes.data,out.ctypes.data,w,h,int(grade),counts.ctypes.data):
                raise RuntimeError('M3 desktop RGB guard failed')
            if cancelled and cancelled():raise Cancelled()
            self.last_report={'backend':self.name,'detected_pixels':int(counts[0]),'active_pixels':int(counts[1]),'staging':'packed RGB'}
            return out
        rgba=np.full((h,w,4),255,np.uint8);rgba[...,:3]=src
        out=np.empty_like(rgba);out[...,:3]=dst;out[...,3]=255
        counts=np.zeros(2,np.uint64)
        if not library().cl_m3_guard(rgba.ctypes.data,out.ctypes.data,w,h,int(grade),counts.ctypes.data):
            raise RuntimeError('M3 desktop guard failed')
        if cancelled and cancelled():raise Cancelled()
        self.last_report={'backend':self.name,'detected_pixels':int(counts[0]),'active_pixels':int(counts[1]),
                          'staging':'RGBA'}
        return out[...,:3].copy()

    def close(self):
        if self.reference:self.reference.close()
        self.reference=None
