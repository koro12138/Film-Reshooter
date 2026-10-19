"""Build the remaining M3 prepare/base routines, keeping v7 DLLs untouched."""
from pathlib import Path
import os,subprocess,sys
root=Path(__file__).resolve().parents[1]
zig=Path(os.environ.get('CAMERALOOK_ZIG','zig'))
target=root/'assets/native/cameralook_m3_core.dll'
extra=[]
if '--probe' in sys.argv:target=target.with_name('cameralook_m3_core_probe.dll');extra=['-DCAMERALOOK_M3_PROBE=1']
subprocess.run([str(zig),'cc','-shared','-O3','-ffp-contract=off','-fno-strict-aliasing',
                '-march=x86_64',*extra,str(root/'tools/native_m3_core.c'),'-o',str(target)],check=True)
print(target)
