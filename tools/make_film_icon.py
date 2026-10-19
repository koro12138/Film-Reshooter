"""Generate the Film Reshooter Windows app icon (PNG + multi-size ICO).

Drawn rather than hand-made so the artwork stays reproducible: a rounded-square
badge, a vertical blue gradient, the "FR" monogram, and a film-strip band under
it to read as a photo tool at 16 px.
"""
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'assets' / 'branding'

S = 1024
TOP = (0x1B, 0x86, 0xE0)      # bright blue
BOTTOM = (0x0A, 0x2E, 0x52)   # deep navy
INK = (0xFF, 0xFF, 0xFF)
FILM = (0x0B, 0x1B, 0x2B)


def gradient(size):
    img = Image.new('RGB', (size, size))
    px = img.load()
    for y in range(size):
        t = y / (size - 1)
        # ease so the bright area stays near the top third
        t = t ** 0.85
        row = tuple(round(TOP[i] + (BOTTOM[i] - TOP[i]) * t) for i in range(3))
        for x in range(size):
            px[x, y] = row
    return img


def rounded_mask(size, radius):
    mask = Image.new('L', (size, size), 0)
    ImageDraw.Draw(mask).rounded_rectangle((0, 0, size - 1, size - 1), radius=radius, fill=255)
    return mask


def font(size, index=0):
    for path, idx in ((r'C:\Windows\Fonts\segoeuib.ttf',0),(r'C:\Windows\Fonts\arialbd.ttf',0)):
        try:
            return ImageFont.truetype(path, size, index=idx)
        except OSError:
            continue
    return ImageFont.load_default()


def build(size=1024):
    base = gradient(size).convert('RGBA')
    draw = ImageDraw.Draw(base)

    # Monogram, optically centred a little above the middle so the film strip
    # underneath does not unbalance the badge.
    label = 'FR'
    f = font(int(size * 0.42))
    box = draw.textbbox((0, 0), label, font=f)
    w, h = box[2] - box[0], box[3] - box[1]
    draw.text(((size - w) / 2 - box[0], size * 0.44 - h / 2 - box[1]), label, font=f, fill=INK)

    # Film strip: a dark band with two rows of sprocket holes.
    band_top, band_h = size * 0.70, size * 0.135
    draw.rounded_rectangle((size * 0.20, band_top, size * 0.80, band_top + band_h),
                           radius=band_h * 0.22, fill=FILM)
    holes = 5
    hole_w = size * 0.055
    hole_h = band_h * 0.30
    gap = (size * 0.60 - holes * hole_w) / (holes + 1)
    for row in (0.24, 0.66):
        for i in range(holes):
            x = size * 0.20 + gap + i * (hole_w + gap)
            y = band_top + band_h * row - hole_h / 2
            draw.rounded_rectangle((x, y, x + hole_w, y + hole_h),
                                   radius=hole_h * 0.28, fill=(0x9F, 0xC8, 0xEA))

    base.putalpha(rounded_mask(size, int(size * 0.225)))
    return base


def main():
    OUT.mkdir(parents=True,exist_ok=True)
    master=build()
    master.save(OUT/'FilmReshooter.png')
    master.save(OUT/'FilmReshooter.ico',format='ICO',sizes=[(16,16),(24,24),(32,32),(48,48),(64,64),(128,128),(256,256)])
    print('Film Reshooter Windows PNG/ICO generated')

if __name__=='__main__':main()
