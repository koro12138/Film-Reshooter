"""Float processing, RAW/16-bit input and real Ultra HDR/16-bit export support."""
from io import BytesIO
from pathlib import Path
import struct
import os
import zlib
import numpy as np
from PIL import Image
from engine import tone_cpu,film_cpu,Cancelled

RAW_EXTENSIONS = {'.dng','.nef','.nrw','.arw','.srf','.sr2','.cr2','.cr3','.crw','.raf','.rw2','.orf','.pef','.ptx','.srw','.x3f','.iiq','.3fr','.erf','.kdc','.mos','.mrw','.rwl'}
HIGH_FORMATS = {'TIFF 16-bit','PNG 16-bit','Ultra HDR JPEG'}


def srgb_to_linear(x):
    return np.where(x<=.04045,x/12.92,((x+.055)/1.055)**2.4).astype(np.float32)


def linear_to_srgb(x):
    return np.where(x<=.0031308,x*12.92,1.055*np.maximum(x,0)**(1/2.4)-.055).astype(np.float32)


def orient_array(a, orientation):
    if orientation==2: return a[:,::-1]
    if orientation==3: return a[::-1,::-1]
    if orientation==4: return a[::-1]
    if orientation==5: return a.transpose(1,0,2)
    if orientation==6: return np.rot90(a,3)
    if orientation==7: return a.transpose(1,0,2)[::-1,::-1]
    if orientation==8: return np.rot90(a)
    return a


def raw_metadata(path):
    import exifread
    import piexif
    from photos import PhotoInfo,clean_text,gps_coordinate
    with Path(path).open('rb') as f:
        tags = exifread.process_file(f,details=False)
    def text(name): return clean_text(str(tags[name])) if name in tags else ''
    def value(name):
        try: return float(tags[name].values[0])
        except (KeyError,ValueError,TypeError,IndexError,ZeroDivisionError): return 0.
    def gps(name,ref,latitude):
        item = tags.get('GPS '+name)
        return gps_coordinate([(v.num,v.den) for v in item.values],text('GPS '+ref),latitude) if item else None
    info = PhotoInfo(Path(path),int(value('EXIF ExifImageWidth') or value('Image ImageWidth')),
        int(value('EXIF ExifImageLength') or value('Image ImageLength')),text('Image Make'),text('Image Model'),
        text('EXIF DateTimeOriginal') or text('EXIF DateTimeDigitized'),value('EXIF FocalLengthIn35mmFilm') or value('EXIF FocalLength'),
        value('EXIF FNumber'),value('EXIF ExposureTime'),text('EXIF ISOSpeedRatings'),text('EXIF LensModel'),
        gps('GPSLatitude','GPSLatitudeRef',True),gps('GPSLongitude','GPSLongitudeRef',False))
    if len(info.date)>=10: info.date=info.date[:10].replace(':','-')+info.date[10:]
    # Rebuild portable EXIF fields instead of copying RAW/TIFF offsets.
    exif={'0th':{},'Exif':{},'GPS':{},'1st':{},'thumbnail':None}
    for key,tag in [('Image Make',271),('Image Model',272)]:
        if text(key): exif['0th'][tag]=text(key).encode('utf8')
    if text('EXIF DateTimeOriginal'): exif['Exif'][36867]=text('EXIF DateTimeOriginal').encode('ascii','replace')
    elif text('EXIF DateTimeDigitized'):exif['Exif'][36868]=text('EXIF DateTimeDigitized').encode('ascii','replace')
    for key,tag in [('EXIF ExposureTime',33434),('EXIF FNumber',33437),('EXIF FocalLength',37386)]:
        item=tags.get(key)
        if item and item.values: exif['Exif'][tag]=(item.values[0].num,item.values[0].den)
    if value('EXIF ISOSpeedRatings'): exif['Exif'][34855]=min(65535,int(value('EXIF ISOSpeedRatings')))
    for key,tag in [('GPSLatitudeRef',1),('GPSLatitude',2),('GPSLongitudeRef',3),('GPSLongitude',4)]:
        item=tags.get('GPS '+key)
        if item: exif['GPS'][tag]=text('GPS '+key).encode('ascii') if tag in (1,3) else [(v.num,v.den) for v in item.values]
    return info,piexif.dump(exif)


