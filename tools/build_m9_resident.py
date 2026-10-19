"""Generate a batch-capable model and portable PTX using a local build compiler.

NVRTC is a build-only dependency; generated releases use nvcuda.dll and the
already bundled CUDA runtime, and do not include PyTorch or its compiler DLLs.
"""
from pathlib import Path
import ctypes,hashlib,importlib.util,os
import onnx
root=Path(__file__).resolve().parents[1]
model=onnx.load(root/'research/models/colorfix.onnx')
assert {n.op_type for n in model.graph.node}<={'Conv','Constant','Clip','MaxPool','DepthToSpace','Concat'}
assert len(model.graph.value_info)==0
model.graph.input[0].type.tensor_type.shape.dim[0].dim_param='batch'
model.graph.output[0].type.tensor_type.shape.dim[0].dim_param='batch'
onnx.checker.check_model(model)
target=root/'assets/m9_models/colorfix_batch.onnx';target.parent.mkdir(exist_ok=True)
onnx.save(model,target)
print('batch model',hashlib.sha256(target.read_bytes()).hexdigest())
compiler=os.environ.get('CAMERALOOK_NVRTC')
if not compiler:
    folder=Path(importlib.util.find_spec('torch').origin).parent/'lib'
    compiler=next(folder.glob('nvrtc64_*.dll'))
compiler=Path(compiler)
cookie=os.add_dll_directory(str(compiler.parent))
builtins=[ctypes.CDLL(str(p)) for p in compiler.parent.glob('nvrtc-builtins*.dll')]
lib=ctypes.CDLL(str(compiler))
def function(name,args):
    fn=getattr(lib,name);fn.argtypes=args;fn.restype=ctypes.c_int;return fn
ptr=ctypes.c_void_p;size=ctypes.c_size_t;char=ctypes.c_char_p
create=function('nvrtcCreateProgram',[ctypes.POINTER(ptr),char,char,ctypes.c_int,ptr,ptr])
compile_=function('nvrtcCompileProgram',[ptr,ctypes.c_int,ctypes.POINTER(char)])
get_log_size=function('nvrtcGetProgramLogSize',[ptr,ctypes.POINTER(size)])
get_log=function('nvrtcGetProgramLog',[ptr,ptr])
get_size=function('nvrtcGetPTXSize',[ptr,ctypes.POINTER(size)])
get_ptx=function('nvrtcGetPTX',[ptr,ptr])
destroy=function('nvrtcDestroyProgram',[ctypes.POINTER(ptr)])
program=ptr();assert create(ctypes.byref(program),(root/'tools/m9_resident.cu').read_bytes(),b'm9_resident.cu',0,None,None)==0
try:
    flags=[b'--gpu-architecture=compute_80',b'--std=c++11',b'--fmad=false',b'--ftz=false',b'--prec-div=true']
    result=compile_(program,len(flags),(char*len(flags))(*flags))
    n=size();get_log_size(program,ctypes.byref(n));log=ctypes.create_string_buffer(n.value);get_log(program,log)
    if result:raise RuntimeError(log.value.decode('utf-8','replace'))
    assert get_size(program,ctypes.byref(n))==0
    data=ctypes.create_string_buffer(n.value);assert get_ptx(program,data)==0
    target=root/'assets/native/m9_resident.ptx';target.write_bytes(data.raw)
    print('PTX',target.stat().st_size,hashlib.sha256(target.read_bytes()).hexdigest())
finally:destroy(ctypes.byref(program));cookie.close()
