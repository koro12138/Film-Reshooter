"""APK NightHighlights and HdrMath/GainPlane on the desktop image canvas."""
import os

import numpy as np
from PIL import Image


def protect(image,is_raw=False):
    if is_raw:return image
    rgb=np.asarray(image)
    h,w=rgb.shape[:2]
    sample=rgb[::max(1,(h+255)//256),::max(1,(w+255)//256)]
    lum=np.floor(sample.astype(np.float32)@np.array([.2126,.7152,.0722],np.float32)+.5)
    count=lum.size;dark=np.count_nonzero(lum<77);bright=np.count_nonzero(sample.max(axis=-1)>=204)
    night=bool(count and dark>=.65*count and lum.sum()<76.5*count and 0<bright<=.15*count)
    image.info['night']=night
    if not night:return image
    if image.info.get('rgb_float') is None and os.environ.get('CAMERALOOK_ARM_REFERENCE')!='1':
        # Native shoulder: identical float32 maths, one pass over the 8-bit frame.
        try:
            from desktop_hdr import protect_rgb
            out=Image.fromarray(protect_rgb(rgb))
            out.info.update(image.info)
            out.info.update(night=True,hdr_max=1.2)
            return out
        except (OSError,ValueError,RuntimeError):
            pass
    source=image.info.get('rgb_float')
    if source is None:source=rgb.astype(np.float32)/255
    peak=source.max(axis=-1)
    t=(peak-np.float32(.72))/np.float32(.28)
    shoulder=np.where(peak<=.72,peak,.72+.28*t/(1+.32*t))
    result=source*np.divide(shoulder,peak,out=np.ones_like(peak),where=peak>0)[...,None]
    out=Image.fromarray(np.floor(np.clip(result,0,1)*255+.5).astype(np.uint8))
    out.info.update(image.info)
    if 'rgb_float' in image.info:out.info['rgb_float']=result
    out.info.update(night=True,hdr_max=1.2)
    return out


def gain_plane(image):
    w,h=image.size;scale=min(1.,384/max(w,h))
    tw,th=max(1,int(w*scale+.5)),max(1,int(h*scale+.5))
    rgb=np.asarray(image.convert('RGB'))
    gray=None
    # The recovered ARM routine is the reference; the native x64 port is a
    # bit-identical reimplementation, so only the interpreter cost disappears.
    if os.environ.get('CAMERALOOK_ARM_REFERENCE')!='1':
        try:
            from desktop_hdr import sample as hdr_sample
            gray=hdr_sample(rgb,tw,th)
        except (OSError,AttributeError,ValueError,RuntimeError):
            gray=None
    if gray is None:
        from native_runtime import NativeImageRuntime
        runtime=NativeImageRuntime(heap_bytes=w*h*4+tw*th*8+8*1024*1024)
        try:gray=runtime.hdr_sample(rgb,tw,th)
        finally:runtime.close()
    x=np.clip((gray.astype(np.float32)/255-.36)/(.94-.36),0,1)
    gain=np.floor(x*x*(3-2*x)*255+.5).astype(np.int32)
    p=np.pad(gain,((0,0),(1,1)),mode='edge')
    gain=(p[:,:-2]+2*p[:,1:-1]+p[:,2:]+2)//4
    p=np.pad(gain,((1,1),(0,0)),mode='edge')
    gain=(p[:-2]+2*p[1:-1]+p[2:]+2)//4
    field=np.asarray(Image.fromarray(gain.astype(np.float32)/255).resize((w,h),Image.Resampling.BILINEAR))
    return np.power(np.float32(image.info.get('hdr_max',2)),field)