def load_raw(path, preview_size=None):
    import rawpy
    from photos import PhotoInfo
    info,exif=raw_metadata(path)
    with rawpy.imread(str(path)) as raw:
        info.width,info.height=raw.sizes.width,raw.sizes.height
        if raw.sizes.flip in (5,6):info.width,info.height=info.height,info.width
        a = raw.postprocess(use_camera_wb=True,output_color=rawpy.ColorSpace.sRGB,
            gamma=(2.4,12.92),no_auto_bright=True,output_bps=16,half_size=bool(preview_size))
    if not preview_size:info.width,info.height = a.shape[1],a.shape[0]
    image = Image.fromarray(np.rint(a.astype(np.float32)/257).astype(np.uint8))
    if preview_size: image.thumbnail((preview_size,preview_size),Image.Resampling.LANCZOS)
    else: image.info['rgb_float']=a.astype(np.float32)/np.float32(65535)
    image.info.update(photo_info=info,is_raw=True)
    return image,info,exif,['RAW：LibRaw 相机白平衡、sRGB 显影、16-bit，关闭自动提亮']


def load_high_array(path, orientation=1, icc=None):
    """Read high-depth raster pixels; never manufacture precision from an 8-bit input."""
    import imagecodecs
    path=Path(path)
    if path.suffix.lower() in ('.tif','.tiff'):
        import tifffile
        a=tifffile.imread(path)
    elif path.suffix.lower()=='.png':
        a=imagecodecs.png_decode(path.read_bytes())
    elif path.suffix.lower() in ('.heic','.heif'):
        import pillow_heif
        heif=pillow_heif.open_heif(path,convert_hdr_to_8bit=False)
        if '16' not in heif.mode: return None
        a=np.frombuffer(heif.data,'<u2').reshape(heif.size[1],heif.stride//2)[:,:heif.size[0]*3].reshape(heif.size[1],heif.size[0],3)
        depth=int(heif.info.get('bit_depth',16))
        if depth in (10,12):
            maximum=((1<<depth)-1)<<(16-depth)
            a=np.rint(a.astype(np.float32)*(65535/maximum)).clip(0,65535).astype(np.uint16)
    else: return None
    if a.dtype==np.uint8: return None
    if a.ndim==2: a=np.repeat(a[...,None],3,axis=-1)
    if a.ndim!=3 or a.shape[2] not in (3,4): raise ValueError('高位深文件仅支持 RGB / RGBA 或灰度')
    a=np.ascontiguousarray(a[...,:3])
    if icc:
        from photos import SRGB
        a=imagecodecs.cms_transform(a,icc,SRGB,colorspace='RGB',outcolorspace='RGB',
            planar=False,outplanar=False,outdtype=a.dtype)
    if np.issubdtype(a.dtype,np.integer): a=a.astype(np.float32)/np.iinfo(a.dtype).max
    else: a=a.astype(np.float32)
    if not np.isfinite(a).all(): raise ValueError('高位深输入有非有限像素')
    return np.ascontiguousarray(orient_array(np.clip(a,0,1),orientation))


def render_float(renderer,image,index,strength=1,progress=None,cancelled=None):
    renderer.name=f'GPU · float32 · {renderer.gpu.name}' if renderer.gpu else 'CPU · float32 NumPy'
    source=image.info.get('rgb_float')
    if source is None: source=np.asarray(image.convert('RGB'),np.float32)/255
    if index<0 or strength<=0: result=source.copy()
    else:
        h,w=source.shape[:2]
        result=np.empty_like(source)
        rows=h if getattr(renderer.gpu,'whole_image',False) else max(1,min(128,(750000 if renderer.gpu else 100000)//w))
        if renderer.gpu and __import__('os').environ.get('CAMERALOOK_LEGACY_GPU')!='1':
            for top in range(0,h,rows):
                if cancelled and cancelled():raise Cancelled()
                end=min(h,top+rows)
                pad=source[np.clip(np.arange(top-1,end+1),0,h-1)]
                result[top:end]=renderer.gpu.tone_film(pad,index,top,h,True)
                if strength!=1:result[top:end]=np.clip(source[top:end]+(result[top:end]-source[top:end])*strength,0,1)
                if progress:progress(end/h)
        else:
            toned=np.empty_like(source)
            for top in range(0,h,rows):
                if cancelled and cancelled(): raise Cancelled()
                strip=source[top:top+rows]
                toned[top:top+rows]=renderer.gpu.tone(strip,index,True) if renderer.gpu else tone_cpu(strip,index,True)
                if progress: progress(.5*min(h,top+rows)/h)
            for top in range(0,h,rows):
                if cancelled and cancelled(): raise Cancelled()
                end=min(h,top+rows)
                pad=toned[np.clip(np.arange(top-1,end+1),0,h-1)]
                result[top:end]=renderer.gpu.film(pad,index,top,h,True) if renderer.gpu else film_cpu(pad,index,top,h,True)
                if strength!=1: result[top:end]=np.clip(source[top:end]+(result[top:end]-source[top:end])*strength,0,1)
                if progress: progress(.5+.5*end/h)
    out=Image.fromarray(np.rint(result*255).astype(np.uint8))
    out.info['rgb_float']=result
    return out


def retain_precision(source,marked,bounds=None,*,preserve=True):
    for key in ('hdr_max','night','is_raw'):
        if key in source.info:marked.info[key]=source.info[key]
    marked.info['source_bounds']=bounds or (0,0,source.width,source.height)
    a=source.info.get('rgb_float') if preserve else None
    if not preserve:marked.info.pop('rgb_float',None)
    if a is None: return marked
    canvas=np.asarray(marked,np.float32)/255
    x,y,right,bottom=bounds or (0,0,source.width,source.height)
    if (right-x,bottom-y)!=source.size: raise ValueError('高位深水印源图区域尺寸不一致')
    # Preserve sub-byte values, including underneath in-image watermark overlays.
    source_rgb=np.asarray(source)
    rows=max(1,150000//max(1,source.width))
    for top in range(0,source.height,rows):
        end=min(source.height,top+rows)
        delta=a[top:end]-source_rgb[top:end].astype(np.float32)/255
        canvas[y+top:y+end,x:right]=np.clip(canvas[y+top:y+end,x:right]+delta,0,1)
    marked.info['rgb_float']=canvas
    marked.info['source_bounds']=(x,y,right,bottom)
    return marked


def hdr_pixels(image):
    rgb=image.info.get('rgb_float')
    from hdr import gain_plane
    gain=gain_plane(image)
    bounds=image.info.get('source_bounds')
    if bounds:
        x,y,r,b=bounds
        gain[:y]=1;gain[b:]=1;gain[y:b,:x]=1;gain[y:b,r:]=1
        if 'watermark_mask' in image.info:
            region=gain[y:b,x:r];region[image.info['watermark_mask']]=1
    source=np.asarray(image.convert('RGB')) if rgb is None else rgb
    if rgb is None and os.environ.get('CAMERALOOK_ARM_REFERENCE')!='1' and os.environ.get('CAMERALOOK_NATIVE_HDR_PACK','1')!='0':
        try:
            from desktop_hdr import pack
            return pack(source,gain,_SRGB_LUT)
        except (OSError,AttributeError,ValueError,RuntimeError):pass
    rgba=np.ones((*gain.shape,4),np.float16)
    rows=max(1,min(512,150000//max(1,gain.shape[1])))
    for y in range(0,gain.shape[0],rows):
        linear=_SRGB_LUT[source[y:y+rows]] if rgb is None else srgb_to_linear(source[y:y+rows])
        rgba[y:y+rows,:,:3]=(linear*gain[y:y+rows,:,None]).astype(np.float16)
    return rgba


_SRGB_LUT=srgb_to_linear(np.arange(256,dtype=np.float32)/np.float32(255))


def encode_high(image,fmt,quality,exif=None,icc=None,*,save_mode=None):
    import imagecodecs
    if fmt in ('TIFF 16-bit','PNG 16-bit'):
        a=image.info.get('rgb_float')
        if a is None:a=np.asarray(image.convert('RGB'),np.float32)/255
        u16=np.empty(a.shape,np.uint16)
        rows=max(1,150000//max(1,image.width))
        for top in range(0,image.height,rows):
            u16[top:top+rows]=np.rint(np.clip(a[top:top+rows],0,1)*65535).astype(np.uint16)
    if fmt=='TIFF 16-bit':
        import piexif
        # A baseline big-endian TIFF uses the same IFD layout as EXIF. Building
        # both together preserves genuine EXIF/GPS sub-IFDs and valid offsets.
        data=piexif.load(exif) if exif else {'0th':{},'Exif':{},'GPS':{},'1st':{},'thumbnail':None}
        data['1st']={};data['thumbnail']=None
        height,width=u16.shape[:2]
        data['0th'].update({256:width,257:height,258:(16,16,16),259:1,262:2,
            273:0,277:3,278:height,279:u16.nbytes,284:1,274:1})
        if icc:
            piexif.TAGS['0th'][34675]={'name':'ICCProfile','type':7}
            data['0th'][34675]=icc
        header=piexif.dump(data)[6:]
        offset=(len(header)+7)&~7
        data['0th'][273]=offset
        header=piexif.dump(data)[6:]
        return header+bytes(offset-len(header))+u16.astype('>u2').tobytes()
    if fmt=='PNG 16-bit':
        import os
        level=(os.environ.get('CAMERALOOK_PNG_LEVEL') or None) if save_mode is None else None
        if level:
            try:level=max(0,min(9,int(level)))
            except ValueError:level=None
        fast=save_mode=='fast' if save_mode is not None else os.environ.get('CAMERALOOK_FAST_SAVE')=='1'
        options={'level':level} if level is not None else {'level':1,'strategy':3,'filter':16} if fast else {}
        b=imagecodecs.png_encode(u16,**options)
        def chunk(name,data): return struct.pack('>I',len(data))+name+data+struct.pack('>I',zlib.crc32(name+data)&0xffffffff)
        extra=b''
        if icc: extra+=chunk(b'iCCP',b'sRGB\0\0'+zlib.compress(icc))
        if exif: extra+=chunk(b'eXIf',exif.removeprefix(b'Exif\0\0'))
        return b[:33]+extra+b[33:]
    if fmt=='Ultra HDR JPEG':
        b=imagecodecs.ultrahdr_encode(hdr_pixels(image),level=quality,gamut=imagecodecs.ULTRAHDR.CG.BT_709)
        if exif:
            # Insert a standard APP1 before the JPEG stream without recompressing
            # the gain map. MPF offsets are relative to its own TIFF header.
            if len(exif)>65533: raise ValueError('EXIF 超过 JPEG APP1 容量')
            extra=b'\xff\xe1'+struct.pack('>H',len(exif)+2)+exif
            b=adjust_mpf_primary_size(b,len(extra))
            b=b[:2]+extra+b[2:]
        return b
    raise ValueError('未知高位深输出格式')


def adjust_mpf_primary_size(jpeg,added_bytes):
    data=bytearray(jpeg)
    pos=2
    while pos+4<len(data) and data[pos]==255:
        marker=data[pos+1]
        if marker in (0xda,0xd9):break
        length=struct.unpack_from('>H',data,pos+2)[0]
        if marker==0xe2 and data[pos+4:pos+8]==b'MPF\0':
            tiff=pos+8
            endian='<' if data[tiff:tiff+2]==b'II' else '>'
            ifd=tiff+struct.unpack_from(endian+'I',data,tiff+4)[0]
            count=struct.unpack_from(endian+'H',data,ifd)[0]
            for i in range(count):
                entry=ifd+2+i*12
                tag,kind,n,offset=struct.unpack_from(endian+'HHII',data,entry)
                if tag==0xb002:
                    address=tiff+offset+4
                    old=struct.unpack_from(endian+'I',data,address)[0]
                    struct.pack_into(endian+'I',data,address,old+added_bytes)
        pos+=length+2
    return bytes(data)
