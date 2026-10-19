"""Platform-aware native library resolution shared by the desktop runtimes.

Windows loads the shipped `.dll` files; macOS loads the clang-built `.dylib`
files next to them. Both live in `assets/native` so the portable layout and the
PyInstaller `_internal` layout stay identical.
"""
import ctypes
import platform
import sys
from functools import lru_cache
from pathlib import Path

ROOT = Path(getattr(sys, '_MEIPASS', Path(__file__).resolve().parent))

WINDOWS = sys.platform == 'win32'
MACOS = sys.platform == 'darwin'
SUFFIX = '.dll' if WINDOWS else '.dylib' if MACOS else '.so'


def backend_name():
    """Human-readable name used in reports instead of a hard-coded 'Windows x64'."""
    machine = platform.machine() or 'unknown'
    if WINDOWS:
        return 'Windows x64' if machine.upper() in ('AMD64', 'X86_64') else f'Windows {machine}'
    if MACOS:
        return 'macOS arm64' if machine == 'arm64' else f'macOS {machine}'
    return f'{sys.platform} {machine}'


@lru_cache(maxsize=None)
def path(name):
    """Return the current-platform library path for `name` (without suffix)."""
    folder = ROOT / 'assets' / 'native'
    candidate = folder / f'{name}{SUFFIX}'
    if candidate.is_file():
        return candidate
    raise OSError(f'缺少原生库 {name}{SUFFIX}（目录 {folder}）')


def load(name):
    return ctypes.CDLL(str(path(name)))
