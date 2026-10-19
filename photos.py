"""Photo input, EXIF-driven watermark layout and collision-safe atomic export."""
from dataclasses import dataclass
from io import BytesIO
from pathlib import Path
import os
import sys
from functools import lru_cache
import re
import tempfile
import warnings
import math
from PIL import Image, ImageOps, ImageCms, ImageDraw, ImageFont
import piexif
from watermark_info import WatermarkInformation, split_stamp
from types import SimpleNamespace

try:
    from pillow_heif import register_heif_opener
    register_heif_opener()
except ImportError:
    pass

EXTENSIONS = {'.jpg', '.jpeg', '.png', '.tif', '.tiff', '.webp', '.heic', '.heif', '.avif', '.bmp'}
from precision import RAW_EXTENSIONS
EXTENSIONS |= RAW_EXTENSIONS
SRGB = ImageCms.ImageCmsProfile(ImageCms.createProfile('sRGB')).tobytes()


def clean_text(value):
    if isinstance(value, bytes):
        for encoding in ('utf-8', 'gb18030', 'latin1'):
            try:
                value = value.decode(encoding)
                break
            except UnicodeDecodeError:
                continue
    return re.sub(r'[\x00-\x1f\x7f]', ' ', str(value or '')).strip()[:512]


def rational(value):
    try:
        return value[0] / value[1] if isinstance(value, tuple) else float(value)
    except (TypeError, ValueError, ZeroDivisionError):
        return 0


def gps_coordinate(value, reference, latitude=True):
    """Parse EXIF DMS without treating malformed or absent coordinates as zero."""
    ref = clean_text(reference).upper()
    if ref not in (('N','S') if latitude else ('E','W')):
        return None
    try:
        if len(value) != 3:
            return None
        values = [float(v[0])/float(v[1]) if isinstance(v,(tuple,list)) else float(v) for v in value]
        degrees, minutes, seconds = values
        limit = 90 if latitude else 180
        if not all(math.isfinite(v) for v in values) or not (0<=degrees<=limit and 0<=minutes<60 and 0<=seconds<60):
            return None
        result = degrees+minutes/60+seconds/3600
        if result>limit:
            return None
        return -result if ref in ('S','W') else result
    except (TypeError,ValueError,ZeroDivisionError,OverflowError):
        return None


@dataclass
class PhotoInfo:
    path: Path
    width: int
    height: int
    make: str = ''
    model: str = ''
    date: str = ''
    focal: float = 0
    aperture: float = 0
    exposure: float = 0
    iso: str = ''
    lens: str = ''
    latitude: float | None = None
    longitude: float | None = None

    @property
    def camera(self):
        if not self.model:
            return self.make
        if not self.make or self.make.casefold() in self.model.casefold():
            return self.model
        return f'{self.make} {self.model}'

    @property
    def settings(self):
        fields = []
        if self.focal:
            fields.append(f'{self.focal:g}mm')
        if self.aperture:
            fields.append(f'f/{self.aperture:g}')
        if self.exposure:
            fields.append(f'1/{round(1/self.exposure)}s' if self.exposure < 1 else f'{self.exposure:g}s')
        if self.iso:
            fields.append(f'ISO {self.iso}')
        return '   '.join(fields)

    @property
    def coordinates(self):
        if self.latitude is None or self.longitude is None:
            return ''
        return f'{abs(self.latitude):.6f}°{"S" if self.latitude<0 else "N"}  {abs(self.longitude):.6f}°{"W" if self.longitude<0 else "E"}'


