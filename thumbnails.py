"""Small queue images and pre-rendered, fixed filter/watermark examples."""
from pathlib import Path
from io import BytesIO
from PIL import Image, ImageOps
from precision import RAW_EXTENSIONS


def photo_thumbnail(path,size=112):
    path=Path(path)
    if path.suffix.lower() in RAW_EXTENSIONS:
        import rawpy
        with rawpy.imread(str(path)) as raw:
            thumb=raw.extract_thumb()
            flip=raw.sizes.flip
            orientation=1
            if thumb.format==rawpy.ThumbFormat.JPEG:
                with Image.open(BytesIO(thumb.data)) as source:
                    orientation=source.getexif().get(274,1)
                    image=ImageOps.exif_transpose(source)
            else:image=Image.fromarray(thumb.data)
        if orientation==1:
            if flip==3:image=image.transpose(Image.Transpose.ROTATE_180)
            elif flip==5:image=image.transpose(Image.Transpose.ROTATE_90)
            elif flip==6:image=image.transpose(Image.Transpose.ROTATE_270)
    else:
        with Image.open(path) as source:
            source.draft('RGB',(size,size))
            image=ImageOps.exif_transpose(source)
    image.thumbnail((size,size),Image.Resampling.LANCZOS)
    return image.convert('RGB')


def watermark_sample(root,key,variant='',background=''):
    return Path(root)/'assets/previews/watermarks'/key/((variant or 'default')+'__'+(background or 'default')+'.jpg')
