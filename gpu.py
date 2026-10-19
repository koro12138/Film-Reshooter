"""OpenGL compute backend; contexts must be created and used in the same thread."""
import numpy as np
from engine import CATALOG, load_lut, quantize

COMMON = r'''
#version 430
layout(local_size_x=256) in;
layout(std430,binding=0) readonly buffer Input { vec4 src[]; };
layout(std430,binding=1) writeonly buffer Output { vec4 dst[]; };
uniform int width, count;
float sat(float x) { return clamp(x,0.,1.); }
vec3 quant(vec3 x) { return floor(clamp(x,0.,1.)*255.+.5)/255.; }
'''
# Byte-quantizing passes write the finished RGBA8 word straight from the shader:
# 4 bytes per pixel over the bus and no floor/clip/astype pass on the CPU. The
# value is identical to quantize() in engine.py because it rounds the same way.
COMMON_U8 = COMMON.replace('writeonly buffer Output { vec4 dst[]; };',
                           'writeonly buffer Output { uint dst[]; };')
PACKED_WRITE = ('ivec3 v=ivec3(floor(clamp(outc,0.,1.)*255.+.5)); '
                'dst[idx]=uint(v.r|(v.g<<8)|(v.b<<16)|0xFF000000u);')
FLOAT_WRITE = 'dst[idx]=vec4(quant(outc),1.);'
TONE = COMMON + r'''
layout(std430,binding=2) readonly buffer Lut { vec4 lut[]; };
uniform int n, rgbCount, lumaCount;
uniform vec3 domainMin, domainMax;
uniform vec2 rgbCurve[8], lumaCurve[8];
uniform float strength;
float curve(float x, bool isRgb) {
    float v = sat(x)*255.;
    int len = isRgb ? rgbCount : lumaCount;
    vec2 prev = isRgb ? rgbCurve[0] : lumaCurve[0];
    if(v<=prev.x) return sat(prev.y/255.);
    for(int j=1;j<len;j++) {
        vec2 p = isRgb ? rgbCurve[j] : lumaCurve[j];
        if(v<=p.x) return sat((prev.y+(p.y-prev.y)*(v-prev.x)/(p.x-prev.x))/255.);
        prev=p;
    }
    return sat(prev.y/255.);
}
void main() {
    int idx=int(gl_GlobalInvocationID.x);
    if(idx>=count) return;
    vec3 original=src[idx].rgb;
    vec3 coord=clamp((original-domainMin)/(domainMax-domainMin),0.,1.)*float(n-1);
    ivec3 base=min(ivec3(coord),ivec3(n-2));
    vec3 f=coord-vec3(base);
    ivec3 s=ivec3(1,n,n*n);
    // Stable descending sorting network; ties give the same tetrahedral result.
    if(f.x<f.y) { float t=f.x; f.x=f.y; f.y=t; int a=s.x; s.x=s.y; s.y=a; }
    if(f.y<f.z) { float t=f.y; f.y=f.z; f.z=t; int a=s.y; s.y=s.z; s.z=a; }
    if(f.x<f.y) { float t=f.x; f.x=f.y; f.y=t; int a=s.x; s.x=s.y; s.y=a; }
    int i0=base.x+base.y*n+base.z*n*n;
    vec3 c0=lut[i0].rgb, c1=lut[i0+s.x].rgb, c2=lut[i0+s.x+s.y].rgb, c3=lut[i0+1+n+n*n].rgb;
    vec3 outc=clamp(c0+(c1-c0)*f.x+(c2-c1)*f.y+(c3-c2)*f.z,0.,1.);
    for(int c=0;c<3;c++) outc[c]=curve(outc[c],true);
    float lum=dot(outc,vec3(.2126,.7152,.0722)), val=curve(lum,false);
    outc=clamp(lum>1e-6 ? outc*val/lum : vec3(val),0.,1.);
    vec3 delta=(clamp(strength,1.,1.8)-1.)*(outc-original);
    for(int c=0;c<3;c++) {
        float room=delta[c]>=0. ? 1.-outc[c] : outc[c];
        if(room>0.) outc[c]+=delta[c]*room/(room+abs(delta[c]));
    }
    dst[idx]=vec4(quant(outc),1.);
}
'''
FILM_BODY = r'''
uniform int yOffset, fullHeight, seed;
uniform float clarity, midpoint, vignette, shadows, midtones, highlights;
uniform float grain, grainSize, roughness, colorVariation;
float hashNoise(ivec2 p,int z) {
    uint v=uint(p.x)*521288629u+uint(p.y)*1597334677u+uint(z)*1821285621u;
    v=(v^(v>>16u))*2146121005u;
    v=(v^(v>>15u))*2221713035u;
    return float((v^(v>>16u))&16777215u)/8388607.5-1.;
}
float noiseAt(ivec2 p,int z) {
    vec2 f=vec2(p)/(max(0.,grainSize)/25.+1.);
    ivec2 b=ivec2(f); f-=vec2(b);
    float smoothValue=(hashNoise(b,z)*(1.-f.x)+hashNoise(b+ivec2(1,0),z)*f.x)*(1.-f.y)
        +(hashNoise(b+ivec2(0,1),z)*(1.-f.x)+hashNoise(b+ivec2(1,1),z)*f.x)*f.y;
    float r=clamp(roughness/100.,0.,.7);
    return smoothValue*(1.-r)+hashNoise(p,z+83)*r;
}
float lumaAt(int x,int y) { return dot(src[y*width+clamp(x,0,width-1)].rgb,vec3(.2126,.7152,.0722)); }
void main() {
    int idx=int(gl_GlobalInvocationID.x); if(idx>=count) return;
    int x=idx%width, y=idx/width;
    vec3 rgb=src[(y+1)*width+x].rgb;
    float lum=dot(rgb,vec3(.2126,.7152,.0722));
    float blurred=0.;
    for(int j=0;j<3;j++) blurred+=(lumaAt(x-1,y+j)+lumaAt(x,y+j)*2.+lumaAt(x+1,y+j))*(j==1?2.:1.);
    blurred/=16.;
    float detail=(lum-blurred)*clamp(clarity,-20.,0.)/100.;
    vec2 pos=vec2((float(x)*2.+1.-float(width))/float(width),
                  (float(y+yOffset)*2.+1.-float(fullHeight))/float(fullHeight));
    float mid=clamp(midpoint/100.,0.,.85);
    float radius=sat((dot(pos,pos)*.5-mid)/(1.-mid));
    float vig=pow(2.,clamp(vignette/100.,-1.25,1.25)*radius*radius*(3.-2.*radius));
    float level=lum<.5 ? shadows+(midtones-shadows)*lum*2. : midtones+(highlights-midtones)*(lum*2.-1.);
    float amplitude=clamp(grain,0.,100.)/100.*max(0.,level)/100.*.06;
    ivec2 pixel=ivec2(x,y+yOffset);
    float g=noiseAt(pixel,seed)*amplitude;
    vec3 outc=(rgb+vec3(detail))*vig+vec3(g);
    for(int c=0;c<3;c++) outc[c]+=noiseAt(pixel,seed+c+1)*amplitude*clamp(colorVariation/100.,0.,1.);
    dst[idx]=vec4(quant(outc),1.);
}
'''
# The film pass is the last stage before the host: pack RGBA8 on the device.
FILM = COMMON + FILM_BODY
FILM_U8 = COMMON_U8 + FILM_BODY.replace(FLOAT_WRITE, PACKED_WRITE)


