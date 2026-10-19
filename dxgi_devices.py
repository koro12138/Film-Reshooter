"""Enumerate the same DXGI adapter indices used by ONNX Runtime DirectML."""
import sys


def adapters():
    if sys.platform!='win32':
        return []
    import ctypes as c
    import uuid
    class Desc(c.Structure):
        _fields_ = [('description',c.c_wchar*128),('vendor',c.c_uint),('device',c.c_uint),
            ('subsys',c.c_uint),('revision',c.c_uint),('dedicated',c.c_size_t),
            ('system',c.c_size_t),('shared',c.c_size_t),('luid',c.c_byte*8),('flags',c.c_uint)]
    def method(ptr,index,restype,*argtypes):
        address = c.cast(ptr,c.POINTER(c.POINTER(c.c_void_p))).contents[index]
        return c.WINFUNCTYPE(restype,c.c_void_p,*argtypes)(address)
    factory = c.c_void_p()
    guid = (c.c_ubyte*16).from_buffer_copy(uuid.UUID('770aae78-f26f-4dba-a829-253c83d1b387').bytes_le)
    create = c.WinDLL('dxgi').CreateDXGIFactory1
    create.argtypes = [c.c_void_p,c.POINTER(c.c_void_p)]
    create.restype = c.c_long
    if create(c.byref(guid),c.byref(factory))<0:
        return []
    result = []
    try:
        enum = method(factory,12,c.c_long,c.c_uint,c.POINTER(c.c_void_p))
        for index in range(16):
            adapter = c.c_void_p()
            if enum(factory,index,c.byref(adapter))<0:
                break
            try:
                desc = Desc()
                if method(adapter,10,c.c_long,c.POINTER(Desc))(adapter,c.byref(desc))>=0:
                    result.append({'id':index,'name':desc.description,'dedicated_bytes':int(desc.dedicated),
                                   'vendor':desc.vendor,'software':bool(desc.flags&2)})
            finally:
                method(adapter,2,c.c_ulong)(adapter)
    finally:
        method(factory,2,c.c_ulong)(factory)
    return result