def info_from_image(image, path):
    exif = image.getexif()
    try:
        nested = exif.get_ifd(34665)
    except Exception:
        nested = {}
    w, h = image.size
    if exif.get(274, 1) in (5, 6, 7, 8):
        w, h = h, w
    date = clean_text(nested.get(36867) or nested.get(36868))
    if re.match(r'^\d{4}:\d{2}:\d{2}', date):
        date = date[:10].replace(':', '-') + date[10:]
    try:
        gps = exif.get_ifd(34853)
    except Exception:
        gps = {}
    return PhotoInfo(Path(path), w, h, clean_text(exif.get(271)), clean_text(exif.get(272)), date,
                     rational(nested.get(41989) or nested.get(37386)), rational(nested.get(33437)),
                     rational(nested.get(33434)), clean_text(nested.get(34855)), clean_text(nested.get(42036)),
                     gps_coordinate(gps.get(2),gps.get(1),True),gps_coordinate(gps.get(4),gps.get(3),False))


def inspect_photo(path):
    if Path(path).suffix.lower() in RAW_EXTENSIONS:
        from precision import raw_metadata
        import rawpy
        info,_=raw_metadata(path)
        with rawpy.imread(str(path)) as raw:
            info.width,info.height=raw.sizes.width,raw.sizes.height
            if raw.sizes.flip in (5,6): info.width,info.height=info.height,info.width
        return info
    with Image.open(path) as image:
        return info_from_image(image, path)


def load_photo(path, preview_size=None):
    if Path(path).suffix.lower() in RAW_EXTENSIONS:
        from precision import load_raw
        return load_raw(path,preview_size)
    notes = []
    with Image.open(path) as source:
        info = info_from_image(source, path)
        exif_data = source.info.get('exif')
        if not exif_data:
            exif_data = source.getexif().tobytes()
        icc = source.info.get('icc_profile')
        high_array=None
        if preview_size is None:
            from precision import load_high_array
            high_array=load_high_array(path,source.getexif().get(274,1),icc)
        # JPEG draft decoding reduces preview work before orientation/color conversion.
        if preview_size:
            source.draft('RGB', (preview_size, preview_size))
        image = ImageOps.exif_transpose(source)
        if preview_size:
            image.thumbnail((preview_size, preview_size), Image.Resampling.LANCZOS)
        if icc:
            try:
                profile = ImageCms.ImageCmsProfile(BytesIO(icc))
                image = ImageCms.profileToProfile(image, profile, ImageCms.createProfile('sRGB'), outputMode='RGB')
            except Exception as exc:
                notes.append(f'ICC 转换失败，按 RGB 处理：{exc}')
                image = image.convert('RGB')
        else:
            image = image.convert('RGB')
    image.info['photo_info'] = info
    if high_array is not None:
        import numpy as np
        image=Image.fromarray(np.rint(high_array*255).astype(np.uint8))
        image.info.update(rgb_float=high_array,photo_info=info)
        notes.append('高位深输入：保留 float32 工作精度')
    return image, info, exif_data, notes


def _ttc_index(path, family, styles):
    """Find the sub-font index inside a TTC by family/weight instead of assuming order."""
    names = []
    for index in range(24):
        try:
            name = ImageFont.truetype(str(path), 12, index=index).getname()
        except Exception:
            break
        if name:
            names.append((index, name))
    for style in (styles or (None,)):
        for index, name in names:
            if name[0] == family and (style is None or name[1] == style):
                return index
    return None


def _mac_pingfang():
    for folder in ('/System/Library/Fonts', '/System/Library/Fonts/Supplemental', '/Library/Fonts'):
        candidate = Path(folder) / 'PingFang.ttc'
        if candidate.exists():
            return candidate
    # PingFang ships as a downloadable system asset on recent macOS releases.
    assets = Path('/System/Library/AssetsV2')
    if assets.is_dir():
        for pattern in ('com_apple_MobileAsset_Font*/*/AssetData/PingFang.ttc',
                        'com_apple_MobileAsset_Font*/*/PingFang.ttc'):
            for candidate in sorted(assets.glob(pattern)):
                return candidate
    return None


