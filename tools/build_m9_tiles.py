"""Build the portable M9 frame packing kernels."""
from pathlib import Path
import os,subprocess
root=Path(__file__).resolve().parents[1]
zig=os.environ.get('CAMERALOOK_ZIG','zig')
target=root/'assets/native/cameralook_m9_tiles.dll'
subprocess.run([zig,'cc','-shared','-O3','-ffp-contract=off','-fno-strict-aliasing',
                '-march=x86_64',str(root/'tools/native_m9_tiles.c'),'-o',str(target)],check=True)
print(target)
