"""Metal compute backend for the LUT tone + film stages (macOS / Apple Silicon).

Drop-in replacement for `gpu.GpuRenderer`'s duck-typed interface used by
`engine.Renderer._render`: `cache_photo` / `clear_photo` / `tone_film` / `tone` /
`film` / `postprocessor` / `close`, plus `photo_cache_hit` / `photo_uploads`.

The heavy lifting lives in `assets/native/cameralook_metal.dylib`
(tools/metal_tonefilm.m); this module only marshals buffers and parameters.
The whole image is rendered in one dispatch, so the NumPy/OpenGL strip loop
disappears and `engine` sets `rows = h` when `whole_image` is set.
"""
import ctypes
import threading
from contextlib import contextmanager
import numpy as np

import native_lib
from engine import CATALOG, load_lut

_PARAM_FIELDS = (
    ('width', ctypes.c_int), ('height', ctypes.c_int), ('n', ctypes.c_int),
    ('rgb_count', ctypes.c_int), ('luma_count', ctypes.c_int), ('seed', ctypes.c_int),
    ('y0', ctypes.c_int), ('out_rows', ctypes.c_int), ('first', ctypes.c_int),
    ('tone_rows', ctypes.c_int), ('pad0', ctypes.c_int), ('pad1', ctypes.c_int),
    ('strength', ctypes.c_float), ('clarity', ctypes.c_float), ('midpoint', ctypes.c_float),
    ('vignette', ctypes.c_float), ('shadows', ctypes.c_float), ('midtones', ctypes.c_float),
    ('highlights', ctypes.c_float), ('grain', ctypes.c_float), ('grainSize', ctypes.c_float),
    ('roughness', ctypes.c_float), ('colorVariation', ctypes.c_float),
    ('ui_strength', ctypes.c_float),
)


class MetalParams(ctypes.Structure):
    _fields_ = _PARAM_FIELDS


_LOCK = threading.RLock()
_ACTIVE_OWNER = None


class _Library:
    """Process-wide handle to the Metal dylib (singletons: device + pipeline)."""

    def __init__(self):
        lib = native_lib.load('cameralook_metal')
        lib.cl_metal_available.restype = ctypes.c_int
        lib.cl_metal_init.restype = ctypes.c_int
        lib.cl_metal_device_name.argtypes = [ctypes.c_char_p, ctypes.c_int]
        lib.cl_metal_last_error.restype = ctypes.c_char_p
        lib.cl_metal_params_size.restype = ctypes.c_int
        lib.cl_metal_reserve.argtypes = [ctypes.c_int, ctypes.c_int]
        lib.cl_metal_reserve.restype = ctypes.c_int
        lib.cl_metal_set_lut.argtypes = [ctypes.c_void_p, ctypes.c_int]
        lib.cl_metal_set_lut.restype = ctypes.c_int
        lib.cl_metal_set_curves.argtypes = [ctypes.c_void_p, ctypes.c_int,
                                            ctypes.c_void_p, ctypes.c_int]
        lib.cl_metal_set_curves.restype = ctypes.c_int
        lib.cl_metal_upload.argtypes = [ctypes.c_void_p, ctypes.c_int]
        lib.cl_metal_upload.restype = ctypes.c_int
        lib.cl_metal_download.argtypes = [ctypes.c_void_p, ctypes.c_int]
        lib.cl_metal_download.restype = ctypes.c_int
        lib.cl_metal_render_u8.argtypes = [ctypes.POINTER(MetalParams)]
        lib.cl_metal_render_u8.restype = ctypes.c_int
        lib.cl_metal_render_f32.argtypes = [ctypes.POINTER(MetalParams)]
        lib.cl_metal_render_f32.restype = ctypes.c_int
        lib.cl_metal_output_denoise.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                                ctypes.c_int, ctypes.c_int, ctypes.c_int]
        lib.cl_metal_output_denoise.restype = ctypes.c_int
        lib.cl_metal_set_monopan.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                             ctypes.c_void_p, ctypes.c_void_p,
                                             ctypes.c_void_p, ctypes.c_void_p]
        lib.cl_metal_set_monopan.restype = ctypes.c_int
        lib.cl_metal_monopan_grain.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                               ctypes.c_int, ctypes.c_int]
        lib.cl_metal_monopan_grain.restype = ctypes.c_int
        lib.cl_metal_shutdown.argtypes = []
        if lib.cl_metal_params_size() != ctypes.sizeof(MetalParams):
            raise RuntimeError(f'Metal 参数结构尺寸不匹配：C={lib.cl_metal_params_size()} '
                               f'Python={ctypes.sizeof(MetalParams)}')
        self.lib = lib
        if not lib.cl_metal_init():
            self.close()
            raise RuntimeError('Metal 初始化失败：' + self.error())
        buf = ctypes.create_string_buffer(128)
        lib.cl_metal_device_name(buf, 128)
        self.device_name = buf.value.decode('utf-8', 'replace')

    def error(self):
        raw = self.lib.cl_metal_last_error()
        return raw.decode('utf-8', 'replace') if raw else 'unknown'

    def close(self):
        try:
            self.lib.cl_metal_shutdown()
        except Exception:
            pass