@lru_cache(maxsize=None)
def _font_spec(bold=False):
    """Resolve (path, index) once per weight; the watermark runs on every export."""
    override = os.environ.get('CAMERALOOK_FONT_BOLD' if bold else 'CAMERALOOK_FONT')
    if override:
        return Path(override), 0
    if os.name == 'nt':
        folder = Path(os.environ.get('WINDIR', r'C:\Windows')) / 'Fonts'
        for name in (['msyhbd.ttc', 'segoeuib.ttf'] if bold else ['msyh.ttc', 'segoeui.ttf']):
            if (folder / name).exists():
                return folder / name, 0
        return None, 0
    if sys.platform == 'darwin':
        styles = ('Semibold', 'Medium', 'Bold') if bold else ('Regular', 'Medium')
        pingfang = _mac_pingfang()
        if pingfang is not None:
            index = _ttc_index(pingfang, 'PingFang SC', styles)
            if index is not None:
                return pingfang, index
            index = _ttc_index(pingfang, 'PingFang SC', None)
            if index is not None:
                return pingfang, index
        heiti = Path('/System/Library/Fonts/Hiragino Sans GB.ttc')
        if heiti.exists():
            index = _ttc_index(heiti, 'Hiragino Sans GB', ('W6',) if bold else ('W3',))
            if index is not None:
                return heiti, index
        for name in ('STHeiti Medium.ttc', 'STHeiti Light.ttc'):
            candidate = Path('/System/Library/Fonts') / name
            if candidate.exists():
                index = _ttc_index(candidate, 'Heiti SC', None) or 0
                return candidate, index
        return None, 0
    for folder in ('/usr/share/fonts/opentype/noto', '/usr/share/fonts/truetype/noto',
                   '/usr/share/fonts'):
        for name in ('NotoSansCJK-Regular.ttc', 'NotoSansCJKsc-Regular.otf', 'DejaVuSans.ttf'):
            candidate = Path(folder) / name
            if candidate.exists():
                return candidate, 0
    return None, 0


def get_font(size, bold=False):
    path, index = _font_spec(bool(bold))
    if path is not None:
        try:
            return ImageFont.truetype(str(path), max(1, int(size)), index=index)
        except Exception:
            pass
    return ImageFont.load_default(size=max(1, int(size)))


def fit_text(draw, text, width, size, bold=False):
    font = get_font(size, bold)
    while draw.textbbox((0, 0), text, font=font)[2] > width and size > 8:
        size *= .9
        font = get_font(size, bold)
    while draw.textlength(text, font=font) > width and text:
        text = text[:-2] + '…' if not text.endswith('…') else text[:-2] + '…'
        if text == '…':
            break
    return text, font


def watermark(image, info, style='white', fallback='', override=False, details=True, date=True, caption='', location=True,location_label='',*,time=True,device=True,brand=True,information=None):
    if style == 'none':
        return image.copy()
    information = information or WatermarkInformation.from_options(info, SimpleNamespace(
        fallback=fallback, override=override, details=details, date=date, time=time,
        device=device, brand=brand, location=location, location_label=location_label,
        signature=caption, caption=False))
    camera = information.camera
    caption = information.desktop_caption
    w, h = image.size
    # Use image width, so portrait and landscape receive equally readable typography.
    coords = information.desktop_location
    band = max(42 if coords else 32, round(w * (.13 if coords else .105)))
    margin = max(6, round(w * .035))
    dark = style == 'black'
    foreground, secondary = ('#f2f0e9', '#aaa9a2') if dark else ('#171919', '#737572')
    extra = information.settings
    stamp = information.stamp
    if stamp:extra=f'{extra}    {stamp}'.strip()
    if style == 'overlay':
        rgba = image.convert('RGBA')
        layer = Image.new('RGBA', image.size)
        d = ImageDraw.Draw(layer)
        top = max(0, h-band)
        d.rectangle((0, top, w, h), fill=(0, 0, 0, 150))
        rgba = Image.alpha_composite(rgba, layer)
        result = rgba.convert('RGB')
        y = top
        foreground, secondary = '#ffffff', '#e2e2df'
    else:
        result = Image.new('RGB', (w, h+band), '#171a1b' if dark else '#faf9f5')
        result.paste(image, (0, 0))
        y = h
    d = ImageDraw.Draw(result)
    # Right caption is optional; reserve space to prevent long camera names colliding.
    available = w - margin*2
    if caption:
        cap, cap_font = fit_text(d, caption, available*.30, w*.021)
        d.text((w-margin, y+band*.32), cap, anchor='rm', font=cap_font, fill=secondary)
        available *= .66
    label, label_font = fit_text(d, camera, available, w*.031, bold=True)
    d.text((margin, y+band*(.26 if coords else .32)), label, anchor='lm', font=label_font, fill=foreground)
    if extra:
        text, font = fit_text(d, extra, w-margin*2, w*.018)
        d.text((margin, y+band*(.58 if coords else .73)), text, anchor='lm', font=font, fill=secondary)
    if coords:
        text,font = fit_text(d,coords,w-margin*2,w*.018)
        d.text((margin,y+band*.83),text,anchor='lm',font=font,fill=secondary)
    return result


