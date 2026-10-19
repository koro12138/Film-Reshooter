# macOS bundle build: <venv>/python -m PyInstaller --noconfirm CameraLook-macos.spec
#
# Produces dist/CameraLook.app (windowed, arm64) with every runtime asset the
# Windows spec also ships, minus the Windows-only NVIDIA runtime and DLLs.
# Signing is ad-hoc; replace CODESIGN_IDENTITY to notarize for distribution.
from pathlib import Path
import os
import json
from PyInstaller.utils.hooks import collect_submodules, collect_dynamic_libs

root = Path(SPECPATH)
# Shipped name. The source tree is still the v11 CameraLook codebase, but the
# product, bundle identity and icon are Film Reshooter.
app_name = os.environ.get('CAMERALOOK_APP_NAME', 'Film Reshooter')
bundle_id = os.environ.get('CAMERALOOK_BUNDLE_ID', 'com.filmreshooter.desktop')
version = os.environ.get('CAMERALOOK_VERSION', '1.0.0')
icon = root / 'assets' / 'macos' / 'FilmReshooter.icns'

hidden = collect_submodules('glcontext') + ['_moderngl', 'PIL.ImageCms', 'pillow_heif']
hidden += ['rawpy._rawpy', 'imagecodecs._imcd', 'imagecodecs._png', 'imagecodecs._cms',
           'imagecodecs._ultrahdr', 'imagecodecs._deflate', 'imagecodecs._jpeg8',
           'imagecodecs._zlib', 'imagecodecs._shared_cython']
hidden += collect_submodules('unicorn') + collect_submodules('elftools')
# Imported lazily inside engine.Renderer, so PyInstaller cannot see it.
hidden += ['metal_renderer']

binaries = collect_dynamic_libs('pillow_heif')
binaries += collect_dynamic_libs('onnxruntime')
binaries += collect_dynamic_libs('rawpy') + collect_dynamic_libs('imagecodecs') + collect_dynamic_libs('unicorn')
# The five clang-built dylibs (cameralook_metal is the ObjC/Metal backend and
# links Foundation + Metal). A universal build would need x86_64 slices too;
# this spec intentionally targets the arm64 host only.
for name in ('cameralook_post', 'cameralook_m3', 'cameralook_m3_core',
             'cameralook_m9_tiles', 'cameralook_hdr', 'cameralook_metal'):
    path = root / 'assets' / 'native' / f'{name}.dylib'
    if not path.is_file():raise FileNotFoundError(f'{path}: run python dev.py native first')
    binaries.append((str(path), 'assets/native'))

config=root/'build/release_config/macos/release_edition.json'
config.parent.mkdir(parents=True,exist_ok=True)
config.write_text(json.dumps({'edition':'macos','nvidia':False,'version':version}),encoding='utf-8')
datas = [(str(root / 'assets/catalog.json'), 'assets'),(str(config),'.')]
datas += [(str(p),'assets/branding') for p in (root/'assets/branding').glob('*') if p.is_file()]
datas += [(str(p),'assets/macos') for p in (root/'assets/macos').glob('*') if p.is_file()]
datas += [(str(p), 'assets/ui') for p in (root / 'assets/ui').iterdir()
         if p.is_file() and p.suffix.lower() in ('.svg', '.png')]
datas += [(str(p), str(p.parent.relative_to(root))) for p in (root / 'assets/previews').rglob('*') if p.is_file()]
datas += [(str(root / 'assets/m9_models/colorfix_batch.onnx'), 'assets/m9_models')]
datas += [(str(p), 'assets/cameralook') for p in (root / 'assets/cameralook').glob('tone-*.lut')]
datas += [(str(root / 'assets/cameralook/author-notice.bin'), 'assets/cameralook')]
datas += [(str(p), str(p.parent.relative_to(root))) for p in (root / 'assets/watermarks').rglob('*') if p.is_file()]
datas += [(str(p), 'assets/fonts') for p in (root / 'assets/fonts').glob('*') if p.is_file()]
datas += [(str(p), 'assets/m9_models') for p in (root / 'research/models').glob('*.onnx')]
datas += [(str(root / 'assets' / name), 'assets')
          for name in ('math_arm.elf', 'monopan_tables.npz', 'leica_filter_param_m3.bin')]
datas += [(str(root / 'assets/fullm9/leica_filter_param_m9_snapshot.bin'), 'assets/fullm9')]
# Android ARM64 oracle libraries stay bundled: PORTING.md keeps them as the
# reference implementation, and they are loaded through Unicorn, not dlopen.
for name in ('libfullm9.so', 'libleicadenoise.so', 'libzxbase.so', 'libzxicamodelembed.so'):
    path = root / 'lib/arm64-v8a' / name
    if path.is_file():
        datas.append((str(path), 'lib/arm64-v8a'))
datas += [(str(root / 'research/synthetic_test.dng'), 'assets/diagnostics')]
datas += [(str(root / 'THIRD_PARTY_NOTICE.md'), '.')]
datas += [(str(p),str(p.parent.relative_to(root))) for p in (root/'第三方许可').rglob('*')
          if p.is_file() and 'NVIDIA' not in p.parts]

a = Analysis([str(root / 'app.py')], pathex=[str(root)], binaries=binaries, datas=datas,
             hiddenimports=hidden, hookspath=[], hooksconfig={}, runtime_hooks=[],
             excludes=['torch', 'onnx', 'cv2', 'matplotlib', 'scipy', 'pandas', 'IPython', 'tkinter',
                       'PySide6.QtWebEngineCore', 'PySide6.QtWebEngineWidgets', 'PySide6.QtQml',
                       'PySide6.QtQuick', 'PySide6.QtMultimedia', 'PySide6.Qt3DCore',
                       'nvidia_backend','cuda_tiles'],
             noarchive=False)
# Windows-only components must never end up inside the macOS bundle.
a.binaries = [entry for entry in a.binaries
              if Path(entry[0]).suffix.lower() not in ('.dll', '.pyd', '.lib')]
pyz = PYZ(a.pure)
exe = EXE(pyz, a.scripts, [], exclude_binaries=True, name=app_name, debug=False,
          bootloader_ignore_signals=False, strip=False, upx=False,
          console=os.environ.get('CAMERALOOK_CONSOLE') == '1',
          disable_windowed_traceback=False, target_arch='arm64')
coll = COLLECT(exe, a.binaries, a.datas, strip=False, upx=False, name=app_name)
app = BUNDLE(coll, name=f'{app_name}.app', icon=str(icon) if icon.is_file() else None,
             bundle_identifier=bundle_id,
             version=version,
             info_plist={
                 'CFBundleName': app_name,
                 'CFBundleDisplayName': app_name,
                 'CFBundleShortVersionString': version,
                 'CFBundleVersion': version,
                 'CFBundleGetInfoString': 'Film Reshooter ver1.0.0',
                 'NSHighResolutionCapable': True,
                 'NSRequiresAquaSystemAppearance': False,
                 'LSMinimumSystemVersion': '14.0',
                 'LSApplicationCategoryType': 'public.app-category.photography',
                 'NSSupportsAutomaticGraphicsSwitching': True,
                 # Opened photos come through the standard open panel; no sandbox
                 # entitlements are claimed because the app writes user-chosen
                 # output folders directly.
                 'CFBundleDocumentTypes': [{
                     'CFBundleTypeName': 'Image',
                     'CFBundleTypeRole': 'Editor',
                     'LSHandlerRank': 'Alternate',
                     'LSItemContentTypes': ['public.image'],
                 }],
             })
