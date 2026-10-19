"""Regression: Metal backend vs the NumPy reference, all 23 LUT filters.

Acceptance follows the project's own cross-implementation standard
(test_port.py: max |diff| <= 2, mean < 0.005).
"""
import sys
import numpy as np
from PIL import Image

sys.path.insert(0, '.')

MAX_OK = 2
MEAN_OK = 0.005


def fixture(w=640, h=427, seed=11):
    """Textured, high-contrast content with smooth gradients and hard edges."""
    rng = np.random.default_rng(seed)
    y, x = np.mgrid[0:h, 0:w]
    base = np.stack([x * 255 // w, y * 255 // h, (x * 3 + y * 5) % 256], -1).astype(np.float32)
    base += rng.normal(0, 9, (h, w, 3))
    checker = (((x // 37 + y // 29) % 2 == 0)[..., None] * 30.0)
    base += checker - 15
    # a blown highlight + deep shadow patch to exercise the luma-ratio branch
    base[h // 8:h // 4, w // 8:w // 4] = 252
    base[h // 2:h // 2 + 20, w // 2:w // 2 + 40] = 3
    return Image.fromarray(np.clip(base, 0, 255).astype(np.uint8))


def compare(a, b):
    da = np.asarray(a).astype(np.int16)
    db = np.asarray(b).astype(np.int16)
    d = np.abs(da - db)
    return int(d.max()), float(d.mean()), float((d == 0).mean())


def main():
    from engine import Renderer, CATALOG
    img = fixture()
    print(f'fixture {img.size[0]}x{img.size[1]}  filters={len(CATALOG)}\n')
    cpu = Renderer('cpu')
    metal = Renderer('auto')
    assert 'Metal' in metal.name, f'Metal backend not active: {metal.name}'

    failures = []
    print(f"{'idx':>3} {'name':<18} {'strength':>8} {'max':>4} {'mean':>9} {'exact%':>7}")
    for idx in range(23):
        for strength in (1.0, 0.7):
            ref = cpu.render(img, idx, strength)
            got = metal.render(img, idx, strength)
            mx, mean, exact = compare(ref, got)
            ok = mx <= MAX_OK and mean < MEAN_OK
            if not ok:
                failures.append((idx, strength, mx, mean))
            print(f'{idx:3d} {CATALOG[idx]["name"]:<18} {strength:8.2f} {mx:4d} {mean:9.6f} {exact*100:6.2f}%'
                  + ('' if ok else '   <-- FAIL'))

    # high-precision (float32) path
    print('\nhigh-depth float32 path')
    for idx in (0, 3, 14, 22):
        hi = img.copy()
        arr = np.asarray(hi, np.float32) / 255
        hi.info['rgb_float'] = arr + np.float32(0.0021)   # sub-byte offset
        ref = cpu.render(hi, idx)
        got = metal.render(hi, idx)
        rf = ref.info.get('rgb_float')
        gf = got.info.get('rgb_float')
        if rf is None or gf is None:
            print(f'{idx:3d} {CATALOG[idx]["name"]:<18} missing rgb_float  <-- FAIL')
            failures.append((idx, 'float', -1, -1))
            continue
        d = np.abs(rf - gf) * 255
        mx, mean = float(d.max()), float(d.mean())
        ok = mx <= MAX_OK and mean < MEAN_OK
        if not ok:
            failures.append((idx, 'float', mx, mean))
        print(f'{idx:3d} {CATALOG[idx]["name"]:<18} max={mx:.3f} mean={mean:.6f}'
              + ('' if ok else '   <-- FAIL'))

    # Monopan grain (M3) must be bit-exact: it is pure integer table lookups
    print('\nMonopan grain (M3) vs m3.grain_cpu')
    import m3
    from engine import Renderer as _R
    for shade, seed in (('#6a7f8c', 4), ('#101010', 7), ('#f0f0f0', 9), ('#c05030', 11)):
        rng = np.random.default_rng(seed)
        hh, ww = 200, 320
        base = np.asarray(Image.new('RGB', (ww, hh), shade)).astype(np.int16)
        base += rng.integers(-30, 30, (hh, ww, 3))
        pad = np.pad(np.clip(base, 0, 255).astype(np.uint8),
                     ((0, hh % 2), (0, (-ww) % 8), (0, 0)), mode='edge')
        ref = m3.grain_cpu(pad)
        got = metal.gpu.monopan_grain(pad)
        d = np.abs(got.astype(np.int16) - ref.astype(np.int16))
        ok = d.max() == 0
        if not ok:
            failures.append(('monopan', shade, int(d.max()), float(d.mean())))
        print(f'  {shade:9s} max={d.max()} mean={d.mean():.6f} exact={(d==0).mean()*100:.2f}%'
              + ('' if ok else '   <-- FAIL'))

    # end_photo / reuse: same photo, several filters => single upload
    cpu.begin_photo(img)
    metal.begin_photo(img)
    before = metal.last_report.get('gpu_photo_uploads', 0)
    for idx in (0, 5, 15):
        metal.render(img, idx)
    rep = metal.last_report
    delta = rep['gpu_photo_uploads'] - before
    print(f"\nresident reuse: new uploads={delta} (total {rep['gpu_photo_uploads']}) "
          f"cache_hit={rep['gpu_photo_cache_hit']}")
    if delta != 1:
        print('   <-- FAIL expected exactly one upload per photo')
        failures.append(('reuse', 1, -1, -1))
    cpu.end_photo()
    metal.end_photo()
    cpu.close()
    metal.close()

    print(f'\n{"PASS" if not failures else "FAIL"} ({len(failures)} failing case(s))')
    return 1 if failures else 0


if __name__ == '__main__':
    sys.exit(main())
