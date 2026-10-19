"""Opt this generated executable out of CFG for Unicorn's JIT/longjmp.

PyInstaller documents this incompatibility and recommends a --no-cfg bootloader:
https://pyinstaller.org/en/stable/common-issues-and-pitfalls.html#windows-executables-and-control-flow-guard-cfg
This changes only the generated PE's opt-in flags, never OS/process policy.
Other mitigations, imports, code and the appended Python archive are preserved.
"""
from pathlib import Path
import json
import os
import pefile


def disable_cfg(path):
    path=Path(path)
    original=path.read_bytes()
    pe=pefile.PE(data=original)
    before=pe.OPTIONAL_HEADER.DllCharacteristics
    # Equivalent PE declaration to a bootloader linked without /GUARD:CF.
    pe.OPTIONAL_HEADER.DllCharacteristics=before&~0x4000
    load=getattr(pe,'DIRECTORY_ENTRY_LOAD_CONFIG',None)
    old_guard=load.struct.GuardFlags if load and hasattr(load.struct,'GuardFlags') else None
    if old_guard is not None:load.struct.GuardFlags=0
    pe.OPTIONAL_HEADER.CheckSum=pe.generate_checksum()
    adjusted=pe.write()
    if len(adjusted)!=len(original):raise RuntimeError('PE update changed file length')
    temporary=path.with_suffix('.cfg.tmp')
    temporary.write_bytes(adjusted)
    os.replace(temporary,path)
    return {'file':str(path),'dll_characteristics_before':before,
            'dll_characteristics_after':before&~0x4000,'guard_flags_before':old_guard,
            'guard_flags_after':0,'file_size_preserved':len(original),
            'scope':'Generated executable only; OS mitigation policy unchanged'}


if __name__=='__main__':
    import sys
    print(json.dumps(disable_cfg(sys.argv[1]),indent=2))
