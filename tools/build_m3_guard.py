"""Build the recovered M3 guard without changing the existing postprocessing DLL."""
from pathlib import Path
import os,subprocess,sys
root=Path(__file__).resolve().parents[1]
subprocess.run([sys.executable,str(root/'tools/prepare_m3_guard.py')],check=True)
zig=Path(os.environ.get('CAMERALOOK_ZIG','zig'))
target=root/'assets/native/cameralook_m3.dll'
subprocess.run([str(zig),'cc','-shared','-O3','-ffp-contract=off','-fno-strict-aliasing',
                '-fwrapv','-march=x86_64',str(root/'tools/native_m3_guard.c'),'-o',str(target)],check=True)
print(target)