class GpuRenderer:
    def __init__(self):
        import sys
        if sys.platform == 'darwin':
            raise RuntimeError('macOS 使用 Metal，OpenGL 4.1 不支持此计算后端')
        import moderngl
        self.ctx = moderngl.create_standalone_context(require=430)
        self.name = self.ctx.info['GL_RENDERER']
        self.tone_program = self.ctx.compute_shader(TONE)
        self.film_program = self.ctx.compute_shader(FILM_U8)
        quantization = 'floor(clamp(x,0.,1.)*255.+.5)/255.'
        self.tone_float_program = self.ctx.compute_shader(TONE.replace(quantization,'clamp(x,0.,1.)'))
        self.film_float_program = self.ctx.compute_shader(FILM.replace(quantization,'clamp(x,0.,1.)'))
        self.luts = {}
        self._dispatch_buffers = {}
        self._resident_programs={}
        self.post=None
        self._photo_key=None
        self.photo_uploads=0
        self.photo_cache_hit=False

    def _buffer(self,key,size):
        previous=self._dispatch_buffers.get(key)
        if previous is None or previous.size<size:
            replacement=self.ctx.buffer(reserve=1<<(max(1,size)-1).bit_length())
            if previous is not None:previous.release()
            self._dispatch_buffers[key]=replacement
        return self._dispatch_buffers[key]

    def dispatch(self, program, rgb, out_shape, high_precision=False, *, packed_output=False):
        # Output storage follows the shader ABI, not merely its quantization.
        # Legacy tone writes float4 even when the final result is 8-bit.
        if high_precision and packed_output:
            raise ValueError('Packed output cannot preserve float precision')
        packed = rgb.dtype == np.uint32
        if packed:
            if rgb.ndim != 2:raise ValueError('Packed input must be HxW uint32')
            # HxW uint32 RGBA8: the byte add and blend passes already have one.
            src = rgb
            payload = np.ascontiguousarray(src).tobytes()
            width = rgb.shape[1]
        else:
            src = np.ones((*rgb.shape[:2], 4), np.float32)
            src[..., :3] = rgb
            payload = src.tobytes()
            width = rgb.shape[1]
        output_bytes=out_shape[0]*out_shape[1]*(4 if packed_output else 16)
        # Reuse bounded stripe buffers. Full-photo Monopan buffers stay temporary.
        reusable=max(len(payload),output_bytes)<=16*1024*1024
        if reusable:
            input_buffer=self._buffer('input',len(payload))
            output_buffer=self._buffer('output',output_bytes)
            input_buffer.write(payload)
        else:
            input_buffer = self.ctx.buffer(payload)
            output_buffer = self.ctx.buffer(reserve=output_bytes)
        try:
            input_buffer.bind_to_storage_buffer(0)
            output_buffer.bind_to_storage_buffer(1)
            if 'width' in program:
                program['width'].value = width
            program['count'].value = out_shape[0]*out_shape[1]
            program.run(group_x=(out_shape[0]*out_shape[1]+255)//256)
            self.ctx.memory_barrier()
            if packed_output:
                return np.frombuffer(output_buffer.read(size=output_bytes), np.uint8).reshape(*out_shape, 4)[..., :3].copy()
            out = np.frombuffer(output_buffer.read(size=output_bytes), np.float32).reshape(*out_shape, 4)[..., :3]
            return out.copy() if high_precision else quantize(out)
        finally:
            if not reusable:
                input_buffer.release()
                output_buffer.release()

    def tone(self, rgb, index, high_precision=False):
        program = self.tone_float_program if high_precision else self.tone_program
        self.configure_tone(program,index)
        return self.dispatch(program, rgb, rgb.shape[:2],high_precision)

    def configure_tone(self,program,index):
        n, domain, lut = load_lut(index)
        if index not in self.luts:
            padded = np.ones((len(lut), 4), np.float32)
            padded[:, :3] = lut
            self.luts[index] = self.ctx.buffer(padded.tobytes())
        self.luts[index].bind_to_storage_buffer(2)
        program['n'].value = n
        program['domainMin'].value = tuple(domain[0])
        program['domainMax'].value = tuple(domain[1])
        p = CATALOG[index]
        program['strength'].value = p['strength']
        for name in ('rgb', 'luma'):
            points = np.asarray(p[name], np.float32).reshape(-1, 2)
            program[name+'Count'].value = len(points)
            padded = np.zeros((8, 2), np.float32)
            padded[:len(points)] = points
            program[name+'Curve'].write(padded.tobytes())

    def film(self, padded, index, y0, height, high_precision=False):
        program = self.film_float_program if high_precision else self.film_program
        self.configure_film(program,index,y0,height)
        return self.dispatch(program, padded.astype(np.float32)/np.float32(1 if high_precision else 255),
                             (len(padded)-2, padded.shape[1]),high_precision,
                             packed_output=not high_precision)

    def configure_film(self,program,index,y0,height):
        p=CATALOG[index]
        for name in ('clarity', 'midpoint', 'vignette', 'shadows', 'midtones', 'highlights',
                     'grain', 'grainSize', 'roughness', 'colorVariation'):
            program[name].value = p[name]
        program['yOffset'].value = y0
        program['fullHeight'].value = height
        program['seed'].value = index

    def cache_photo(self,rgb,key):
        h,w=rgb.shape[:2]
        self.photo_cache_hit=self._photo_key is key
        if w*h*4>128*1024*1024:return None
        if self._photo_key is not key:
            rgba=np.empty((h,w,4),np.uint8);rgba[...,:3]=rgb;rgba[...,3]=255
            self._buffer('photo',rgba.nbytes).write(memoryview(rgba));self._photo_key=key
            self.photo_uploads+=1
        return self._dispatch_buffers['photo'],w,h

    def clear_photo(self):
        self._photo_key=None
        b=self._dispatch_buffers.pop('photo',None)
        if b is not None:b.release()

    def tone_film(self,padded,index,y0,height,high_precision=False,cached=None,out_rows=None):
        """Keep the tone result on device, including its original byte boundary."""
        if high_precision:
            tone=self.tone_float_program;film=self.film_float_program
        else:
            key='tone_cached_byte' if cached else 'tone_byte'
            if key not in self._resident_programs:
                source=TONE.replace('uniform int width, count;',
                    'uniform int width, count; uniform float byteValue[256];')
                source=source.replace('return floor(clamp(x,0.,1.)*255.+.5)/255.;',
                    'ivec3 v=ivec3(floor(clamp(x,0.,1.)*255.+.5)); return vec3(byteValue[v.r],byteValue[v.g],byteValue[v.b]);')
                if cached:
                    source=source.replace('readonly buffer Input { vec4 src[]; }','readonly buffer Input { uint photo[]; }')
                    source=source.replace('uniform int n, rgbCount, lumaCount;',
                        'uniform int n, rgbCount, lumaCount; uniform int sourceRow,sourceHeight;')
                    source=source.replace('vec3 original=src[idx].rgb;',
                        'uint v=photo[clamp(sourceRow+idx/width,0,sourceHeight-1)*width+idx%width]; vec3 original=vec3(byteValue[v&255u],byteValue[(v>>8)&255u],byteValue[(v>>16)&255u]);')
                self._resident_programs[key]=self.ctx.compute_shader(source)
                self._resident_programs[key]['byteValue'].write((np.arange(256,dtype=np.float32)/np.float32(255)).tobytes())
            tone=self._resident_programs[key];film=self.film_program
        if cached:
            inp,w,full_h=cached;h=out_rows+2
            tone['sourceRow'].value=y0-1;tone['sourceHeight'].value=full_h
        else:
            h,w=padded.shape[:2]
            rgba=np.ones((h,w,4),np.float32);rgba[...,:3]=padded
            inp=self._buffer('input',rgba.nbytes);inp.write(memoryview(rgba))
        out_h=h-2
        intermediate=self._buffer('intermediate',h*w*16)
        output=self._buffer('output',out_h*w*(16 if high_precision else 4))
        inp.bind_to_storage_buffer(0);intermediate.bind_to_storage_buffer(1)
        self.configure_tone(tone,index)
        if 'width' in tone:tone['width'].value=w
        tone['count'].value=h*w
        tone.run(group_x=(h*w+255)//256);self.ctx.memory_barrier()
        intermediate.bind_to_storage_buffer(0);output.bind_to_storage_buffer(1)
        self.configure_film(film,index,y0,height);film['width'].value=w;film['count'].value=out_h*w
        film.run(group_x=(out_h*w+255)//256);self.ctx.memory_barrier()
        if high_precision:
            out=np.frombuffer(output.read(size=out_h*w*16),np.float32).reshape(out_h,w,4)[...,:3]
            return out.copy()
        return np.frombuffer(output.read(size=out_h*w*4),np.uint8).reshape(out_h,w,4)[...,:3].copy()

    def postprocessor(self):
        if self.post is None:
            from gpu_post import GpuPost
            self.post=GpuPost(self)
        return self.post

    def close(self):
        self._photo_key=None
        if self.post:self.post.close();self.post=None
        for program in self._resident_programs.values():program.release()
        self._resident_programs.clear()
        for buffer in self._dispatch_buffers.values():buffer.release()
        self._dispatch_buffers.clear()
        if getattr(self,'m3_program',None):
            self.m3_program.release()
            for b in self.m3_buffers:b.release()
        for b in self.luts.values():
            b.release()
        self.tone_program.release()
        self.film_program.release()
        self.tone_float_program.release()
        self.film_float_program.release()
        self.ctx.release()
