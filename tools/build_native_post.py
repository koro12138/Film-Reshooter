"""Build the portable x64 image routines; no compiler is needed by users."""
from pathlib import Path
import subprocess
import os
root=Path(__file__).resolve().parents[1]
zig=Path(os.environ.get('CAMERALOOK_ZIG','zig'))
target=root/'assets/native/cameralook_post.dll'
target.parent.mkdir(parents=True,exist_ok=True)
subprocess.run([str(zig),'cc','-shared','-O3','-ffp-contract=off','-march=x86_64',
                str(root/'tools/native_post.c'),'-o',str(target)],check=True)
print(target)
