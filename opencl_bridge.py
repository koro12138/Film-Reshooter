"""Explicit OpenCL ABI adapter for the APK's isolated Monopan image routines.

Emulated pointers are copied across the boundary. Transfers are synchronized;
no native callback or filesystem API is exposed to the ARM code.
"""
import ctypes as C
import struct

P=C.c_void_p
U=C.c_uint
I=C.c_int
Z=C.c_size_t
Q=C.c_ulonglong


class OpenCLBridge:
    def __init__(self,runtime):
        self.runtime=runtime
        self.lib=C.WinDLL('OpenCL.dll')
        self.keep=[]
        self.mapped={}
        self.calls={}

    def invoke(self,name,types,args,result=I):
        fn=getattr(self.lib,name)
        fn.argtypes=types;fn.restype=result
        return fn(*args)

    def read(self,p,n):
        return bytes(self.runtime.uc.mem_read(p,n)) if p and n else bytes(n)

    def write(self,p,data):
        if p and data:self.runtime.uc.mem_write(p,bytes(data))

    def array(self,p,count):
        return (Z*count).from_buffer_copy(self.read(p,count*8)) if p else None

    def error(self,p,code): self.write(p,struct.pack('<i',code))

    def call(self,name,a):
        self.calls[name]=self.calls.get(name,0)+1
        r=self.runtime
        if name=='clGetDeviceImageInfoQCOM':
            self.write(a[6],bytes(a[5]))
            self.write(a[7],struct.pack('<Q',a[5]));return 0
        if name in ('clGetExtensionFunctionAddressForPlatform','clGetExtensionFunctionAddress'):
            return 0
        if name in ('clGetPlatformIDs','clGetDeviceIDs'):
            device=name=='clGetDeviceIDs'
            count=a[2] if device else a[0]
            ptr=a[3] if device else a[1]
            countptr=a[4] if device else a[2]
            values=(P*max(1,count))();n=U()
            code=self.invoke(name,[P,Q,U,P,P] if device else [U,P,P],
                [a[0],a[1],count,values if ptr else None,C.byref(n)] if device else [count,values if ptr else None,C.byref(n)])
            if ptr and count:self.write(ptr,bytes(values)[:count*8])
            self.write(countptr,struct.pack('<I',n.value));return code
        if name in ('clGetPlatformInfo','clGetDeviceInfo','clGetContextInfo','clGetCommandQueueInfo','clGetMemObjectInfo','clGetEventInfo','clGetProgramInfo','clGetProgramBuildInfo','clGetKernelWorkGroupInfo','clGetKernelInfo'):
            if name=='clGetDeviceInfo' and a[1]==0x102b:
                # The original runtime dispatches only Adreno/Mali kernels by
                # device name. Select its portable Mali buffer-kernel branch;
                # actual execution and diagnostics still identify the PC GPU.
                value=b'Adreno (TM) 740\0'
                self.write(a[4],struct.pack('<Q',len(value)))
                if a[3] and a[2]>=len(value):self.write(a[3],value)
                return 0 if not a[3] or a[2]>=len(value) else -30
            two=name in ('clGetProgramBuildInfo','clGetKernelWorkGroupInfo')
            offset=1 if two else 0
            size=a[2+offset];data=C.create_string_buffer(max(1,size));needed=Z()
            types=[P,P,U,Z,P,P] if two else [P,U,Z,P,P]
            prefix=a[:3] if two else a[:2]
            code=self.invoke(name,types,[*prefix,size,data if a[3+offset] else None,C.byref(needed)])
            if a[3+offset]:self.write(a[3+offset],data.raw[:size])
            self.write(a[4+offset],struct.pack('<Q',needed.value));return code
        if name=='clCreateContext':
            props=None
            if a[0]:
                values=[]
                for i in range(0,32,2):
                    key=struct.unpack('<Q',self.read(a[0]+i*8,8))[0];values.append(key)
                    if not key:break
                    values.append(struct.unpack('<Q',self.read(a[0]+(i+1)*8,8))[0])
                values=[v for i in range(0,len(values)-1,2) if values[i]==0x1084 for v in values[i:i+2]]+[0]
                props=(Z*len(values))(*values)
            devices=self.array(a[2],a[1]);err=I()
            value=self.invoke(name,[P,U,P,P,P,P],[props,a[1],devices,None,None,C.byref(err)],P)
            self.error(a[5],err.value);return value or 0
        if name in ('clCreateCommandQueue','clCreateCommandQueueWithProperties'):
            err=I()
            flags=a[2]
            if name.endswith('WithProperties'):
                flags=0
                if a[2]:
                    for offset in range(0,64,16):
                        key,value=struct.unpack('<2Q',self.read(a[2]+offset,16))
                        if not key:break
                        if key==0x1093:flags=value&3
            value=self.invoke('clCreateCommandQueue',[P,P,Q,P],[a[0],a[1],flags,C.byref(err)],P)
            self.error(a[3],err.value);return value or 0
        if name=='clCreateBuffer':
            err=I();host=C.create_string_buffer(self.read(a[3],a[2]),a[2]) if a[3] else None
            value=self.invoke(name,[P,Q,Z,P,P],[a[0],a[1],a[2],host,C.byref(err)],P)
            if host:self.keep.append(host)
            self.error(a[4],err.value);return value or 0
        if name=='clCreateProgramWithSource':
            lengths=self.array(a[3],a[1]);ptrs=self.array(a[2],a[1]);data=[]
            for i,p in enumerate(ptrs):data.append(self.read(p,lengths[i]) if lengths and lengths[i] else r.cstring(p))
            strings=(C.c_char_p*len(data))(*data);lens=(Z*len(data))(*map(len,data));err=I()
            value=self.invoke(name,[P,U,P,P,P],[a[0],a[1],strings,lens,C.byref(err)],P)
            self.error(a[4],err.value);return value or 0
        if name=='clBuildProgram':
            options=r.cstring(a[3]) if a[3] else None
            return self.invoke(name,[P,U,P,C.c_char_p,P,P],[a[0],a[1],self.array(a[2],a[1]),options,None,None])
        if name=='clCreateKernel':
            err=I();value=self.invoke(name,[P,C.c_char_p,P],[a[0],r.cstring(a[1]),C.byref(err)],P)
            self.error(a[2],err.value);return value or 0
        if name=='clSetKernelArg':
            data=C.create_string_buffer(self.read(a[3],a[2]),a[2]) if a[3] else None
            return self.invoke(name,[P,U,Z,P],[a[0],a[1],a[2],data])
        if name in ('clEnqueueReadBuffer','clEnqueueWriteBuffer'):
            size=a[4];data=C.create_string_buffer(self.read(a[5],size),size)
            event=P();wait=self.array(a[7],a[6])
            code=self.invoke(name,[P,P,U,Z,Z,P,U,P,P],[a[0],a[1],1,a[3],size,data,a[6],wait,C.byref(event) if a[8] else None])
            if name=='clEnqueueReadBuffer':self.write(a[5],data.raw[:size])
            self.write(a[8],struct.pack('<Q',event.value or 0));return code
        if name=='clEnqueueMapBuffer':
            event=P();err=I()
            value=self.invoke(name,[P,P,U,Q,Z,Z,U,P,P,P],
                [a[0],a[1],1,a[3],a[4],a[5],a[6],self.array(a[7],a[6]),C.byref(event) if a[8] else None,C.byref(err)],P)
            address=r.alloc(C.string_at(value,a[5])) if value else 0
            if address:self.mapped[address]=(value,a[5])
            self.write(a[8],struct.pack('<Q',event.value or 0));self.error(a[9],err.value);return address
        if name=='clEnqueueUnmapMemObject':
            value,size=self.mapped.pop(a[2]);C.memmove(value,self.read(a[2],size),size)
            event=P()
            code=self.invoke(name,[P,P,P,U,P,P],[a[0],a[1],value,a[3],self.array(a[4],a[3]),C.byref(event) if a[5] else None])
            self.invoke('clFinish',[P],[a[0]])
            self.write(a[5],struct.pack('<Q',event.value or 0));return code
        if name=='clEnqueueNDRangeKernel':
            event=P();n=a[2]
            code=self.invoke(name,[P,P,U,P,P,P,U,P,P],
                [a[0],a[1],n,self.array(a[3],n),self.array(a[4],n),self.array(a[5],n),a[6],self.array(a[7],a[6]),C.byref(event) if a[8] else None])
            self.invoke('clFinish',[P],[a[0]])
            self.write(a[8],struct.pack('<Q',event.value or 0));return code
        if name=='clEnqueueCopyBuffer':
            event=P()
            code=self.invoke(name,[P,P,P,Z,Z,Z,U,P,P],[*a[:7],self.array(a[7],a[6]),C.byref(event) if a[8] else None])
            self.invoke('clFinish',[P],[a[0]])
            self.write(a[8],struct.pack('<Q',event.value or 0));return code
        if name=='clWaitForEvents':return self.invoke(name,[U,P],[a[0],self.array(a[1],a[0])])
        if name.startswith(('clRelease','clRetain')) or name in ('clFinish','clFlush'):
            return self.invoke(name,[P],[a[0]])
        raise RuntimeError(f'OpenCL adapter missing {name}')
