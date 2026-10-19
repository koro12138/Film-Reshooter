# Build: python -m PyInstaller --noconfirm CameraLook.spec
from pathlib import Path
import os
import json
from PyInstaller.utils.hooks import collect_submodules, collect_dynamic_libs

root = Path(SPECPATH)
include_nvidia=os.environ.get('CAMERALOOK_INCLUDE_NVIDIA','1')=='1'
edition='full' if include_nvidia else 'standard'
release_name = os.environ.get('CAMERALOOK_RELEASE_NAME','FilmReshooter-v1.0.0-'+edition.capitalize())
config=root/'build/release_config'/edition/'release_edition.json'
config.parent.mkdir(parents=True,exist_ok=True)
config.write_text(json.dumps({'edition':edition,'nvidia':include_nvidia,'version':'1.0.0'}),encoding='utf-8')
hidden = collect_submodules('glcontext') + ['_moderngl', 'PIL.ImageCms', 'pillow_heif']
hidden += ['rawpy._rawpy','imagecodecs._imcd','imagecodecs._png','imagecodecs._cms',
           'imagecodecs._ultrahdr','imagecodecs._deflate','imagecodecs._jpeg8','imagecodecs._zlib','imagecodecs._shared_cython']
hidden += collect_submodules('unicorn') + collect_submodules('elftools')
binaries = collect_dynamic_libs('pillow_heif')
binaries += collect_dynamic_libs('onnxruntime')
binaries += collect_dynamic_libs('rawpy') + collect_dynamic_libs('imagecodecs') + collect_dynamic_libs('unicorn')
datas = [(str(root/'assets/catalog.json'), 'assets')]
datas += [(str(config),'.')]
datas += [(str(p),'assets/branding') for p in (root/'assets/branding').glob('*') if p.is_file()]
datas += [(str(p),'assets/ui') for p in (root/'assets/ui').iterdir() if p.suffix.lower() in ('.svg','.png')]
datas += [(str(p),str(p.parent.relative_to(root))) for p in (root/'assets/previews').rglob('*') if p.is_file()]
binaries += [(str(root/'assets/native/cameralook_post.dll'),'assets/native')]
binaries += [(str(root/'assets/native/cameralook_m3.dll'),'assets/native')]
binaries += [(str(root/'assets/native/cameralook_m3_core.dll'),'assets/native')]
binaries += [(str(root/'assets/native/cameralook_m9_tiles.dll'),'assets/native')]
binaries += [(str(root/'assets/native/cameralook_hdr.dll'),'assets/native')]
if include_nvidia:
    datas += [(str(root/'assets/native/m9_resident.ptx'),'assets/native')]
    datas += [(str(root/'assets/m9_models/colorfix_batch.onnx'),'assets/m9_models')]
# Optional EP stays separate from the installed DirectML Python package. Its
# ordinary Python package loads from this directory in source and frozen builds.
nvidia_package=root/'assets/nvidia_runtime/onnxruntime_ep_nv_tensorrt_rtx'
if include_nvidia and nvidia_package.is_dir():
    for p in nvidia_package.iterdir():
        if p.suffix.lower()=='.dll':binaries.append((str(p),'assets/nvidia_runtime/onnxruntime_ep_nv_tensorrt_rtx'))
        elif p.suffix.lower() in ('.py','.txt'):
            datas.append((str(p),'assets/nvidia_runtime/onnxruntime_ep_nv_tensorrt_rtx'))
datas += [(str(p), 'assets/cameralook') for p in (root/'assets/cameralook').glob('tone-*.lut')]
datas += [(str(root/'assets/cameralook/author-notice.bin'), 'assets/cameralook')]
datas += [(str(p), str(p.parent.relative_to(root))) for p in (root/'assets/watermarks').rglob('*') if p.is_file()]
datas += [(str(p), 'assets/fonts') for p in (root/'assets/fonts').glob('*') if p.is_file()]
datas += [(str(p), 'assets/m9_models') for p in (root/'research/models').glob('*.onnx')]
datas += [(str(root/'assets'/name),'assets') for name in ('math_arm.elf','monopan_tables.npz','leica_filter_param_m3.bin')]
datas += [(str(root/'assets/fullm9/leica_filter_param_m9_snapshot.bin'),'assets/fullm9')]
datas += [(str(root/'lib/arm64-v8a'/name),'lib/arm64-v8a') for name in
          ('libfullm9.so','libleicadenoise.so','libzxbase.so','libzxicamodelembed.so')]
datas += [(str(root/'research/synthetic_test.dng'),'assets/diagnostics')]
datas += [(str(p),str(p.parent.relative_to(root))) for p in (root/'第三方许可').rglob('*')
          if p.is_file() and (include_nvidia or 'NVIDIA' not in p.parts)]
datas += [(str(root/'THIRD_PARTY_NOTICE.md'),'.')]
a = Analysis([str(root/'app.py')], pathex=[str(root)], binaries=binaries, datas=datas,
    hiddenimports=hidden, hookspath=[], hooksconfig={}, runtime_hooks=[],
    excludes=['torch','onnx','cv2','matplotlib','scipy','pandas','IPython','tkinter',
              'PySide6.QtWebEngineCore','PySide6.QtWebEngineWidgets','PySide6.QtQml','PySide6.QtQuick']+
             ([] if include_nvidia else ['nvidia_backend','cuda_tiles','onnxruntime_ep_nv_tensorrt_rtx']),
    noarchive=False)
# Qt 6.12 links Windows' unversioned ICU API. An unrelated Poppler icuuc.dll
# on the build host PATH exports versioned symbols and must never shadow it.
# Also avoid bundling host-specific Windows API-set stubs discovered via PATH.
a.binaries = [entry for entry in a.binaries
    if Path(entry[0]).name.lower() not in {'icuuc.dll', 'icudt78.dll', 'ucrtbase.dll'}
    and not Path(entry[0]).name.lower().startswith('api-ms-win-')]
pyz = PYZ(a.pure)
exe = EXE(pyz, a.scripts, [], exclude_binaries=True, name='FilmReshooter', debug=False,
    bootloader_ignore_signals=False, strip=False, upx=False, console=os.environ.get('CAMERALOOK_CONSOLE')=='1',
    disable_windowed_traceback=False,icon=str(root/'assets/branding/FilmReshooter.ico'),version=str(root/'tools/film_version.txt'))
coll = COLLECT(exe, a.binaries, a.datas, strip=False, upx=False, name=release_name)
# The stock MSVC bootloader opts the process into CFG, which rejects Unicorn's
# JIT longjmp. Apply --no-cfg-equivalent PE declarations to this app only.
import runpy
runpy.run_path(str(root/'tools/fix_exe_cfg.py'))['disable_cfg'](root/'dist'/release_name/'FilmReshooter.exe')
