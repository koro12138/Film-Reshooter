"""Local ARM64 image-routine sandbox, with a minimal bitmap/libc adapter.

Only selected image functions are called; Android entry points, networking,
filesystem access, dlopen and process creation are not implemented.
"""
from pathlib import Path
import math
import struct
import time
import numpy as np
from functools import lru_cache
from threading import Lock
from engine import ROOT, Cancelled

_image_lock=Lock()

@lru_cache(maxsize=8)
def _library_image(library):
    """Immutable ELF data shared by independent engines, not shared ARM state."""
    from elftools.elf.elffile import ELFFile
    with (ROOT/'lib/arm64-v8a'/library).open('rb') as f:
        elf=ELFFile(f)
        segments=tuple((s['p_vaddr'],s.data()) for s in elf.iter_segments() if s['p_type']=='PT_LOAD')
        symbols={}
        for section in ('.dynsym','.symtab'):
            table=elf.get_section_by_name(section)
            if table:symbols.update({s.name:s['st_value'] for s in table.iter_symbols() if s['st_value']})
        relocations=[]
        for section in elf.iter_sections():
            if section['sh_type']!='SHT_RELA':continue
            table=elf.get_section(section['sh_link'])
            for rel in section.iter_relocations():
                kind=rel['r_info_type'];value=0;name=''
                if kind in (257,1025,1026):
                    symbol=table.get_symbol(rel['r_info_sym']);value=symbol['st_value'];name=symbol.name
                relocations.append((kind,rel['r_offset'],rel['r_addend'],value,name))
        return segments,tuple(symbols.items()),tuple(relocations)


