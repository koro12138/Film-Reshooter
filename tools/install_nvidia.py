"""Developer setup only: install the pinned optional EP inside this project."""
from pathlib import Path
import subprocess,sys
root=Path(__file__).resolve().parents[1]
subprocess.run([sys.executable,'-m','pip','install','--target',str(root/'assets/nvidia_runtime'),
    '--no-deps','--upgrade','onnxruntime-ep-nv-tensorrt-rtx-cu12==0.4.0'],check=True)
print('NVIDIA EP installed locally; the global DirectML package was not replaced.')
