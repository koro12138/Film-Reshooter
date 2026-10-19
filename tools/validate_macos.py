"""Headless acceptance check for the macOS build (source tree or bundled .app).

Run from the source directory:
    ../.venv/bin/python tools/validate_macos.py
or against a built bundle:
    ../.venv/bin/python tools/validate_macos.py --app dist/CameraLook.app

The Windows regression suite (`dev.py test`) asserts DirectML/OpenGL 4.3 output,
so those cases cannot run here. This script keeps the platform-neutral coverage:
LUT tone/film math, EXIF-aware watermark typography, every export format, the
M9 ONNX path, the native M3 chain and the Qt UI, and records real timings.
"""
import argparse
import json
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def check_source():
    report = {'stage': 'source', 'platform': sys.platform, 'machine': os.uname().machine}
    sys.path.insert(0, str(ROOT))
    import numpy as np
    from PIL import Image
    import engine
    import native_lib
    from engine import Renderer, CATALOG

    report['native_backend'] = native_lib.backend_name()
    report['native_libraries'] = {name: str(native_lib.path(name)) for name in
                                  ('cameralook_post', 'cameralook_m3',
                                   'cameralook_m3_core', 'cameralook_m9_tiles')}

    source = next(p for p in sorted((ROOT / 'examples').glob('*.jpg')))
    original = Image.open(source).convert('RGB')
    original.thumbnail((800, 800))
    report['sample'] = {'path': source.name, 'size': original.size}

    started = time.perf_counter()
    renderer = Renderer('auto')
    report['renderer'] = renderer.name
    report['renderer_fallback'] = renderer.fallback_reason

    report['lut'] = []
    for index in (0, 3, 22):
        step = time.perf_counter()
        out = renderer.render(original, index)
        assert out.size == original.size
        report['lut'].append({'index': index, 'name': CATALOG[index]['name'],
                              'seconds': round(time.perf_counter() - step, 3),
                              'report': dict(renderer.last_report)})

    step = time.perf_counter()
    m3 = renderer.render(original, 25)
    assert m3.size == original.size
    report['m3'] = {'seconds': round(time.perf_counter() - step, 3), 'report': dict(renderer.m3.last_report)}
    assert report['m3']['report']['guard_backend'] == native_lib.backend_name()
    assert report['m3']['report']['prepare_backend'] == native_lib.backend_name()
    assert report['m3']['report']['base_backend'] == native_lib.backend_name()
    assert report['m3']['report']['arm_engines'] == 0

    step = time.perf_counter()
    m9 = renderer.render(original, 23)
    assert m9.size == original.size
    report['m9'] = {'seconds': round(time.perf_counter() - step, 3), 'report': dict(renderer.m9.last_report)}
    report['m9_fallback'] = renderer.m9.inference_fallback

    import app as ui_module
    from app import Options, apply_mark
    from photos import PhotoInfo, export_photo, load_photo, get_font
    import tempfile
    out_dir = Path(tempfile.mkdtemp(prefix='filmreshooter-macos-source-'))
    info = PhotoInfo(Path('DEMO.jpg'), 1024, 768, 'SONY', 'ILCE-7RM2',
                     '2025-08-09 16:12:34', 35, 2.8, 1 / 250, '200',
                     latitude=31.2304, longitude=121.4737)
    report['font'] = {'regular': list(get_font(20).getname()),
                      'bold': list(get_font(20, True).getname())}

    marked = apply_mark(original, info, Options(style='original'), CATALOG[0]['name'])
    report['watermark'] = {'size': marked.size, 'expanded': marked.size != original.size}

    report['exports'] = []
    _, _, exif_data, _ = load_photo(source)
    for fmt in ('JPEG', 'PNG', 'TIFF 16-bit', 'PNG 16-bit', 'Ultra HDR JPEG'):
        step = time.perf_counter()
        marked_fmt = apply_mark(original, info, Options(style='original', fmt=fmt), CATALOG[0]['name'])
        target, notes = export_photo(marked_fmt, out_dir, 'check', 'macos', exif_data, fmt)
        assert target.is_file() and target.stat().st_size > 0
        report['exports'].append({'format': fmt, 'file': target.name,
                                  'bytes': target.stat().st_size,
                                  'seconds': round(time.perf_counter() - step, 3),
                                  'notes': notes})

    # The watermark band has no EXIF of its own, so a JPEG export must still carry
    # the original camera metadata or the whole point of the tool is lost.
    jpeg = out_dir / report['exports'][0]['file']
    roundtrip, roundtrip_info, _, _ = load_photo(jpeg)
    origin, origin_info, _, _ = load_photo(source)
    report['exif_roundtrip'] = {'source_camera': origin_info.camera,
                                'camera': roundtrip_info.camera,
                                'date': roundtrip_info.date,
                                'settings': roundtrip_info.settings,
                                'size': roundtrip.size}
    assert roundtrip_info.camera == origin_info.camera, report['exif_roundtrip']
    assert roundtrip_info.date == origin_info.date, report['exif_roundtrip']
    assert roundtrip_info.settings == origin_info.settings, report['exif_roundtrip']

    renderer.close()
    report['total_seconds'] = round(time.perf_counter() - started, 2)
    report['ok'] = True
    return report


