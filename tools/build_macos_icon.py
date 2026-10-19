"""Generate the macOS app icon (Big Sur style rounded square) as an .icns file."""
from pathlib import Path
import subprocess
import tempfile

from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'assets' / 'macos' / 'CameraLook.icns'


def rounded(size):
    canvas = Image.new('RGBA', (size, size), (0, 0, 0, 0))
    inset = round(size * 0.098)
    box = (inset, inset, size - inset, size - inset)
    radius = round((size - inset * 2) * 0.225)
    plate = Image.new('RGBA', (size, size), (0, 0, 0, 0))
    d = ImageDraw.Draw(plate)
    # Subtle vertical gradient from #1670c4 to #0c4f8c, matching the app accent.
    for y in range(box[1], box[3]):
        t = (y - box[1]) / max(1, box[3] - box[1])
        color = (round(22 + (12 - 22) * t), round(112 + (79 - 112) * t),
                 round(196 + (140 - 196) * t), 255)
        d.line([(box[0], y), (box[2] - 1, y)], fill=color)
    mask = Image.new('L', (size, size), 0)
    ImageDraw.Draw(mask).rounded_rectangle(box, radius=radius, fill=255)
    canvas.paste(plate, (0, 0), mask)
    draw = ImageDraw.Draw(canvas)
    # Aperture ring plus a soft highlight, then the brand "C".
    cx = cy = size / 2
    ring = size * 0.30
    draw.ellipse([cx - ring, cy - ring, cx + ring, cy + ring],
                 outline=(255, 255, 255, 70), width=max(2, round(size * 0.012)))
    font = None
    for candidate in ('/System/Library/Fonts/PingFang.ttc',
                      '/System/Library/Fonts/Hiragino Sans GB.ttc'):
        if Path(candidate).exists():
            try:
                font = ImageFont.truetype(candidate, round(size * 0.42), index=11)
                break
            except Exception:
                font = None
    if font is None:
        font = ImageFont.load_default(size=round(size * 0.42))
    draw.text((cx, cy - size * 0.012), 'C', font=font, fill=(255, 255, 255, 245), anchor='mm')
    return canvas


def main():
    OUT.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        iconset = Path(tmp) / 'CameraLook.iconset'
        iconset.mkdir()
        for base in (16, 32, 128, 256, 512):
            for scale in (1, 2):
                px = base * scale
                name = f'icon_{base}x{base}' + ('@2x' if scale == 2 else '') + '.png'
                rounded(px).save(iconset / name)
        subprocess.run(['iconutil', '-c', 'icns', str(iconset), '-o', str(OUT)], check=True)
    print(OUT)


if __name__ == '__main__':
    main()
