"""Keep the NVIDIA JIT's process path ASCII without moving the portable app."""
from pathlib import Path
import hashlib
import os
import subprocess
import sys


def relaunch_if_needed():
    if os.name!='nt' or not getattr(sys,'frozen',False) or sys.executable.isascii():return None
    source=Path(sys.executable).resolve().parent
    if not (source/'_internal/assets/nvidia_runtime').is_dir():return None
    # Mount-point junctions require no administrator privileges. A per-location
    # name prevents another portable copy from taking over an existing alias.
    base=Path(os.environ.get('LOCALAPPDATA',str(Path.home())))/'CameraLookDesktop/launch-v7'
    base.mkdir(parents=True,exist_ok=True)
    if not str(base).isascii():
        import ctypes
        buf=ctypes.create_unicode_buffer(32768)
        if not ctypes.windll.kernel32.GetShortPathNameW(str(base),buf,len(buf)) or not buf.value.isascii():
            return None
        base=Path(buf.value)
    alias=base/hashlib.sha256(str(source).casefold().encode('utf-8')).hexdigest()[:20]
    if not alias.exists():
        import _winapi
        try:_winapi.CreateJunction(str(source),str(alias))
        except FileExistsError:pass
    if alias.resolve()!=source:raise RuntimeError('应用兼容路径与当前目录不一致')
    executable=alias/Path(sys.executable).name
    child=subprocess.Popen([str(executable),*sys.argv[1:]],creationflags=subprocess.CREATE_NO_WINDOW)
    return child.wait()


def process_memory():
    if os.name != 'nt':
        # ru_maxrss is reported in bytes on macOS and kilobytes on Linux.
        import resource
        peak = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
        if sys.platform != 'darwin':
            peak *= 1024
        return {'peak_working_set_megabytes': round(peak/1024**2, 1),
                'peak_pagefile_megabytes': 0.0}
    import ctypes
    from ctypes import wintypes
    class Memory(ctypes.Structure):
        _fields_=[('cb',wintypes.DWORD),('PageFaultCount',wintypes.DWORD)]+[
            (name,ctypes.c_size_t) for name in ('PeakWorkingSetSize','WorkingSetSize','QuotaPeakPagedPoolUsage',
            'QuotaPagedPoolUsage','QuotaPeakNonPagedPoolUsage','QuotaNonPagedPoolUsage','PagefileUsage','PeakPagefileUsage')]
    query=ctypes.WinDLL('psapi',use_last_error=True).GetProcessMemoryInfo
    query.argtypes=[wintypes.HANDLE,ctypes.POINTER(Memory),wintypes.DWORD];query.restype=wintypes.BOOL
    current=ctypes.WinDLL('kernel32').GetCurrentProcess
    current.restype=wintypes.HANDLE
    value=Memory();value.cb=ctypes.sizeof(value)
    if not query(current(),ctypes.byref(value),value.cb):raise ctypes.WinError()
    return {'peak_working_set_megabytes':round(value.PeakWorkingSetSize/1024**2,1),
            'peak_pagefile_megabytes':round(value.PeakPagefileUsage/1024**2,1)}


def available_memory():
    """Available physical bytes for optional prefetch; unknown means no prefetch."""
    try:
        if os.name=='nt':
            import ctypes
            class Status(ctypes.Structure):
                _fields_=[('length',ctypes.c_ulong),('load',ctypes.c_ulong)]+[
                    (name,ctypes.c_ulonglong) for name in ('total','available','page_total','page_available','virtual_total','virtual_available','extended')]
            value=Status();value.length=ctypes.sizeof(value)
            if ctypes.windll.kernel32.GlobalMemoryStatusEx(ctypes.byref(value)):return value.available
        elif hasattr(os,'sysconf'):
            return os.sysconf('SC_AVPHYS_PAGES')*os.sysconf('SC_PAGE_SIZE')
    except (OSError,ValueError,AttributeError):pass
    return None