def check_bundle(app_path):
    """Launch the frozen app, render one photo and dump what it reports."""
    app_path = Path(app_path).resolve()
    # Derive the executable name so a renamed build still validates.
    executable = app_path / 'Contents' / 'MacOS' / 'Film Reshooter'
    try:
        import plistlib
        with open(app_path / 'Contents' / 'Info.plist', 'rb') as fh:
            executable = app_path / 'Contents' / 'MacOS' / plistlib.load(fh)['CFBundleExecutable']
    except Exception:
        pass
    binary = executable
    assert binary.is_file(), f'缺少可执行文件: {binary}'
    report = {'stage': 'bundle', 'binary': str(binary),
              'arch': subprocess.check_output(['file', '-b', str(binary)], text=True).strip()}
    import tempfile
    out_dir = Path(tempfile.mkdtemp(prefix='filmreshooter-macos-bundle-'))
    script = out_dir / 'probe.py'
    script.write_text(
        'import json,os,sys\n'
        'sys.argv=[a for a in sys.argv if not a.startswith("--self-test")]\n'
        'from PySide6.QtWidgets import QApplication\n'
        'import app as A\n'
        'from engine import Renderer,CATALOG\n'
        'from PIL import Image\n'
        'qapp=QApplication([]);A.configure_fonts(qapp)\n'
        'w=A.MainWindow()\n'
        'r=Renderer("auto")\n'
        'im=Image.new("RGB",(480,360),"#688e84")\n'
        'out=r.render(im,0)\n'
        'json.dump({"title":w.windowTitle(),"renderer":r.name,"size":out.size,\n'
        '           "backend":w.backend.currentText()},open(sys.argv[-1],"w"))\n',
        'utf-8')
    env = dict(os.environ, QT_QPA_PLATFORM='offscreen',
               PYINSTALLER_SUPPRESS_SPLASH_SCREEN='1')
    # The frozen interpreter only understands the bundled entry point, so use the
    # app's own self-test hook instead of an external script.
    result = subprocess.run([str(binary), '--self-test', str(out_dir)],
                            capture_output=True, text=True, timeout=1800, env=env)
    report['exit_code'] = result.returncode
    report['stdout'] = result.stdout[-4000:]
    report['stderr'] = result.stderr[-4000:]
    produced = out_dir / 'packaged_test.json'
    if produced.is_file():
        report['self_test'] = json.loads(produced.read_text('utf-8'))
    bootstrap = out_dir / 'bootstrap.log'
    if bootstrap.is_file():
        report['bootstrap_log'] = bootstrap.read_text('utf-8')[-4000:]
    report['outputs'] = sorted(p.name for p in out_dir.iterdir())
    report['ok'] = result.returncode == 0 and report.get('self_test', {}).get('ok') is True
    return report


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--app', help='Path to CameraLook.app; omit to check the source tree')
    parser.add_argument('--json', help='Write the report here')
    args = parser.parse_args()
    if sys.platform!='darwin':parser.error('Run this validation on macOS; Windows mocks are not a device test.')
    report = check_bundle(args.app) if args.app else check_source()
    text = json.dumps(report, ensure_ascii=False, indent=2, default=str)
    print(text)
    if args.json:
        Path(args.json).write_text(text, 'utf-8')
    return 0 if report.get('ok') else 1


if __name__ == '__main__':
    raise SystemExit(main())
