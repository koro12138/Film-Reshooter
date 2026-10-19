"""Exact native M3 preparation and fixed-parameter base, with an ARM oracle."""
import ctypes
import native_lib
from functools import lru_cache
from pathlib import Path
import hashlib,os,time
import numpy as np
from engine import ROOT,Cancelled

PARAM_HASH='6e9217ee8c59872a3d700614681c30742df01d9bc9b44b7f2a170eeaab68052b'


def _worker_cap():
    """Upper bound for the native base split: 4 left 8-16 core hosts idle."""
    override=os.environ.get('CAMERALOOK_M3_WORKERS')
    if override:
        try:return max(1,min(16,int(override)))
        except ValueError:pass
    return 8

@lru_cache(maxsize=1)
def library():
    lib=native_lib.load('cameralook_m3_core')
    lib.cl_m3_core_version.restype=ctypes.c_int
    if lib.cl_m3_core_version()!=1:raise OSError('M3 native core version mismatch')
    lib.cl_m3_prepare.argtypes=[ctypes.c_void_p,ctypes.c_int,ctypes.c_int,ctypes.c_int]
    lib.cl_m3_prepare.restype=ctypes.c_int
    lib.cl_m3_base.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int,ctypes.c_int,
                            ctypes.c_int,ctypes.c_int,ctypes.c_void_p]
    lib.cl_m3_base.restype=ctypes.c_int
    return lib

class CoreRuntime:
    def __init__(self):
        self.available=False;self.fallback_reason='';self.pool=None;self.pool_size=0
        self.workers=1;self.worker_reports=[]
        try:
            if os.environ.get('CAMERALOOK_ARM_REFERENCE')=='1' or os.environ.get('CAMERALOOK_ARM_M3_CORE')=='1':
                raise OSError('ARM M3 core requested for comparison')
            raw=(ROOT/'assets/leica_filter_param_m3.bin').read_bytes()
            if hashlib.sha256(raw).hexdigest()!=PARAM_HASH:raise OSError('Unsupported M3 parameter resource')
            self.lib=library()
            from leica_params import parameters
            self.shade=np.ascontiguousarray(parameters('leica_filter_param_m3.bin').shading(1,200,5500),dtype=np.float32)
            self.available=True
        except (OSError,AttributeError) as exc:self.fallback_reason=str(exc)

    def validate(self,image):
        src=np.asarray(image)
        if src.dtype!=np.uint8 or src.ndim!=3 or src.shape[2]!=3:raise ValueError('M3 core expects uint8 RGB')
        h,w=src.shape[:2]
        if w<1 or h<1 or w>32768 or h>32768 or w*h>80000000:raise ValueError('M3 core dimensions exceed limits')
        return np.ascontiguousarray(src)

    def prepare(self,image,cancelled=None):
        if cancelled and cancelled():raise Cancelled()
        out=self.validate(image).copy();h,w=out.shape[:2]
        if 2<=w<=16384 and 2<=h<=16384:
            if not self.lib.cl_m3_prepare(out.ctypes.data,w,h,0):raise RuntimeError('M3 native preparation failed')
        if cancelled and cancelled():raise Cancelled()
        return out

    def base(self,image,cancelled=None):
        if cancelled and cancelled():raise Cancelled()
        src=self.validate(image);h,w=src.shape[:2];out=np.empty_like(src)
        workers=min(_worker_cap(),max(1,(os.cpu_count() or 1)//2),max(1,h//128))
        if (w*h<2000000 and os.environ.get('CAMERALOOK_PARALLEL_M3')!='1') or os.environ.get('CAMERALOOK_SERIAL_M3')=='1':workers=1
        self.workers=workers
        def rows(index):
            started=time.perf_counter();first,last=h*index//workers,h*(index+1)//workers
            for top in range(first,last,128):
                if cancelled and cancelled():raise Cancelled()
                if not self.lib.cl_m3_base(src.ctypes.data,out.ctypes.data,w,h,top,min(top+128,last),self.shade.ctypes.data):
                    raise RuntimeError('M3 native base failed')
            return {'backend':native_lib.backend_name(),'setup_seconds':0.,'render_seconds':round(time.perf_counter()-started,4),'heap_megabytes':0.}
        if workers==1:self.worker_reports=[rows(0)]
        else:
            if self.pool_size!=workers:
                self.close()
                from concurrent.futures import ThreadPoolExecutor
                self.pool=ThreadPoolExecutor(max_workers=workers,thread_name_prefix='M3-native')
                self.pool_size=workers
            # Wait for every writer before unwinding an error/cancellation.
            # A queued task owns references to both arrays until it completes.
            futures=[self.pool.submit(rows,i) for i in range(workers)]
            reports=[];error=None
            for future in futures:
                try:reports.append(future.result())
                except Exception as exc:
                    if error is None:error=exc
            if error is not None:raise error
            self.worker_reports=reports
        if cancelled and cancelled():raise Cancelled()
        return out

    def close(self):
        if self.pool is not None:self.pool.shutdown(wait=True,cancel_futures=True)
        self.pool=None;self.pool_size=0