_LIB = None
_LIB_FAILED = None


def _library():
    with _LOCK:
        return _locked_library()


def _locked_library():
    global _LIB, _LIB_FAILED
    if _LIB is not None:
        return _LIB
    if _LIB_FAILED is not None:
        raise _LIB_FAILED
    try:
        _LIB = _Library()
    except Exception as exc:                     # keep the reason for the fallback report
        _LIB_FAILED = exc
        raise
    return _LIB


def available():
    try:
        _library()
        return True
    except Exception:
        return False


class MetalRenderer:
    """Whole-image Metal implementation of the tone + film pipeline."""

    whole_image = True                            # engine may dispatch the full frame
    applies_strength = True                       # the film kernel folds in the UI strength blend
    # 3 bytes/px on device; cap at 768 MB so a 200 MP scan still fits.
    MAX_RESIDENT_BYTES = 768 * 1024 * 1024

    @contextmanager
    def render_scope(self):
        """Protect the dylib's process-global device state across a whole photo.

        Preview and export use different renderer instances. Their local LUT
        and residency caches must be invalidated when ownership changes.
        """
        global _ACTIVE_OWNER
        with _LOCK:
            if _ACTIVE_OWNER is not self:
                self.clear_photo()
                self._curve_index = None
                self._capacity = 0
                self._monopan_ready = False
                _ACTIVE_OWNER = self
            yield

    def __init__(self):
        lib = _library()
        self._lib = lib.lib
        self.name = f'Metal · {lib.device_name}'
        self.ctx = None                            # no OpenGL context: m3 uses native/CPU grain
        self.photo_cache_hit = False
        self.photo_uploads = 0
        self._photo_key = None
        self._size = (0, 0)
        self._lut_cache = {}
        self._n = 0
        self._rgb_count = 2
        self._luma_count = 2
        self._curve_index = None
        self._capacity = 0

    # -- photo residency ---------------------------------------------------
    def cache_photo(self, rgb, key):
        h, w = rgb.shape[:2]
        nbytes = w * h * 3
        self.photo_cache_hit = self._photo_key is key
        if nbytes > self.MAX_RESIDENT_BYTES:
            return None
        with _LOCK:
            if not self._reserve(nbytes, 0):
                return None
            if self._photo_key is not key or self._size != (w, h):
                src = np.ascontiguousarray(rgb, dtype=np.uint8)
                if not self._lib.cl_metal_upload(src.ctypes.data, nbytes):
                    return None
                self._photo_key = key
                self._size = (w, h)
                self.photo_uploads += 1
        return (w, h)

    def clear_photo(self):
        self._photo_key = None
        self._size = (0, 0)

    def _reserve(self, photo_bytes, float_bytes):
        need = max(photo_bytes, float_bytes)
        if need <= self._capacity:
            return True
        if not self._lib.cl_metal_reserve(photo_bytes, float_bytes):
            return False
        self._capacity = need
        return True

    # -- per-filter state --------------------------------------------------
    def _configure(self, index):
        """Upload the LUT and curve tables for `index` (cached until it changes)."""
        if self._curve_index == index:
            return
        n, domain, lut = load_lut(index)
        padded = np.ones((len(lut), 4), np.float32)
        padded[:, :3] = lut
        padded = np.ascontiguousarray(padded)
        if not self._lib.cl_metal_set_lut(padded.ctypes.data, n):
            raise RuntimeError('Metal LUT 上传失败：' + self._lib_error())
        p = CATALOG[index]
        rgbc = np.ascontiguousarray(np.asarray(p['rgb'], np.float32).reshape(-1, 2))[:8]
        lumac = np.ascontiguousarray(np.asarray(p['luma'], np.float32).reshape(-1, 2))[:8]
        if not self._lib.cl_metal_set_curves(rgbc.ctypes.data, len(rgbc),
                                             lumac.ctypes.data, len(lumac)):
            raise RuntimeError('Metal 曲线上传失败：' + self._lib_error())
        self._curve_index = index
        self._n = n
        self._rgb_count = len(rgbc)
        self._luma_count = len(lumac)

    def _lib_error(self):
        raw = self._lib.cl_metal_last_error()
        return raw.decode('utf-8', 'replace') if raw else 'unknown'

    def _film_params(self, index, width, height, y0, out_rows, first, tone_rows, ui_strength):
        p = CATALOG[index]
        return MetalParams(
            width=width, height=height, n=self._n,
            rgb_count=self._rgb_count, luma_count=self._luma_count,
            seed=index, y0=y0, out_rows=out_rows, first=first, tone_rows=tone_rows,
            strength=float(p['strength']),
            clarity=float(p['clarity']), midpoint=float(p['midpoint']),
            vignette=float(p['vignette']), shadows=float(p['shadows']),
            midtones=float(p['midtones']), highlights=float(p['highlights']),
            grain=float(p['grain']), grainSize=float(p['grainSize']),
            roughness=float(p['roughness']), colorVariation=float(p['colorVariation']),
            ui_strength=float(ui_strength),
        )

    # -- main entry --------------------------------------------------------
    def tone_film(self, padded, index, y0, height, high_precision=False, cached=None,
                  out_rows=None, strength=1.0):
        """Render `out_rows` rows starting at `y0`.

        `cached` (the token returned by :meth:`cache_photo`) renders from the
        resident uint8 photo; otherwise `padded` is a float32 strip that already
        includes one halo row above and below (matching engine._render).
        """
        with _LOCK:
            self._configure(index)
            if cached is not None:
                w, h = self._size
                if not w or not h:
                    raise RuntimeError('Metal 照片未驻留')
                out_rows = int(out_rows or h)
                first, tone_rows = 0, h
                p = self._film_params(index, w, h, y0, out_rows, first, tone_rows, strength)
                p.rgb_count, p.luma_count = self._rgb_count, self._luma_count
                if not self._reserve(w * h * 3, 0):
                    raise RuntimeError('Metal 缓冲区不足')
                if not self._lib.cl_metal_render_u8(ctypes.byref(p)):
                    raise RuntimeError('Metal 渲染失败：' + self._lib_error())
                out = np.empty((out_rows, w, 3), np.uint8)
                if not self._lib.cl_metal_download(out.ctypes.data, out.nbytes):
                    raise RuntimeError('Metal 回读失败：' + self._lib_error())
                return out

            arr = np.ascontiguousarray(padded, dtype=np.float32)
            rows, w = arr.shape[:2]
            h = int(height)
            out_rows = int(out_rows if out_rows is not None else rows - 2)
            first, tone_rows = int(y0) - 1, rows
            self._reserve(0, arr.nbytes)
            if not self._lib.cl_metal_upload(arr.ctypes.data, arr.nbytes):
                raise RuntimeError('Metal 输入上传失败：' + self._lib_error())
            p = self._film_params(index, w, h, y0, out_rows, first, tone_rows,
                                 strength if high_precision else 1.0)
            p.rgb_count, p.luma_count = self._rgb_count, self._luma_count
            if high_precision:
                if not self._lib.cl_metal_render_f32(ctypes.byref(p)):
                    raise RuntimeError('Metal 浮点渲染失败：' + self._lib_error())
                out = np.empty((out_rows, w, 3), np.float32)
                if not self._lib.cl_metal_download(out.ctypes.data, out.nbytes):
                    raise RuntimeError('Metal 浮点回读失败：' + self._lib_error())
                return np.clip(out, 0.0, 1.0)
            # 8-bit non-resident fallback: float strip in, uint8 out, blend left
            # to engine's NumPy pass (ui_strength == 1 makes the kernel skip it).
            raise RuntimeError('Metal 需要驻留照片')

    # -- single-stage helpers (never on the hot path; kept for API parity) --
    def tone(self, rgb, index, high_precision=False):
        from engine import tone_cpu
        return tone_cpu(rgb, index, high_precision)

    def film(self, padded, index, y0, height, high_precision=False):
        from engine import film_cpu
        return film_cpu(padded, index, y0, height, high_precision)

    def monopan_grain(self, rgb, cancelled=None):
        """Monopan mode-0 grain on the GPU (m3.grain_cpu equivalent)."""
        from engine import Cancelled
        if cancelled and cancelled():
            raise Cancelled()
        src = np.ascontiguousarray(rgb, dtype=np.uint8)
        h, w = src.shape[:2]
        with _LOCK:
            self._upload_monopan_tables()
            out = np.empty_like(src)
            if not self._lib.cl_metal_monopan_grain(src.ctypes.data, out.ctypes.data, w, h):
                raise RuntimeError('Metal Monopan 失败：' + self._lib_error())
            # monopan shares the resident photo buffers
            self._photo_key = None
        if cancelled and cancelled():
            raise Cancelled()
        return out

    def _upload_monopan_tables(self):
        if getattr(self, '_monopan_ready', False):
            return
        from m3 import tables
        t = tables()
        pixel = np.ascontiguousarray(t['m_pixel_map'], dtype=np.uint8)
        batch = np.ascontiguousarray(t['m_batch_map'], dtype=np.uint16)
        lut = np.ascontiguousarray(t['m_lut_map'], dtype=np.uint8)
        rand = np.ascontiguousarray(t['m_rand_map_pixel'], dtype=np.uint8)
        # sqrt(v/255)*16 for v in 0..255: computed on the CPU so the kernel is
        # integer-only and bit-identical to numpy's float32 sqrt.
        levels = np.arange(256, dtype=np.float32)
        sqrt16 = np.ascontiguousarray(np.sqrt(levels / np.float32(255)) * np.float32(16))
        # value*0.3 + lum*0.7 evaluated exactly as engine/m3 does, so the GPU
        # never has to rely on float32 blend rounding.
        mixed = np.clip(levels[None, :] * np.float32(.3) + levels[:, None] * np.float32(.7),
                        0, 255).astype(np.uint8)
        mixed = np.ascontiguousarray(mixed)          # [lum, value]
        if not self._lib.cl_metal_set_monopan(pixel.ctypes.data, batch.ctypes.data,
                                             lut.ctypes.data, rand.ctypes.data,
                                             sqrt16.ctypes.data, mixed.ctypes.data):
            raise RuntimeError('Metal Monopan 表上传失败：' + self._lib_error())
        self._monopan_ready = True

    def input_denoise(self, rgb, style=2, cancelled=None):
        """Native cl_output_denoise on the GPU: median stats on CPU, 3x3 pass on Metal."""
        from engine import Cancelled
        if cancelled and cancelled():
            raise Cancelled()
        src = np.ascontiguousarray(rgb, dtype=np.uint8)
        h, w = src.shape[:2]
        out = np.empty_like(src)
        with _LOCK:
            if not self._lib.cl_metal_output_denoise(src.ctypes.data, out.ctypes.data, w, h, style):
                raise RuntimeError('Metal 降噪失败：' + self._lib_error())
            # the denoise path reuses gPhoto/gOut, so the resident photo is stale
            self._photo_key = None
        if cancelled and cancelled():
            raise Cancelled()
        return out

    def postprocessor(self):
        """Monopan/M9 post stages stay on the existing native C path."""
        return None

    def close(self):
        global _ACTIVE_OWNER
        with _LOCK:
            if _ACTIVE_OWNER is self:_ACTIVE_OWNER=None
        self.clear_photo()
        self._lut_cache.clear()
        self._curve_index = None
