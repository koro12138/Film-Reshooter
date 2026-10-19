import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from native_runtime import NativeImageRuntime
from elftools.elf.elffile import ELFFile
from pathlib import Path
import struct
r=NativeImageRuntime('libmialgo_monopan.so')
with open('lib/arm64-v8a/libmialgo_monopan.so','rb') as f:
 e=ELFFile(f);s=e.get_section_by_name('.init_array');entries=struct.unpack('<'+'Q'*(s['sh_size']//8),r.uc.mem_read(r.BASE+s['sh_addr'],s['sh_size']))
 for i,x in enumerate(entries):
  if not x:continue
  try:r.call(x-r.BASE)
  except Exception as err:print('init failed',i,hex(x),repr(err));break
 else:print('ALL INITIALIZERS PASSED')

from unicorn import UC_HOOK_CODE
import struct,numpy as np
r.tensor_tables={}
def create_tensor(uc,address,size,data):
 args=[uc.reg_read(getattr(r.regs,f'UC_ARM64_REG_X{i}')) for i in range(6)]
 name=r.get_string(args[1]).decode('utf8');dims=struct.unpack('<3i',uc.mem_read(args[3],12));rows,cols,ch=dims;ch=max(1,ch);bps=(1,1,2,2,4,4,4,8,2)[args[2]-1]
 count=rows*cols*ch*bps;pixel=r.alloc(bytes(count));obj=r.alloc(bytes(112))
 uc.mem_write(obj,struct.pack('<2Q8I',r.BASE+0x1170250,1,args[2],1,rows,cols,ch,rows,cols*ch*bps,0))
 uc.mem_write(obj+0x30,struct.pack('<Q',count));uc.mem_write(obj+0x58,struct.pack('<Q',pixel))
 r.tensor_tables[name]=(obj,pixel,dims,args[2],count)
 print('tensor',name,dims,args[2],count,flush=True)
 uc.reg_write(r.regs.UC_ARM64_REG_X0,obj);uc.reg_write(r.regs.UC_ARM64_REG_PC,uc.reg_read(r.regs.UC_ARM64_REG_LR))
r.uc.hook_add(UC_HOOK_CODE,create_tensor,begin=r.BASE+0xdf22d8,end=r.BASE+0xdf22d8)
try:
 context=r.call('MonopanInit',r.alloc(Path('research/monopan_config.bin').read_bytes()));print('CONTEXT',hex(context),flush=True)
 tables={}
 for name,(obj,pixel,dims,kind,count) in r.tensor_tables.items():
  array=np.frombuffer(r.uc.mem_read(pixel,count),{1:np.uint8,3:np.uint16,7:np.float32}[kind]).reshape(dims)
  tables[name]=array
 np.savez_compressed('assets/monopan_tables.npz',**tables)
 Path('research/monopan_context.bin').write_bytes(r.uc.mem_read(context,256))
except Exception as err:
 import traceback;traceback.print_exc();print('pc',hex(r.uc.reg_read(r.regs.UC_ARM64_REG_PC)));print('\n'.join(r.messages[-10:]))
