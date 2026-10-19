"""Repeatable performance audit for the shipped macOS pipeline.

Measures the stages a user actually waits for, one photo at a time, and prints
medians so run-to-run noise does not get mistaken for a change.

    python3 perf_audit.py [--repeats 5] [--size 6000x4000]
"""
import argparse
import gc
import json
import statistics
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parent


def synthetic(width, height, seed=1):
    rng = np.random.default_rng(seed)
    y, x = np.mgrid[0:height, 0:width]
    base = np.stack([(x * 255 // max(1, width)), (y * 255 // max(1, height)),
                     ((x * 3 + y * 5) % 256)], -1).astype(np.float32)
    base += rng.normal(0, 10, (height, width, 3))
    checker = (((x // 64 + y // 64) % 2 == 0)[..., None] * 18.0)
    return Image.fromarray(np.clip(base + checker - 9, 0, 255).astype(np.uint8))


def timed(fn, repeats):
    samples = []
    for _ in range(repeats):
        gc.collect()
        start = time.perf_counter()
        fn()
        samples.append(time.perf_counter() - start)
    return statistics.median(samples), min(samples), max(samples)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--repeats', type=int, default=5)
    ap.add_argument('--size', default='6000x4000')
    args = ap.parse_args()
    width, height = (int(v) for v in args.size.lower().split('x'))

    from engine import Renderer, CATALOG
    import m3
    from m9 import M9Renderer
    from photos import PhotoInfo, export_photo, watermark
    from original_marks import render_original
    from types import SimpleNamespace

    image = synthetic(width, height)
    megapixels = width * height / 1e6
    print(f'image {width}x{height} ({megapixels:.1f} MP), repeats {args.repeats}')
    results = []

    def record(name, fn, note=''):
        median, low, high = timed(fn, args.repeats)
        results.append({'stage': name, 'median_ms': round(median * 1000, 1),
                        'min_ms': round(low * 1000, 1), 'max_ms': round(high * 1000, 1),
                        'note': note})
        print(f'  {name:28s} {median*1000:8.1f} ms   (min {low*1000:7.1f} / max {high*1000:7.1f})  {note}')

    renderer = Renderer('auto')
    renderer.render(image, 0)          # warm up libraries and model sessions
    print(f'  backend: {getattr(renderer, "name", getattr(renderer, "backend", "?"))}')
    print(f'  last report: {renderer.last_report}')

    record('LUT 滤镜 01', lambda: renderer.render(image, 0))
    record('LUT 滤镜 08', lambda: renderer.render(image, 7))
    grain_index = next((i for i, f in enumerate(CATALOG) if f.get('grain')), 0)
    record(f'LUT 滤镜 {grain_index+1:02d} (含颗粒)', lambda: renderer.render(image, grain_index))
    record('M9 滤镜', lambda: renderer.render(image, 23))
    record('M3 滤镜', lambda: renderer.render(image, 25))

    info = PhotoInfo(Path('/tmp/x.jpg'), width, height, 'SONY', 'ILCE-7RM2',
                     '2026-10-18 11:03:56', 35, 2.8, 1/250, '400',
                     latitude=25.068143, longitude=102.693241)
    marked = image
    record('原版水印模板 (leica/1)',
           lambda: render_original(image, info, 'leica/1',
                                   SimpleNamespace(original_template='leica/1', original_variant='',
                                                   original_background='', title='', caption='',
                                                   details=True, date=True, time=True, device=True,
                                                   brand=True, location=True, fallback='',
                                                   override=False, signature='', signature_image='',
                                                   location_label=''), '', ''))
    record('白框水印', lambda: watermark(image, info, 'white'))

    out = Path('/tmp/perf_audit_out')
    out.mkdir(parents=True, exist_ok=True)
    record('导出 JPEG 97 4:4:4',
           lambda: export_photo(image, out, 'audit', 'bench', None, 'JPEG', 97, False))
    record('导出 PNG', lambda: export_photo(image, out, 'audit', 'bench', None, 'PNG', 97, False))
    record('导出 TIFF 16bit',
           lambda: export_photo(image, out, 'audit', 'bench', None, 'TIFF 16-bit', 97, False))

    small = image.resize((320, 213), Image.Resampling.BILINEAR)
    record('预览渲染 1080 短边',
           lambda: renderer.render(image.resize((1620, 1080), Image.Resampling.BILINEAR), lut_index))

    print()
    print(json.dumps({'image': f'{width}x{height}', 'backend': getattr(renderer, 'backend', '?'),
                      'results': results}, ensure_ascii=False, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