class NativeImageRuntime:
    BASE = 0x1000000
    HEAP = 0x10000000
    LIMIT = 0x68000000
    STUB = 0x70000000
    STACK = 0x80000000
    RETURN = 0x90000000

    def __init__(self, library='libfullm9.so', heap_bytes=None):
        from unicorn import Uc, UC_ARCH_ARM64, UC_MODE_ARM, UC_HOOK_CODE
        from unicorn import arm64_const as regs
        from elftools.elf.elffile import ELFFile
        self.regs = regs
        self.uc = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        self.uc.ctl_set_cpu_model(regs.UC_CPU_ARM64_MAX)
        if heap_bytes is not None:
            size=(max(65536,int(heap_bytes))+4095)&~4095
            if size>self.LIMIT-self.HEAP:raise MemoryError('原生工作内存请求超限')
            self.LIMIT=self.HEAP+size
        self.heap_capacity=self.LIMIT-self.HEAP
        self.uc.mem_map(self.BASE, 0x4000000)
        self.uc.mem_map(self.HEAP, self.LIMIT-self.HEAP)
        self.uc.mem_map(self.STUB, 0x10000)
        self.uc.mem_map(self.STACK, 0x100000)
        self.uc.mem_map(self.RETURN, 0x1000)
        self.uc.reg_write(regs.UC_ARM64_REG_CPACR_EL1, 0x300000)
        self.stubs = {}
        self.symbols = {}
        self.math_symbols = {}
        self.cpp_symbols = {}
        self.opencl = None
        if library=='libmialgo_monopan.so':
            self.uc.mem_map(0x8000000,0x1000000)
            with (ROOT/'lib/arm64-v8a/libc++_shared.so').open('rb') as f:
                elf=ELFFile(f)
                for seg in elf.iter_segments():
                    if seg['p_type']=='PT_LOAD':self.uc.mem_write(0x8000000+seg['p_vaddr'],seg.data())
                self.cpp_symbols={s.name:0x8000000+s['st_value'] for s in elf.get_section_by_name('.dynsym').iter_symbols() if s['st_value']}
                for section in elf.iter_sections():
                    if section['sh_type']!='SHT_RELA':continue
                    table=elf.get_section(section['sh_link'])
                    for rel in section.iter_relocations():
                        kind,addend=rel['r_info_type'],rel['r_addend']
                        if kind==1027:target=0x8000000+addend
                        elif kind in (257,1025,1026):
                            sym=table.get_symbol(rel['r_info_sym'])
                            target=0x8000000+sym['st_value']+addend if sym['st_value'] else self.stub(sym.name)+addend
                        else:raise RuntimeError(f'C++ relocation {kind}')
                        self.uc.mem_write(0x8000000+rel['r_offset'],struct.pack('<Q',target))
        helper = ROOT/'assets/math_arm.elf'
        if helper.exists():
            self.uc.mem_map(0x6000000,0x1000000)
            with helper.open('rb') as f:
                elf=ELFFile(f)
                for seg in elf.iter_segments():
                    if seg['p_type']=='PT_LOAD':
                        self.uc.mem_write(0x5000000+seg['p_vaddr'],seg.data())
                self.math_symbols={s.name:0x5000000+s['st_value'] for s in elf.get_section_by_name('.symtab').iter_symbols() if s['st_value']}
        # A lock avoids duplicate cold parsing when four M3 workers start together.
        with _image_lock:segments,symbols,relocations=_library_image(library)
        for address,data in segments:self.uc.mem_write(self.BASE+address,data)
        self.symbols.update({name:self.BASE+value for name,value in symbols})
        for kind,offset,addend,value,name in relocations:
            if kind==1027:target=self.BASE+addend
            elif kind in (257,1025,1026):
                target=self.BASE+value+addend if value else self.stub(name)+addend
            elif kind==1031:
                self.uc.mem_write(self.BASE+offset,struct.pack('<2Q',self.stub('TLS_offset'),0x100));continue
            else:raise RuntimeError(f'Unsupported native relocation {kind}')
            self.uc.mem_write(self.BASE+offset,struct.pack('<Q',target))
        self.hooks=[self.uc.hook_add(UC_HOOK_CODE,self._dispatch,begin=self.STUB,end=self.STUB+0xffff)]
        if 'b6_rows' in self.symbols:
            self.hooks.append(self.uc.hook_add(UC_HOOK_CODE,self._serial_rows,begin=self.symbols['b6_rows'],end=self.symbols['b6_rows']))
        self.reset()

    def close(self):
        if self.uc is not None:
            for handle in self.hooks:self.uc.hook_del(handle)
            self.hooks.clear()
            self.uc=None
            self.opencl=None

    def _serial_rows(self,uc,address,size,data):
        r=self.regs
        height=uc.reg_read(r.UC_ARM64_REG_X0)
        callback=uc.reg_read(r.UC_ARM64_REG_X2)
        context=uc.reg_read(r.UC_ARM64_REG_X3)
        self.row_job=[context,callback,0,height,uc.reg_read(r.UC_ARM64_REG_LR)]
        self._advance_rows()

    def _advance_rows(self):
        from engine import Cancelled
        if self.active_cancelled and self.active_cancelled():raise Cancelled()
        context,callback,start,height,parent_return=self.row_job
        if start>=height:
            self.uc.reg_write(self.regs.UC_ARM64_REG_LR,parent_return)
            self.uc.reg_write(self.regs.UC_ARM64_REG_PC,parent_return)
            self.row_job=None
            return
        end=min(height,start+getattr(self,'row_chunk',128))
        self.row_job[2]=end
        self.uc.reg_write(self.regs.UC_ARM64_REG_X0,context)
        self.uc.reg_write(self.regs.UC_ARM64_REG_X1,start)
        self.uc.reg_write(self.regs.UC_ARM64_REG_X2,end)
        self.uc.reg_write(self.regs.UC_ARM64_REG_LR,self.stub('RowsNext'))
        self.uc.reg_write(self.regs.UC_ARM64_REG_PC,callback)

    def stub(self, name):
        if name in self.cpp_symbols:
            return self.cpp_symbols[name]
        if name in ('sinf','expf','powf','fmodf','log2f','exp2f','logf') and name in self.math_symbols:
            return self.math_symbols[name]
        for address, existing in self.stubs.items():
            if existing == name:
                return address
        address = self.STUB+len(self.stubs)*16
        self.stubs[address] = name
        self.uc.mem_write(address,b'\xc0\x03\x5f\xd6')  # ret
        return address

    def reset(self):
        self.next = self.HEAP
        self.allocations = {}
        self.bitmaps = {}
        self.files = {}
        self.thread_values = {}
        self.next_key = 1
        self.messages = []
        self.row_job=None
        self.active_cancelled=None
        table = self.alloc(bytes(2048))
        self.env = self.alloc(struct.pack('<Q',table))
        self.uc.mem_write(table+0xc0,struct.pack('<Q',self.stub('JNI_IsSameObject')))
        self.uc.mem_write(table+0x598,struct.pack('<Q',self.stub('JNI_NewIntArray')))
        self.uc.mem_write(table+0x698,struct.pack('<Q',self.stub('JNI_SetIntArrayRegion')))

    def alloc(self, value):
        data = value if isinstance(value,(bytes,bytearray)) else None
        size = len(data) if data is not None else int(value)
        address = self.next
        self.next += (max(1,size)+63)&~63
        if self.next>=self.LIMIT:
            raise MemoryError('原生图像处理工作内存超限')
        self.allocations[address] = size
        if data is not None:
            self.uc.mem_write(address,bytes(data))
        return address

    def bitmap(self, rgb):
        h,w = rgb.shape[:2]
        rgba = np.full((h,w,4),255,np.uint8)
        rgba[...,:3] = rgb
        pixels = self.alloc(rgba.tobytes())
        obj = self.alloc(64)
        self.bitmaps[obj] = (w,h,pixels)
        return obj

    def read_bitmap(self, obj):
        w,h,p = self.bitmaps[obj]
        return np.frombuffer(self.uc.mem_read(p,w*h*4),np.uint8).reshape(h,w,4)[...,:3].copy()

    def _dispatch(self, uc, address, size, data):
        r = self.regs
        a = [uc.reg_read(getattr(r,f'UC_ARM64_REG_X{i}')) for i in range(8)]
        a.extend(struct.unpack('<8Q',uc.mem_read(uc.reg_read(r.UC_ARM64_REG_SP),64)))
        name = self.stubs[address]
        result = 0
        if name=='RowsNext':
            self._advance_rows()
            return
        if name in ('malloc','calloc','realloc','_Znwm','_Znam'):
            count = a[0]*a[1] if name=='calloc' else a[1] if name=='realloc' else a[0]
            result = self.alloc(count)
            if name=='calloc':
                uc.mem_write(result,bytes(count))
            if name=='realloc' and a[0]:
                uc.mem_write(result,bytes(uc.mem_read(a[0],min(count,self.allocations.get(a[0],0)))))
        elif name in ('free','_ZdlPv','_ZdaPv','AndroidBitmap_unlockPixels','__cxa_atexit','__cxa_finalize'):
            pass
        elif name in ('memcpy','memmove'):
            uc.mem_write(a[0],bytes(uc.mem_read(a[1],a[2])))
            result = a[0]
        elif name=='memset':
            uc.mem_write(a[0],bytes([a[1]&255])*a[2]); result=a[0]
        elif name=='memchr':
            pos=bytes(uc.mem_read(a[0],a[2])).find(bytes([a[1]&255]));result=a[0]+pos if pos>=0 else 0
        elif name in ('memcmp','strcmp','strncmp'):
            left=bytes(uc.mem_read(a[0],a[2])) if name=='memcmp' else self.cstring(a[0])
            right=bytes(uc.mem_read(a[1],a[2])) if name=='memcmp' else self.cstring(a[1])
            if name=='strncmp':left,right=left[:a[2]],right[:a[2]]
            result=(left>right)-(left<right)
        elif name=='AndroidBitmap_getInfo':
            w,h,p = self.bitmaps[a[1]]
            uc.mem_write(a[2],struct.pack('<5I',w,h,w*4,1,0))
        elif name=='AndroidBitmap_lockPixels':
            uc.mem_write(a[2],struct.pack('<Q',self.bitmaps[a[1]][2]))
        elif name=='JNI_IsSameObject':
            result = int(a[1]==a[2])
        elif name=='JNI_NewIntArray':result=self.alloc(bytes(a[1]*4))
        elif name=='JNI_SetIntArrayRegion':
            uc.mem_write(a[1]+a[2]*4,bytes(uc.mem_read(a[4],a[3]*4)))
        elif name in ('sinf','expf','sqrtf','logf','powf'):
            x = struct.unpack('<f',struct.pack('<I',uc.reg_read(r.UC_ARM64_REG_S0)))[0]
            if name=='powf':
                y = struct.unpack('<f',struct.pack('<I',uc.reg_read(r.UC_ARM64_REG_S1)))[0]
                value = math.pow(x,y)
            else:
                value = {'sinf':math.sin,'expf':math.exp,'sqrtf':math.sqrt,'logf':math.log}[name](x)
            uc.reg_write(r.UC_ARM64_REG_S0,struct.unpack('<I',struct.pack('<f',value))[0])
        elif name in ('log','exp','sqrt','pow','ceil','floor','erf'):
            x=struct.unpack('<d',struct.pack('<Q',uc.reg_read(r.UC_ARM64_REG_D0)))[0]
            if name=='pow':
                y=struct.unpack('<d',struct.pack('<Q',uc.reg_read(r.UC_ARM64_REG_D1)))[0];value=math.pow(x,y)
            elif name=='log' and x==0:value=-math.inf
            else:value={'log':math.log,'exp':math.exp,'sqrt':math.sqrt,'ceil':math.ceil,'floor':math.floor,'erf':math.erf}[name](x)
            uc.reg_write(r.UC_ARM64_REG_D0,struct.unpack('<Q',struct.pack('<d',value))[0])
        elif name=='strlen':
            result = 0
            while uc.mem_read(a[0]+result,1)!=b'\0': result+=1
        elif name=='posix_memalign':
            uc.mem_write(a[0],struct.pack('<Q',self.alloc(a[2])))
        elif name in ('getauxval','pthread_mutex_lock','pthread_mutex_unlock','_ZNSt6__ndk15mutex4lockEv','_ZNSt6__ndk15mutex6unlockEv'):
            pass
        elif name in ('pthread_cond_broadcast','pthread_mutex_init','pthread_mutex_destroy','pthread_rwlock_rdlock','pthread_rwlock_wrlock','pthread_rwlock_unlock','pthread_rwlock_init','pthread_rwlock_destroy'):
            pass
        elif name=='pthread_once':
            if uc.mem_read(a[0],4)==bytes(4):
                uc.mem_write(a[0],struct.pack('<I',1))
                uc.reg_write(r.UC_ARM64_REG_PC,a[1])
                return
        elif name=='pthread_key_create':
            uc.mem_write(a[0],struct.pack('<I',self.next_key));self.next_key+=1
        elif name=='pthread_setspecific': self.thread_values[a[0]]=a[1]
        elif name=='pthread_getspecific': result=self.thread_values.get(a[0],0)
        elif name=='pthread_key_delete': self.thread_values.pop(a[0],None)
        elif name=='TLS_offset':
            result = 0x100
        elif name in ('__android_log_print','__android_log_write'):
            try:self.messages.append(self.cstring(a[2]).decode('utf8','replace'))
            except Exception:pass
        elif name in ('vsnprintf','snprintf','__vsnprintf_chk','__vsprintf_chk'):
            fmt_index=3 if name=='__vsprintf_chk' else 4 if name=='__vsnprintf_chk' else 2
            fmt=self.cstring(a[fmt_index])
            text=self.format_va(fmt,a[fmt_index+1]) if name!='snprintf' else fmt
            if b'/proc/' in fmt:text=b'/proc/1000/maps'
            if fmt!=b'%c' and len(self.messages)<2000:self.messages.append(text.decode('utf8','replace'))
            if a[0]: uc.mem_write(a[0],text+b'\0')
            result=len(text)
        elif name=='__system_property_get':
            prop=self.cstring(a[0])
            value=b'3' if prop.endswith(b'.loglevel') else b'1' if b'.print.' in prop else b''
            uc.mem_write(a[1],value+b'\0');result=len(value)
        elif name=='atoi':
            value=bytes(uc.mem_read(a[0],64)).split(b'\0')[0]
            try: result=int(value)
            except ValueError: result=0
        elif name=='access': result=0xffffffffffffffff
        elif name in ('open','open64'):
            result=42 if self.cstring(a[0])==b'/dev/urandom' else 0xffffffffffffffff
        elif name=='read':
            if a[0]==42:
                import os
                uc.mem_write(a[1],os.urandom(a[2]));result=a[2]
            else: result=0
        elif name=='close': result=0
        elif name=='__errno':
            if not hasattr(self,'errno_address'): self.errno_address=self.alloc(struct.pack('<I',2))
            result=self.errno_address
        elif name=='strerror_r':
            text=b'Optional Android resource unavailable'[:max(0,a[2]-1)]
            if a[2]:uc.mem_write(a[1],text+b'\0')
        elif name=='fopen':
            path=self.cstring(a[0])
            if path==b'/proc/1000/maps':
                result=self.alloc(64)
                self.files[result]=[b'01000000-05000000 rwxp 00000000 00:00 0 /system/lib64/libmialgo_monopan.so\n',0]
        elif name=='fgets':
            content,pos=self.files[a[2]]
            end=min(len(content),content.find(b'\n',pos)+1 if b'\n' in content[pos:] else len(content),pos+max(0,a[1]-1))
            if end>pos:
                uc.mem_write(a[0],content[pos:end]+b'\0');self.files[a[2]][1]=end;result=a[0]
        elif name=='fclose': self.files.pop(a[0],None)
        elif name=='strstr':
            pos=self.cstring(a[0]).find(self.cstring(a[1]));result=a[0]+pos if pos>=0 else 0
        elif name=='strtoul':
            import re
            match=re.match(rb'[0-9a-fA-F]+',self.cstring(a[0]));result=int(match[0],a[2] or 10) if match else 0
        elif name in ('strtof','strtod'):
            import re
            match=re.match(rb'\s*[+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?',self.cstring(a[0]))
            value=float(match[0]) if match else 0.
            if a[1]:self.write_end_pointer(a[1],a[0]+(match.end() if match else 0))
            reg=r.UC_ARM64_REG_S0 if name=='strtof' else r.UC_ARM64_REG_D0
            uc.reg_write(reg,struct.unpack('<I' if name=='strtof' else '<Q',struct.pack('<f' if name=='strtof' else '<d',value))[0])
        elif name=='strtok':
            start=a[0] or getattr(self,'token_cursor',0)
            delimiters=self.cstring(a[1]);content=self.cstring(start)
            pos=next((i for i,c in enumerate(content) if c in delimiters),len(content))
            if pos<len(content):uc.mem_write(start+pos,b'\0')
            self.token_cursor=start+pos+1
            result=start if content else 0
        elif name in ('mprotect','__register_atfork','__cxa_guard_release'):
            if name=='__cxa_guard_release': uc.mem_write(a[0],b'\x01')
        elif name=='__cxa_guard_acquire':
            result=int(uc.mem_read(a[0],1)==b'\0')
        elif name=='getpid': result=1000
        elif name=='newlocale': result=self.alloc(bytes(1024))
        elif name in ('freelocale','uselocale'): result=0
        elif name=='localeconv': result=self.alloc(bytes(128))
        elif name=='sysconf': result=4096 if a[0]==39 else 1
        elif name=='syscall':
            if a[0] in (178,172): result=1000
            elif a[0] in (98,124): result=0
            else: raise RuntimeError(f'Unsupported native syscall {a[0]}')
        elif name=='_ZNSt6__ndk16chrono12steady_clock3nowEv': result=time.perf_counter_ns()
        elif name=='time':
            result=1700000000
            if a[0]:uc.mem_write(a[0],struct.pack('<Q',result))
        elif name in ('gettimeofday','clock_gettime'):
            target=a[0] if name=='gettimeofday' else a[1]
            now=time.perf_counter();seconds=int(now)
            uc.mem_write(target,struct.pack('<2Q',seconds,int((now-seconds)*(1e6 if name=='gettimeofday' else 1e9))))
        elif name in ('localtime','localtime_r'):
            result=a[1] if name.endswith('_r') else self.alloc(64)
            uc.mem_write(result,struct.pack('<9i',20,13,22,14,10,123,2,317,0)+bytes(28))
        elif name=='strftime':
            text=b'2023-11-14 22:13:20'
            text=text[:max(0,a[1]-1)]
            if a[1]:uc.mem_write(a[0],text+b'\0')
            result=len(text)
        elif name=='_ZNSt6__ndk16thread20hardware_concurrencyEv': result=1
        elif name=='dlopen':
            if self.cstring(a[0])==b'libOpenCL.so':
                from opencl_bridge import OpenCLBridge
                if self.opencl is None:self.opencl=OpenCLBridge(self)
                result=0xc1000000
            elif self.cstring(a[0])==b'libion.so':result=0xc2000000
        elif name=='dlsym':
            symbol=self.cstring(a[1]).decode('ascii')
            if a[0]==0xc1000000 and self.opencl and (hasattr(self.opencl.lib,symbol) or symbol=='clGetDeviceImageInfoQCOM'):result=self.stub(symbol)
            elif a[0]==0xc2000000:result=self.stub(symbol)
        elif name=='ion_open': result=43
        elif name=='ion_close': result=0
        elif name=='dlclose':result=0
        elif name.startswith('cl') and self.opencl:
            result=self.opencl.call(name,a)
        elif name=='dlerror': result=self.alloc(b'Desktop: optional Android compute driver unavailable\0')
        elif name=='_ZNSt6__ndk112__next_primeEm':
            result=max(2,a[0])
            while any(result%d==0 for d in range(2,math.isqrt(result)+1)): result+=1
        elif name.startswith('_ZNSt6__ndk1plIc'):
            out=uc.reg_read(r.UC_ARM64_REG_X8)
            self.set_string(out,self.cstring(a[0])+self.get_string(a[1]))
            result=out
        elif 'basic_stringIc' in name and '4findEcm' in name:
            result=self.get_string(a[0]).find(bytes([a[1]&255]),a[2])
        elif 'basic_stringIc' in name and any(token in name for token in ('C1ERKS','C2ERKS','aSERKS','C1EPKc','C2EPKc','D1Ev','D2Ev','5eraseEmm','6appendEPKc','6assignEPKc')):
            if any(t in name for t in ('D1Ev','D2Ev')):
                content=b''
            elif 'ERKS' in name:
                content=self.get_string(a[1])
            elif 'EPKc' in name and ('C1E' in name or 'C2E' in name or '6assign' in name):
                content=self.cstring(a[1])
            else:
                content=self.get_string(a[0])
            if '5erase' in name:
                content=content[:a[1]]+content[min(len(content),a[1]+a[2]):]
            elif '6append' in name: content+=bytes(uc.mem_read(a[1],a[2])) if name.endswith('EPKcm') else self.cstring(a[1])
            self.set_string(a[0],content)
            result=a[0]
        else:
            raise RuntimeError(f'原生图像函数调用了未支持的接口：{name}')
        uc.reg_write(r.UC_ARM64_REG_X0,result)
        uc.reg_write(r.UC_ARM64_REG_PC,uc.reg_read(r.UC_ARM64_REG_LR))

    def set_string(self,address,content):
        if len(content)<=22:
            self.uc.mem_write(address,bytes([len(content)*2])+content+bytes(23-len(content)))
        else:
            ptr=self.alloc(content+b'\0')
            self.uc.mem_write(address,struct.pack('<3Q',(len(content)+1)|1,len(content),ptr))

    def cstring(self,address):
        out=bytearray()
        for offset in range(0,1048576,64):
            block=bytes(self.uc.mem_read(address+offset,64))
            if b'\0' in block: return bytes(out)+block.split(b'\0',1)[0]
            out.extend(block)
        raise ValueError('Native string too long')

    def write_end_pointer(self,address,value):
        self.uc.mem_write(address,struct.pack('<Q',value))

    def format_va(self,fmt,va):
        import re
        stack,gr_top,vr_top,gr_off,vr_off=struct.unpack('<3Q2i',self.uc.mem_read(va,32))
        def replace(match):
            nonlocal stack,gr_off,vr_off
            token=match[0].decode('ascii')
            spec=token[-1]
            if spec=='%':return b'%'
            floating=spec in 'fFeEgGaA'
            if floating and vr_off<0:
                address=vr_top+vr_off;vr_off+=16
            elif not floating and gr_off<0:
                address=gr_top+gr_off;gr_off+=8
            else:address=stack;stack+=8
            raw=bytes(self.uc.mem_read(address,8))
            value=struct.unpack('<d' if floating else '<Q',raw)[0]
            if spec=='s':return self.cstring(value) if value else b'(null)'
            if spec=='c':return bytes([value&255])
            if spec=='p':return hex(value).encode('ascii')
            if spec in 'di':
                bits=64 if 'l' in token or 'z' in token else 32
                value&=(1<<bits)-1
                if value>>(bits-1):value-=1<<bits
            clean=re.sub('[lzhtj]','',token).replace('%u','%d')
            try:return (clean%value).encode('ascii')
            except Exception:return str(value).encode('ascii')
        return re.sub(rb'%(?:[-+ #0]*\d*(?:\.\d+)?[lzhtj]*[diuxXocspfFeEgGaA%])',replace,fmt)

    def get_string(self,address):
        header=bytes(self.uc.mem_read(address,24))
        if header[0]&1:
            length,ptr=struct.unpack_from('<2Q',header,8)
            if length>1048576: raise ValueError('Native C++ string has invalid length')
            return bytes(self.uc.mem_read(ptr,length))
        return header[1:1+(header[0]>>1)]

    def call(self, name, *args, cancelled=None):
        r = self.regs
        for i,arg in enumerate(args): self.uc.reg_write(getattr(r,f'UC_ARM64_REG_X{i}'),int(arg))
        self.uc.reg_write(r.UC_ARM64_REG_SP,self.STACK+0xff000)
        self.uc.reg_write(r.UC_ARM64_REG_LR,self.RETURN)
        self.uc.reg_write(r.UC_ARM64_REG_TPIDR_EL0,self.STACK)
        address = self.symbols[name] if isinstance(name,str) else self.BASE+name
        if cancelled and cancelled():raise Cancelled()
        # Run synchronously: Unicorn's timer may leave an ARM translation block
        # at a non-resumable PC on Windows. Row shims check cancellation between
        # completed callbacks; other functions finish their current stage.
        self.active_cancelled=cancelled
        try:self.uc.emu_start(address,self.RETURN)
        finally:self.active_cancelled=None
        if cancelled and cancelled():raise Cancelled()
        if self.uc.reg_read(r.UC_ARM64_REG_PC)!=self.RETURN:raise RuntimeError('原生图像函数未正常返回')
        return self.uc.reg_read(r.UC_ARM64_REG_X0)

    def texture(self, source, processed, cancelled=None):
        self.reset()
        src,dst = self.bitmap(source),self.bitmap(processed)
        self.call('Java_com_codex_fullm9_NativeM9_restoreTexture',self.env,0,src,dst,cancelled=cancelled)
        return self.read_bitmap(dst)

    def hdr_sample(self,image,width,height,cancelled=None):
        self.reset();bitmap=self.bitmap(image)
        array=self.call('Java_com_codex_fullm9_NativeM9_hdrSample',self.env,0,bitmap,width,height,cancelled=cancelled)
        if not array:raise RuntimeError('HDR 原生采样失败')
        return (np.frombuffer(self.uc.mem_read(array,width*height*4),'<u4')&255).astype(np.uint8).reshape(height,width)

    def denoise(self, image, finish=False, cancelled=None):
        self.reset()
        dst = self.bitmap(image)
        self.call('Java_com_codex_lmport_DenoiseFlow_filter',self.env,0,dst,int(finish),cancelled=cancelled)
        return self.read_bitmap(dst)

    def set_float(self, index, value):
        self.uc.reg_write(getattr(self.regs,f'UC_ARM64_REG_S{index}'),struct.unpack('<I',struct.pack('<f',value))[0])

    def quality_guard(self,source,processed,grade=False,cancelled=None):
        self.reset()
        src,dst=self.bitmap(source),self.bitmap(processed)
        w,h,ptr=self.bitmaps[src]
        reference=self.call('b6_reference_snapshot',ptr,w,h,w*4,1,cancelled=cancelled)
        out=self.bitmaps[dst][2]
        if grade:self.call('b4_m3_grade',out,w,h,w*4,cancelled=cancelled)
        stats=self.alloc(bytes(128))
        self.call('b4_guard',reference,out,w,h,w*4,1,int(grade),stats,cancelled=cancelled)
        return self.read_bitmap(dst)

    def m3_filter(self, image, cancelled=None, row_range=None):
        """Original zxbase M3 per-row function, without Android file/thread glue."""
        self.reset()
        raw = (ROOT/'assets/leica_filter_param_m3.bin').read_bytes()
        rp = self.alloc(raw)
        vector = self.alloc(struct.pack('<3Q',rp,rp+len(raw),rp+len(raw)))
        shade = self.alloc(bytes(32))
        for i,v in enumerate((200.,5500.,1.)): self.set_float(i,v)
        if not self.call(0xd620,vector,shade): raise RuntimeError('M3 原生暗角参数解析失败')
        if row_range is None:
            obj = self.bitmap(image)
            first,last=0,image.shape[0]
        else:
            # The base algorithm reads only the current pixel. Keep full-frame
            # coordinates/stride for shading, but populate just this worker's rows.
            height,width=image.shape[:2]
            first,last=row_range
            if not 0<=first<last<=height:raise ValueError('Invalid M3 row range')
            pixels=self.alloc(width*height*4)
            rgba=np.full((last-first,width,4),255,np.uint8);rgba[...,:3]=image[first:last]
            self.uc.mem_write(pixels+first*width*4,rgba.tobytes())
            obj=self.alloc(64);self.bitmaps[obj]=(width,height,pixels)
        w,h,pixels = self.bitmaps[obj]
        info = self.alloc(struct.pack('<5I',w,h,w*4,1,0))
        pointer = self.alloc(struct.pack('<Q',pixels))
        flag = self.alloc(bytes([bool(struct.unpack_from('<H',raw,0x362)[0])]))
        shade_flag = self.alloc(bytes([bool(struct.unpack_from('<H',raw,0x366)[0])]))
        lut = self.alloc(bytes(24))
        if raw[0x362:0x364]!=b'\0\0':
            self.set_float(0,200.); self.set_float(1,5500.)
            if not self.call(0xc620,vector,lut): raise RuntimeError('M3 原生 LUT 解析失败')
        false = self.alloc(bytes(1))
        floats = [self.alloc(struct.pack('<f',v)) for v in (-1.,-.35,.025,0.)]
        capture = self.alloc(struct.pack('<12Q',info,pointer,flag,lut,false,*floats[:3],shade_flag,shade,floats[3],vector))
        for top in range(first,last,64):
            self.call(0xf2ec,capture,top,min(last,top+64),cancelled=cancelled)
        if row_range is None:return self.read_bitmap(obj)
        return np.frombuffer(self.uc.mem_read(pixels+first*w*4,(last-first)*w*4),np.uint8).reshape(last-first,w,4)[...,:3].copy()
