"""APK LeicaParams scene selection and native leicaPixel LUT/shading math."""
from functools import lru_cache
import math
import struct
import numpy as np
from engine import ROOT, Cancelled


class LeicaParams:
    def __init__(self, name='fullm9/leica_filter_param_m9_snapshot.bin'):
        self.raw = (ROOT/'assets'/name).read_bytes()
        self.pos = 0
        sizes = [self.u16() for _ in range(self.u16())]
        start,self.lut_off,n = self.u16(),self.u16(),self.u16()
        if n!=17: raise ValueError('Leica LUT size')
        zoom_sizes = [self.u16() for _ in range(self.u16())]
        self.scenes = {}
        count = 0
        for size in sizes:
            self.pos = start
            name = self.raw[start:start+64].split(b'\0')[0].decode('utf8').strip()
            self.pos += 64
            tree = self.tree()
            self.scenes[name] = tree
            count = max(count,max(c[2]+1 for l in tree for c in l[2]))
            start += size
        self.zooms = []
        for size in zoom_sizes:
            self.pos = start+4
            self.zooms.append((struct.unpack_from('<f',self.raw,start)[0],self.tree()))
            start += size
        self.shade_off = self.lut_off+count*14739

    def u16(self):
        result = struct.unpack_from('<H',self.raw,self.pos)[0]
        self.pos += 2
        return result

    def tree(self):
        tree = []
        for _ in range(self.u16()):
            lo,hi = self.u16(),self.u16()
            children = [(self.u16(),self.u16(),self.u16()) for _ in range(self.u16())]
            tree.append((lo,hi,children))
        return tree

    @staticmethod
    def find(bins,value):
        for i,b in enumerate(bins):
            if value<=b[1]: return (b,b) if value>=b[0] or i==0 else (bins[i-1],b)
        return bins[-1],bins[-1]

    @staticmethod
    def fraction(value,a,b):
        # Fallback DEX disassembly confirms int-to-float before div-float.
        return np.float32(value-a[1])/np.float32(b[0]-a[1]) if b[0]!=a[1] else np.float32(0)

    def corners(self,tree,lux,cct):
        a,b = self.find(tree,lux)
        aa,ab = self.find(a[2],cct)
        ba,bb = self.find(b[2],cct)
        x,y,z = self.fraction(lux,a,b),self.fraction(cct,aa,ab),self.fraction(cct,ba,bb)
        result = {}
        for item,weight in zip((aa,ab,ba,bb),((1-y)*(1-x),(1-x)*y,(1-z)*x,x*z)):
            result[item[2]] = np.float32(result.get(item[2],0)+weight)
        return result

    def lut(self,lux=300,cct=5000,scene='common'):
        tree = self.scenes.get(scene) or self.scenes.get('common') or next(iter(self.scenes.values()))
        out = np.zeros(14739,np.float32)
        for index,weight in self.corners(tree,lux,cct).items():
            out += weight*np.frombuffer(self.raw,np.uint8,14739,self.lut_off+index*14739)
        return out.astype(np.uint8).reshape(17,17,17,3)

    def shading(self,zoom=1,lux=300,cct=5000):
        selected = 0
        for i,(threshold,_) in enumerate(self.zooms):
            if zoom>=threshold: selected=i
        out = np.zeros(8,np.float32)
        for index,weight in self.corners(self.zooms[selected][1],lux,cct).items():
            out += weight*np.frombuffer(self.raw,'<f4',8,self.shade_off+index*32)
        return out


@lru_cache(maxsize=2)
def parameters(name='fullm9/leica_filter_param_m9_snapshot.bin'):
    return LeicaParams(name)


def settings(info=None):
    lux,cct,zoom = 300,5000,1.
    if info:
        try:
            if info.aperture>0 and info.exposure>0 and float(info.iso)>0:
                ev = math.log2(info.aperture**2/info.exposure)-math.log2(float(info.iso)/100)
                lux = int(max(0,min(999,474.9-ev*23.45)))
        except (ValueError,TypeError,OverflowError): pass
        if info.focal>=50: zoom=max(3.2,min(4.3,info.focal/23))
    return lux,cct,zoom


def pixels(rgb,lut,shade,x,y,width,height):
    """Float32 native trilinear BGR LUT followed by noisy radial shading."""
    c = rgb.astype(np.float32)/np.float32(255)*np.float32(16)
    b = np.minimum(c.astype(np.int32),15)
    f = (c-b).astype(np.float32)
    out = np.zeros_like(c)
    for i in (0,1):
        for j in (0,1):
            for k in (0,1):
                weight = ((f[...,0] if i else 1-f[...,0])*(f[...,1] if j else 1-f[...,1])*(f[...,2] if k else 1-f[...,2])).astype(np.float32)
                out += weight[...,None]*lut[b[...,0]+i,b[...,1]+j,b[...,2]+k,::-1].astype(np.float32)/np.float32(255)
    xx = (((x+np.float32(.5))/np.float32(width)-np.float32(.5))*np.float32(width))/np.float32(height)+np.float32(.5)-np.float32(.5)
    yy = (y+np.float32(.5))/np.float32(height)-np.float32(.5)
    angle=(yy-np.float32(.5))*np.float32(78.233)+(xx-np.float32(.5))*np.float32(12.9898)
    # Ghidra rounds the literal to 43758.55; the actual ARM FMOV bit pattern
    # is 0x472aee8c (one ULP lower). Fract makes that one bit observable.
    multiplier=np.array(0x472aee8c,dtype=np.uint32).view(np.float32)
    n = np.sin(angle.astype(np.float64)).astype(np.float32)*multiplier
    radial = np.clip((np.sqrt(yy*yy+xx*xx)+(n-np.floor(n))*np.float32(.04)*shade[2]-shade[0])/(shade[1]-shade[0]),0,1)
    lum = out[...,0]*np.float32(.499)+out[...,1]*np.float32(.387)+out[...,2]*np.float32(.114)
    with np.errstate(over='ignore'):
        gain = shade[7]+shade[6]/(np.exp(shade[4]*(shade[5]-lum))+np.float32(1))
    delta = (out[...,0]*np.float32(.299)+out[...,1]*np.float32(.587)+out[...,2]*np.float32(.114))*(shade[3]*(gain+radial*radial*(3-(radial+radial))*(1-gain))-1)
    return np.clip(out+delta[...,None],0,1)


def apply(image,lut,shade,cancelled=None):
    from PIL import Image
    src = np.asarray(image)
    h,w = src.shape[:2]
    result = np.empty_like(src)
    for top in range(0,h,128):
        if cancelled and cancelled(): raise Cancelled()
        y,x = np.mgrid[top:min(top+128,h),:w].astype(np.float32)
        out = pixels(src[top:top+128],lut,shade,x,y,w,h)
        result[top:top+128] = np.rint(out*np.float32(255)).astype(np.uint8)
    return Image.fromarray(result)
