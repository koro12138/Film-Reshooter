"""NVIDIA frame packing/stitching via precompiled PTX and stable ORT pointers."""
import ctypes,threading
import numpy as np
from engine import ROOT,Cancelled


class CudaTiles:
    def __init__(self):
        self.owner=threading.get_ident();self.buffers={};self.module=ctypes.c_void_p()
        self.runtime=ctypes.CDLL(str(ROOT/'assets/nvidia_runtime/onnxruntime_ep_nv_tensorrt_rtx/cudart64_12.dll'))
        self.driver=ctypes.WinDLL('nvcuda.dll')
        P=ctypes.c_void_p;I=ctypes.c_int;S=ctypes.c_size_t
        def bind(lib,name,args):
            fn=getattr(lib,name);fn.argtypes=args;fn.restype=I;return fn
        self.malloc=bind(self.runtime,'cudaMalloc',[ctypes.POINTER(P),S])
        self.free=bind(self.runtime,'cudaFree',[P])
        self.memcpy=bind(self.runtime,'cudaMemcpy',[P,P,S,I])
        self.memset=bind(self.runtime,'cudaMemset',[P,I,S])
        self.sync=bind(self.runtime,'cudaDeviceSynchronize',[])
        self.memory=bind(self.runtime,'cudaMemGetInfo',[ctypes.POINTER(S),ctypes.POINTER(S)])
        self.load=bind(self.driver,'cuModuleLoadData',[ctypes.POINTER(P),P])
        self.unload=bind(self.driver,'cuModuleUnload',[P])
        self.get_function=bind(self.driver,'cuModuleGetFunction',[ctypes.POINTER(P),P,ctypes.c_char_p])
        self.launch_kernel=bind(self.driver,'cuLaunchKernel',[P,*([ctypes.c_uint]*7),P,ctypes.POINTER(P),P])
        self.check(self.free(None),'initialize CUDA primary context')
        data=ctypes.create_string_buffer((ROOT/'assets/native/m9_resident.ptx').read_bytes())
        self.check(self.load(ctypes.byref(self.module),data),'load M9 PTX')
        self.functions={}
        try:
            for name in ('style_bytes','pack_tiles','unpack_tiles','crop_canvas'):
                fn=P();self.check(self.get_function(ctypes.byref(fn),self.module,name.encode()),name)
                self.functions[name]=fn
        except Exception:self.close();raise

    def check(self,result,action):
        if result:raise RuntimeError(f'CUDA M9 {action}: error {result}')

    def thread(self):
        if threading.get_ident()!=self.owner:raise RuntimeError('CUDA M9 used outside its render thread')

    def buffer(self,name,size):
        self.thread();old=self.buffers.get(name)
        if old is None or old[1]<size:
            ptr=ctypes.c_void_p();self.check(self.malloc(ctypes.byref(ptr),size),'allocate '+name)
            if old:self.check(self.free(old[0]),'free '+name)
            self.buffers[name]=(ptr,size)
        return self.buffers[name][0]

    def upload(self,name,array):
        array=np.ascontiguousarray(array);ptr=self.buffer(name,array.nbytes)
        self.check(self.memcpy(ptr,array.ctypes.data,array.nbytes,1),'upload '+name)
        return ptr

    def free_memory(self):
        free=ctypes.c_size_t();total=ctypes.c_size_t()
        self.check(self.memory(ctypes.byref(free),ctypes.byref(total)),'query device memory')
        return free.value,total.value

    def launch(self,name,count,*args):
        self.thread()
        values=[ctypes.c_void_p(v) if kind=='p' else ctypes.c_int(v) for kind,v in args]
        params=(ctypes.c_void_p*len(values))(*[ctypes.cast(ctypes.byref(v),ctypes.c_void_p) for v in values])
        self.check(self.launch_kernel(self.functions[name],(count+255)//256,1,1,256,1,1,0,None,params,None),name)

    def begin(self,frame,style_device):
        self.original=self.upload('original',frame.original)
        self.styled=self.buffer('styled',768*1024*3)
        self.canvas=self.buffer('canvas',3072*4096*3)
        self.error=self.buffer('error',4)
        self.check(self.memset(self.canvas,0,3072*4096*3),'clear output')
        self.check(self.memset(self.error,0,4),'clear status')
        self.launch('style_bytes',768*1024*3,('p',style_device.data_ptr()),('p',self.styled.value),('p',self.error.value))

    def pack(self,indices,batch,device):
        if batch not in (1,2,4) or not 1<=len(indices)<=batch or any(not 0<=i<48 for i in indices):raise ValueError('M9 resident tile group')
        ids=(list(indices)+[indices[-1]]*4)[:4]
        self.launch('pack_tiles',batch*6*544*544,('p',self.original.value),('p',self.styled.value),
                    ('p',device.data_ptr()),*[('i',i) for i in ids],('i',batch))
        self.check(self.sync(),'pack completion')

    def unpack(self,indices,device):
        ids=(list(indices)+[indices[-1]]*4)[:4]
        self.launch('unpack_tiles',len(indices)*3*512*512,('p',device.data_ptr()),('p',self.canvas.value),
                    *[('i',i) for i in ids],('i',len(indices)),('p',self.error.value))

    def recover(self,frame):
        out=np.empty((frame.height,frame.width,3),np.uint8)
        target=self.buffer('crop',out.nbytes)
        self.launch('crop_canvas',out.size,('p',self.canvas.value),('p',target.value),
                    ('i',frame.left),('i',frame.top),('i',frame.width),('i',frame.height))
        self.check(self.sync(),'output completion')
        error=np.zeros(1,np.int32)
        self.check(self.memcpy(error.ctypes.data,self.error,4,2),'read status')
        if error[0]:raise RuntimeError('M9 网络输出出现非有限值')
        self.check(self.memcpy(out.ctypes.data,target,out.nbytes,2),'read merged output')
        return out

    def close(self):
        self.thread()
        # Complete all kernels before buffers or module can be released.
        self.sync()
        for ptr,_ in self.buffers.values():self.free(ptr)
        self.buffers.clear()
        if self.module.value:self.unload(self.module);self.module=ctypes.c_void_p()