def export_photo(image, folder, stem, filter_name, exif_data, fmt='JPEG', quality=97, keep_exif=True,*,save_mode=None):
    folder = Path(folder)
    folder.mkdir(parents=True, exist_ok=True)
    safe = re.sub(r'[<>:"/\\|?*\x00-\x1f]', '_', f'{stem}_{filter_name}').strip(' .')[:150] or 'photo'
    suffix = '.jpg' if fmt in ('JPEG','Ultra HDR JPEG') else '.tif' if fmt=='TIFF 16-bit' else '.png'
    notes = []
    kwargs = {'icc_profile': SRGB}
    if save_mode not in (None,'normal','fast'):raise ValueError('未知保存模式')
    fast=save_mode=='fast' if save_mode is not None else os.environ.get('CAMERALOOK_FAST_SAVE')=='1'
    if fmt=='PNG':
        try:level=max(0,min(9,int(os.environ.get('CAMERALOOK_PNG_LEVEL','3' if fast else '6') if save_mode is None else '3' if fast else '6')))
        except ValueError:level=3 if fast else 6
        kwargs['compress_level']=level
    if fmt == 'JPEG':
        optimize=(os.environ.get('CAMERALOOK_JPEG_OPTIMIZE','0' if fast else '1') not in ('0','','false','False')) if save_mode is None else not fast
        kwargs.update(quality=quality, subsampling=0, optimize=optimize)
    if keep_exif and exif_data:
        try:
            exif = piexif.load(exif_data)
            exif['0th'][274] = 1
            exif['0th'][256], exif['0th'][257] = image.size
            exif['Exif'][40962], exif['Exif'][40963] = image.size
            exif['thumbnail'] = None
            exif['1st'] = {}
            kwargs['exif'] = piexif.dump(exif)
        except Exception as exc:
            notes.append(f'EXIF 无法保留：{exc}')
    fd, tmp = tempfile.mkstemp(prefix='.cameralook-', suffix='.tmp', dir=folder)
    os.close(fd)
    try:
        from precision import HIGH_FORMATS,encode_high
        if fmt in HIGH_FORMATS:
            Path(tmp).write_bytes(encode_high(image,fmt,quality,kwargs.get('exif'),SRGB,save_mode=save_mode))
            if 'rgb_float' not in image.info:
                notes.append('此滤镜使用原生 8-bit 运算；高位深容器不会增加原算法的色阶')
        else:
            image.save(tmp, format=fmt, **kwargs)
        for i in range(100000):
            dest = folder / (safe + (f'_{i}' if i else '') + suffix)
            try:
                # Windows rename is atomic and refuses to overwrite an existing file.
                os.rename(tmp, dest)
                return dest, notes
            except FileExistsError:
                continue
        raise OSError('输出文件重名过多')
    finally:
        if os.path.exists(tmp):
            os.unlink(tmp)
