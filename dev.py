"""Portable development entry point for Windows x64 and macOS arm64."""
from pathlib import Path
import argparse
import importlib.metadata
import json
import os
import platform
import shutil
import subprocess
import sys

ROOT=Path(__file__).resolve().parent
PORTABLE_TESTS=['test_cross_platform','test_watermark_controls','test_watermark_typography']
WINDOWS_TESTS=['test_port','test_v3','test_optimization','test_m3_guard','test_gpu_v7',
    'test_m3_core','test_pipeline_v9','test_merge_v12','test_cache_v12',
    'test_optimization_v13','test_film_reshooter',*PORTABLE_TESTS]


def call(args,env=None):
    return subprocess.call([str(a) for a in args],cwd=ROOT,env=env)


def native_macos():
    if platform.machine()!='arm64':raise RuntimeError('macOS native builds currently target Apple Silicon arm64.')
    sdk=subprocess.check_output(['xcrun','--show-sdk-path'],text=True).strip()
    cc=subprocess.check_output(['xcrun','--find','clang'],text=True).strip()
    common=['-dynamiclib','-isysroot',sdk,'-O3','-ffp-contract=off','-fPIC','-arch','arm64','-mmacosx-version-min=14.0']
    targets=[('native_post.c','cameralook_post',[]),
        ('native_m3_core.c','cameralook_m3_core',['-fno-strict-aliasing','-DCAMERALOOK_M3_EXACT_PREPARE=1']),
        ('native_m3_guard.c','cameralook_m3',['-fno-strict-aliasing','-fwrapv']),
        ('native_m9_tiles.c','cameralook_m9_tiles',['-fno-strict-aliasing']),
        ('native_hdr.c','cameralook_hdr',[]),
        ('metal_tonefilm.m','cameralook_metal',['-fobjc-arc','-framework','Foundation','-framework','Metal'])]
    folder=ROOT/'assets/native';folder.mkdir(parents=True,exist_ok=True)
    for source,name,flags in targets:
        code=call([cc,*common,*flags,'-I',ROOT/'tools',ROOT/'tools'/source,'-o',folder/(name+'.dylib')])
        if code:return code
    return 0


def doctor():
    packages=('numpy','Pillow','PySide6-Essentials','moderngl','glcontext','pillow-heif',
              'piexif','unicorn','pyelftools','rawpy','tifffile','imagecodecs','ExifRead')
    installed={};missing=[]
    for name in packages:
        try:installed[name]=importlib.metadata.version(name)
        except importlib.metadata.PackageNotFoundError:missing.append(name)
    try:
        import onnxruntime as ort
        providers=ort.get_available_providers()
    except ImportError:providers=[];missing.append('onnxruntime-directml (Windows) / onnxruntime (macOS)')
    paths=['assets/catalog.json','assets/leica_filter_param_m3.bin','assets/monopan_tables.npz',
           'research/models/high.onnx','research/models/low.onnx','research/models/colorfix.onnx']
    native=('cameralook_post','cameralook_m3','cameralook_m3_core','cameralook_m9_tiles','cameralook_hdr')
    if sys.platform=='darwin':native+=('cameralook_metal',)
    suffix='.dll' if sys.platform=='win32' else '.dylib'
    paths += ['assets/native/'+name+suffix for name in native]
    missing_files=[name for name in paths if not (ROOT/name).is_file()]
    supported=(sys.platform=='win32' and platform.machine().upper() in ('AMD64','X86_64')) or (sys.platform=='darwin' and platform.machine()=='arm64')
    if sys.platform=='darwin':
        try:supported=supported and int(platform.mac_ver()[0].split('.')[0])>=14
        except ValueError:supported=False
    report=dict(python=sys.version,platform=platform.platform(),machine=platform.machine(),
        host_is_supported_target=supported,dependencies=installed,onnx_providers=providers,
        missing_dependencies=missing,missing_files=missing_files,
        nvidia_optional_installed=(ROOT/'assets/nvidia_runtime/onnxruntime_ep_nv_tensorrt_rtx').is_dir())
    print(json.dumps(report,ensure_ascii=False,indent=2))
    return int(bool(missing or missing_files or not supported))


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command',choices=('doctor','run','test','native','build','verify'))
    parser.add_argument('--edition',choices=('standard','full'),default='standard')
    parser.add_argument('--portable',action='store_true',help='Run platform-independent tests only')
    parser.add_argument('--zig',help='Windows native compiler (Zig 0.13.0)')
    args,extra=parser.parse_known_args()
    if args.command=='run':return call([sys.executable,ROOT/'app.py',*extra])
    if extra:parser.error('Extra arguments are supported only by run')
    if args.command=='doctor':return doctor()
    if args.command=='verify':return call([sys.executable,'verify_source.py'])
    if args.command=='test':
        tests=list(PORTABLE_TESTS if args.portable or sys.platform!='win32' else WINDOWS_TESTS)
        if sys.platform=='win32' and not args.portable and (ROOT/'assets/nvidia_runtime/onnxruntime_ep_nv_tensorrt_rtx').is_dir():tests+=['test_resident_v10']
        code=call([sys.executable,'-m','unittest',*tests,'-v'])
        if code:return code
        if sys.platform=='darwin' and not args.portable:return call([sys.executable,'metal_regression.py'])
        return 0
    if sys.platform not in ('win32','darwin'):parser.error('Native build targets are Windows x64 and macOS arm64.')
    if args.command=='build':
        if sys.platform=='darwin':
            if platform.machine()!='arm64':parser.error('The macOS bundle targets Apple Silicon arm64.')
            return call([sys.executable,'-m','PyInstaller','--noconfirm','CameraLook-macos.spec'])
        if args.edition=='full' and not (ROOT/'assets/nvidia_runtime/onnxruntime_ep_nv_tensorrt_rtx').is_dir():
            parser.error('Install the optional NVIDIA runtime first: python tools/install_nvidia.py')
        env={**os.environ,'CAMERALOOK_INCLUDE_NVIDIA':'1' if args.edition=='full' else '0'}
        return call([sys.executable,'-m','PyInstaller','--noconfirm','--workpath','build/'+args.edition,'CameraLook.spec'],env)
    if sys.platform=='darwin':return native_macos()
    if platform.machine().upper() not in ('AMD64','X86_64'):parser.error('Windows native builds target x64.')
    zig=args.zig or os.environ.get('CAMERALOOK_ZIG') or shutil.which('zig')
    if not zig:parser.error('Provide --zig PATH or put Zig 0.13.0 on PATH.')
    zig=Path(shutil.which(zig) or zig).expanduser().resolve()
    if not zig.is_file():parser.error('Zig executable does not exist.')
    env={**os.environ,'CAMERALOOK_ZIG':str(zig)}
    for name in ('build_native_post.py','build_m3_guard.py','build_m3_core.py','build_m9_tiles.py','build_native_hdr.py'):
        code=call([sys.executable,ROOT/'tools'/name],env)
        if code:return code
    return call([sys.executable,ROOT/'tools/build_m3_core.py','--probe'],env)


if __name__=='__main__':raise SystemExit(main())
