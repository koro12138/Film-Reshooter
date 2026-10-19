"""Vendor-neutral packed-RGB compute postprocessing with persistent device buffers.

Small noise statistics are read back; full images stay on the device between
scene, denoise, texture and blend. CPU mode remains the numerical reference.
"""
import math
import os
import time
import numpy as np
from engine import Cancelled

COMMON=r'''
#version 430
layout(local_size_x=256) in;
layout(std430,binding=0) readonly buffer Input {uint src[];};
layout(std430,binding=1) writeonly buffer Output {uint dst[];};
uniform int width,height,count,base;
vec3 unpackRGB(uint v){return vec3(v&255u,(v>>8)&255u,(v>>16)&255u);}
uint packRGB(vec3 v){uvec3 b=uvec3(clamp(v,0.,255.));return b.r|(b.g<<8)|(b.b<<16)|0xff000000u;}
float sat(float v){return clamp(v,0.,1.);}
float plainLum(vec3 p){precise float v=(p.r*.2126+p.g*.7152)+p.b*.0722;return v;}
float fusedLum(vec3 p){return fma(p.b,.0722,fma(p.r,.2126,p.g*.7152));}
int at(int x,int y){return clamp(y,0,height-1)*width+clamp(x,0,width-1);}
'''

RGB_UPLOAD=r'''
#version 430
layout(local_size_x=256) in;
layout(std430,binding=0) readonly buffer Raw {uint bytes[];};
layout(std430,binding=1) writeonly buffer Packed {uint pixels[];};
uniform int count,base;
uint byteAt(int i){return (bytes[i/4]>>uint(8*(i%4)))&255u;}
void main(){
 int i=base+int(gl_GlobalInvocationID.x);if(i>=count)return;
 pixels[i]=byteAt(i*3)|(byteAt(i*3+1)<<8)|(byteAt(i*3+2)<<16)|0xff000000u;
}
'''

HISTOGRAM=COMMON+r'''
layout(std430,binding=2) buffer Histogram {uint hist[];};
uniform int stepSize,samplesX;
shared uint bins[256];
void main(){
 uint lane=gl_LocalInvocationID.x;bins[lane]=0u;barrier();
 int i=base+int(gl_GlobalInvocationID.x);
 if(i<count){
 int x=1+(i%samplesX)*stepSize,y=1+(i/samplesX)*stepSize;
 float aa=fusedLum(unpackRGB(src[at(x,y)]));
 float ab=fusedLum(unpackRGB(src[at(x+1,y)])),ba=fusedLum(unpackRGB(src[at(x,y+1)])),bb=fusedLum(unpackRGB(src[at(x+1,y+1)]));
 if(aa>=8.&&aa<=246.&&abs(aa-ab)<=12.&&abs(aa-ba)<=12.&&abs(bb-ab)<=12.&&abs(bb-ba)<=12.){
 precise float lap=((aa-ab)-ba)+bb;
 int bin=clamp(int(fma(abs(lap),2.,.5)),0,255);atomicAdd(bins[bin],1u);
 }}
 barrier();if(bins[lane]!=0u)atomicAdd(hist[lane],bins[lane]);
}
'''

HORIZONTAL=COMMON.replace('local_size_x=256','local_size_x=32')+r'''
layout(std430,binding=2) writeonly buffer Statistics {float stats[];};
uniform int startRow;
void main(){
 int row=base+int(gl_GlobalInvocationID.x);if(row>=count)return;
 int y=clamp(startRow+row,0,height-1);float a[7],u[7],v[7];
 precise float sy=0.,su=0.,sv=0.,yy=0.,uu=0.,vv=0.;
 for(int j=0;j<7;j++){
   vec3 p=unpackRGB(src[at(j-3,y)]);a[j]=fusedLum(p);u[j]=p.r-a[j];v[j]=p.b-a[j];
   sy+=a[j];yy=fma(a[j],a[j],yy);uu=fma(u[j],u[j],uu);vv=fma(v[j],v[j],vv);
 }
 for(int j=6;j>=0;j--){su+=u[j];sv+=v[j];}
 for(int x=0;x<width;x++){
   int o=(row*width+x)*6;stats[o]=sy;stats[o+1]=yy;stats[o+2]=su;stats[o+3]=uu;stats[o+4]=sv;stats[o+5]=vv;
   vec3 old=unpackRGB(src[at(x-3,y)]),next=unpackRGB(src[at(x+4,y)]);
   precise float ay=fusedLum(old),by=fusedLum(next),au=old.r-ay,bu=next.r-by,av=old.b-ay,bv=next.b-by;
   sy+=by-ay;yy+=fma(by,by,-(ay*ay));su+=bu-au;sv=(bv-av)+sv;
   uu=fma(bu,bu,-(au*au))+uu;vv=fma(bv,bv,-(av*av))+vv;
 }
}
'''

VERTICAL=COMMON+r'''
layout(std430,binding=2) readonly buffer Statistics {float stats[];};
layout(std430,binding=3) buffer Carry {float carry[];};
uniform int top,bottom,finish;
uniform float sigma;
void main(){
 int x=base+int(gl_GlobalInvocationID.x);if(x>=count)return;
 precise float s[6];for(int c=0;c<6;c++)s[c]=top==0?0.:carry[x*6+c];
 if(top==0)for(int j=0;j<7;j++)for(int c=0;c<6;c++)s[c]=stats[(j*width+x)*6+c]+s[c];
 precise float variance=sigma*sigma,ny=(finish!=0?1.:2.4)*variance,nc=(finish!=0?2.:4.)*variance;
 precise float ky=(finish!=0?.4:.88)*ny,kc=(finish!=0?.65:.95)*nc;
 float edge=fma(variance,9.,4.);int vectorEnd=width>8?width-(width%8!=0?width%8:8):0;
 for(int y=top;y<bottom;y++){
   vec3 p=unpackRGB(src[y*width+x]);precise float my=s[0]/49.,mu=s[2]/49.,mv=s[4]/49.;
   precise float vy=max(0.,s[1]/49.-my*my),vu=max(0.,s[3]/49.-mu*mu),vv=max(0.,s[5]/49.-mv*mv);
   if(x>=vectorEnd)vu=max(0.,fma(-mu,mu,s[3]/49.));
   precise float yy=x<vectorEnd?(p.g*.7152+p.r*.2126)+p.b*.0722:fusedLum(p);
   precise float u=p.r-yy,v=p.b-yy,d=yy-my,e=1./(d*d/edge+1.);
   precise float outy=yy+(my-yy)*(ky/(ny+vy))*e,ku=(kc/(nc+vu))*e;
   precise float outv=(outy+v)+((mv-v)*(kc/(nc+vv)))*e;
   precise float r=x<vectorEnd?(outy+u)+((mu-u)*(kc/(nc+vu)))*e:outy+fma(ku,mu-u,u);
   precise float g=x<vectorEnd?((outy+r*-.2126)+outv*-.0722)/.7152:fma(outv,-.0722,fma(r,-.2126,outy))/.7152;
   dst[y*width+x]=packRGB(floor(clamp(vec3(r,g,outv),0.,255.)+.5));
   if(y+1<height)for(int c=0;c<6;c++){
     s[c]-=stats[((y-top)*width+x)*6+c];s[c]=stats[((y-top+7)*width+x)*6+c]+s[c];
   }
 }
 for(int c=0;c<6;c++)carry[x*6+c]=s[c];
}
'''

SCENE=COMMON+r'''
layout(std430,binding=2) readonly buffer LUT {uint lut[];};
uniform float shading[8];
float div32(float a,float b){return float(double(a)/double(b));}
// Double sine, restricted to the finite scene-coordinate domain. Range
// reduction retains the low part of pi, before a degree-21 polynomial.
double sceneSin(double x){
 precise double k=roundEven(x*.15915494309189533576888376337251lf);
 precise double d=(x-k*6.283185307179586232lf)-k*2.449293598294706414e-16lf;
 if(d>1.57079632679489661923lf)d=(3.141592653589793116lf-d)+1.224646799147353207e-16lf;
 if(d< -1.57079632679489661923lf)d=(-3.141592653589793116lf-d)-1.224646799147353207e-16lf;
 precise double z=d*d;
 precise double p=1.9572941063391261231e-20lf;
 p=p*z-8.22063524662432971696e-18lf;p=p*z+2.8114572543455207632e-15lf;
 p=p*z-7.6471637318198164759e-13lf;p=p*z+1.6059043836821614599e-10lf;
 p=p*z-2.5052108385441718775e-8lf;p=p*z+2.7557319223985890653e-6lf;
 p=p*z-1.984126984126984127e-4lf;p=p*z+8.3333333333333333333e-3lf;
 p=p*z-1.6666666666666666667e-1lf;return d+(d*z)*p;
}
void main(){
 int idx=base+int(gl_GlobalInvocationID.x);if(idx>=count)return;int x=idx%width,y=idx/width;
 vec3 inputRGB=unpackRGB(src[idx]);
 precise vec3 v=vec3(div32(inputRGB.r,255.),div32(inputRGB.g,255.),div32(inputRGB.b,255.))*16.;
 ivec3 b=min(ivec3(v),ivec3(15));precise vec3 f=v-vec3(b),outc=vec3(0);
 for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++){
   precise float weight=((i!=0?f.r:1.-f.r)*(j!=0?f.g:1.-f.g))*(k!=0?f.b:1.-f.b);
   vec3 rgb=unpackRGB(lut[((b.r+i)*17+b.g+j)*17+b.b+k]).bgr;
   for(int c=0;c<3;c++)outc[c]+=div32(weight*rgb[c],255.);
 }
 precise float xx=div32(float(x)+.5,float(width))-.5;xx*=float(width);xx=div32(xx,float(height));xx+=.5;xx-=.5;
 precise float yy=div32(float(y)+.5,float(height))-.5;
 precise float angle=(yy-.5)*78.233+(xx-.5)*12.9898;
 precise float n=float(sceneSin(double(angle)))*uintBitsToFloat(0x472aee8cu);
 precise float radial=sat(((sqrt(yy*yy+xx*xx)+((n-floor(n))*.04)*shading[2])-shading[0])/(shading[1]-shading[0]));
 precise float lum=(outc.r*.499+outc.g*.387)+outc.b*.114;
 precise float gain=shading[7]+shading[6]/(exp(shading[4]*(shading[5]-lum))+1.);
 precise float delta=((outc.r*.299+outc.g*.587)+outc.b*.114)*
     (shading[3]*(gain+((radial*radial)*(3.-(radial+radial)))*(1.-gain))-1.);
 dst[idx]=packRGB(roundEven(clamp(outc+delta,0.,1.)*255.));
}
'''

TEXTURE_COMMON=COMMON+r'''
layout(std430,binding=4) readonly buffer Reference {uint reference[];};
float aLum(int x,int y){return plainLum(unpackRGB(reference[at(x,y)]));}
float bLum(int x,int y){return plainLum(unpackRGB(src[at(x,y)]));}
float blur(int x,int y,bool a){
 precise float value=0.;
 for(int j=-1;j<=1;j++)for(int i=-1;i<=1;i++){
   float weight=(i==0?2.:1.)*(j==0?2.:1.)*.0625;
   value+=(a?aLum(x+i,y+j):bLum(x+i,y+j))*weight;
 }return value;
}
'''
TEXTURE_NOISE=TEXTURE_COMMON+r'''
layout(std430,binding=2) writeonly buffer Samples {float samples[];};
uniform int stepSize,samplesX;
void main(){
 int idx=base+int(gl_GlobalInvocationID.x);if(idx>=count)return;
 int x=1+(idx%samplesX)*stepSize,y=1+(idx/samplesX)*stepSize;
 uint hash=(uint(y)*0x9e3779b1u+uint(x)*0x85ebca77u);hash=(hash^(hash>>13))*0xc2b2ae3du;
 x=clamp(x+int(hash%uint(stepSize)),0,width-2);y=clamp(y+int((hash>>16)%uint(stepSize)),0,height-2);
 precise float lap=(((aLum(x,y)*4.-aLum(x-1,y))-aLum(x+1,y))-aLum(x,y-1))-aLum(x,y+1);
 samples[idx]=abs(lap);
}
'''
TEXTURE=TEXTURE_COMMON+r'''
layout(std430,binding=5) readonly buffer Original {uint original[];};
uniform float noise,strength;
void main(){
 int idx=base+int(gl_GlobalInvocationID.x);if(idx>=count)return;int x=idx%width,y=idx/width;
 vec3 p=unpackRGB(src[idx]);precise vec3 result=p;
 if(width>=5&&height>=5){
 precise float center=aLum(x,y),smoothed=blur(x,y,true),detail=center-smoothed;
 if(noise*.8+.75<abs(detail)){
  precise float targetSmooth=blur(x,y,false),targetDetail=bLum(x,y)-targetSmooth;
  precise float gain=clamp((targetSmooth*(255.-targetSmooth))/max(64.,smoothed*(255.-smoothed)),.5,1.5),wanted=gain*detail;
  if(abs(targetDetail)+.5<abs(wanted)&&wanted*targetDetail>=-.25){
   precise float ex=0.,ey=0.,cross=0.;
   for(int j=-1;j<=1;j++)for(int i=-1;i<=1;i++){
    precise float dx=aLum(x+i+1,y+j)-aLum(x+i-1,y+j),dy=aLum(x+i,y+j+1)-aLum(x+i,y+j-1);
    ex+=dx*dx;ey+=dy*dy;cross+=dx*dy;
   }
   precise float d=ex-ey;
   precise float coherence=sat((sqrt(d*d+cross*cross*4.)/((noise*noise)*36.+(ex+ey)+1.)-.35)/.4);
   precise float headroom=sat(min(targetSmooth*.0625,(255.-targetSmooth)*.0625));
   precise float smoothCoherence=(coherence*coherence)*(3.-(coherence+coherence));
   precise float delta=headroom*(clamp(wanted-targetDetail,-12.,12.)*smoothCoherence);
   delta=clamp(delta,-min(p.r,min(p.g,p.b)),255.-max(p.r,max(p.g,p.b)));
   result=roundEven(p+delta);
  }
 }
 }
 if(strength!=1.){precise vec3 a=unpackRGB(original[idx]);result=floor(clamp(a+(result-a)*strength,0.,255.));}
 dst[idx]=packRGB(result);
}
'''

SIGMA_GPU=r'''
#version 430
#extension GL_ARB_gpu_shader_fp64 : require
layout(local_size_x=1) in;
layout(std430,binding=2) readonly buffer Histogram {uint hist[];};
layout(std430,binding=6) buffer Parameters {float parameters[];};
void main(){
 uint total=0u;for(int i=0;i<256;i++)total+=hist[i];
 uint sum=0u;int median=0;
 if(total>=32u)for(int i=0;i<256;i++){sum+=hist[i];if(sum>=(total+1u)/2u){median=i;break;}}
 parameters[0]=total>=32u?max(.7,min(7.,float(double(median)/double(float(2.698))))):1.;
}
'''

NOISE_GPU=r'''
#version 430
#extension GL_ARB_gpu_shader_fp64 : require
layout(local_size_x=256) in;
layout(std430,binding=2) readonly buffer Samples {float samples[];};
layout(std430,binding=6) buffer Parameters {float parameters[];};
uniform int sampleCount;
shared uint bins[256];shared uint prefix;shared uint rank;
void main(){
 uint lane=gl_LocalInvocationID.x;
 if(lane==0u){prefix=0u;rank=uint(sampleCount/5);}barrier();
 for(int shift=24;shift>=0;shift-=8){
  bins[lane]=0u;barrier();
  uint mask=shift==24?0u:(0xffffffffu<<uint(shift+8));
  for(uint i=lane;i<uint(sampleCount);i+=256u){uint bits=floatBitsToUint(samples[i]);if((bits&mask)==prefix)atomicAdd(bins[(bits>>uint(shift))&255u],1u);}
  barrier();
  if(lane==0u){uint below=0u;for(uint b=0u;b<256u;b++){if(rank<below+bins[b]){rank-=below;prefix|=b<<uint(shift);break;}below+=bins[b];}}
  barrier();
 }
 if(lane==0u)parameters[1]=float(double(uintBitsToFloat(prefix))/double(float(1.133)));
}
'''

HORIZONTAL_M3=HORIZONTAL.replace('for(int j=6;j>=0;j--)','for(int j=0;j<7;j++)')
_vertical_math=VERTICAL[VERTICAL.index('   precise float vy='):VERTICAL.index('   if(y+1<height)')]
VERTICAL_M3=VERTICAL.replace(_vertical_math,r'''
   precise float vy=max(0.,fma(-my,my,exactDiv(s[1],49.))),vu=max(0.,fma(-mu,mu,exactDiv(s[3],49.))),vv=max(0.,fma(-mv,mv,exactDiv(s[5],49.)));
   precise float yy=fusedLum(p),u=p.r-yy,v=p.b-yy,d=yy-my,e=exactDiv(1.,exactDiv(d*d,edge)+1.);
   precise float outy=fma(my-yy,exactDiv(ky,ny+vy)*e,yy);
   precise float outu=fma(mu-u,exactDiv(kc,nc+vu)*e,u),outv=fma(mv-v,exactDiv(kc,nc+vv)*e,v);
   precise float r=outy+outu,b=outy+outv,g=exactDiv(fma(b,-.0722,fma(r,-.2126,outy)),.7152);
   dst[y*width+x]=packRGB(floor(clamp(vec3(r,g,b),0.,255.)+.5));
''')
VERTICAL_M3=VERTICAL_M3.replace('void main(){','float exactDiv(float a,float b){return float(double(a)/double(b));}\nvoid main(){')
for _component in range(6):
    VERTICAL_M3=VERTICAL_M3.replace(f's[{_component}]/49.',f'exactDiv(s[{_component}],49.)')
VERTICAL_M3_FINISH=VERTICAL.replace('void main(){','float exactDiv(float a,float b){return float(double(a)/double(b));}\nvoid main(){')
for _component in range(6):
    VERTICAL_M3_FINISH=VERTICAL_M3_FINISH.replace(f's[{_component}]/49.',f'exactDiv(s[{_component}],49.)')
VERTICAL_M3_FINISH=VERTICAL_M3_FINISH.replace('e=1./(d*d/edge+1.)','e=exactDiv(1.,exactDiv(d*d,edge)+1.)')
for _numerator,_denominator in (('ky','ny+vy'),('kc','nc+vu'),('kc','nc+vv')):
    VERTICAL_M3_FINISH=VERTICAL_M3_FINISH.replace(f'{_numerator}/({_denominator})',f'exactDiv({_numerator},{_denominator})')
VERTICAL_M3_FINISH=VERTICAL_M3_FINISH.replace('((outy+r*-.2126)+outv*-.0722)/.7152','exactDiv((outy+r*-.2126)+outv*-.0722,.7152)')
VERTICAL_M3_FINISH=VERTICAL_M3_FINISH.replace('fma(outv,-.0722,fma(r,-.2126,outy))/.7152','exactDiv(fma(outv,-.0722,fma(r,-.2126,outy)),.7152)')
VERTICAL_M3_FINISH=VERTICAL_M3_FINISH.replace(
    'precise float g=x<vectorEnd?exactDiv((outy+r*-.2126)+outv*-.0722,.7152):exactDiv(fma(outv,-.0722,fma(r,-.2126,outy)),.7152);',
    'precise float redTerm=r*-.2126;precise float blueTerm=outv*-.0722;precise float green1=outy+redTerm;precise float green2=green1+blueTerm;precise float numerator=x<vectorEnd?green2:fma(outv,-.0722,fma(r,-.2126,outy));precise float g=exactDiv(numerator,.7152);')


class GpuPost:
    def __init__(self,gpu):
        self.gpu=gpu;self.ctx=gpu.ctx;self.buffers={};self.programs={};self.last_report={}
        self.host_read=None;self.queries=[]
        if 'GL_ARB_gpu_shader_fp64' not in self.ctx.extensions:raise RuntimeError('GPU 缺少双精度场景计算支持')

    def buffer(self,key,size):
        old=self.buffers.get(key)
        if old is None or old.size<size:
            new=self.ctx.buffer(reserve=((max(4,size)+65535)//65536)*65536)
            if old is not None:old.release()
            self.buffers[key]=new
        return self.buffers[key]

    def upload(self,key,rgb):
        a=np.ascontiguousarray(rgb,dtype=np.uint8);h,w=a.shape[:2]
        if os.environ.get('CAMERALOOK_LEGACY_POST_UPLOAD')=='1':
            packed=np.empty((h,w,4),np.uint8);packed[...,:3]=a;packed[...,3]=255
            b=self.buffer(key,packed.nbytes);b.write(memoryview(packed));return b
        raw=self.buffer('upload_rgb',a.nbytes);raw.write(memoryview(a))
        b=self.buffer(key,w*h*4)
        self.run('rgb_upload',RGB_UPLOAD,w*h,w,h,{0:raw,1:b})
        return b

    def read(self,buffer,w,h):
        size=w*h*4
        if self.host_read is None or len(self.host_read)<size:self.host_read=bytearray(size)
        buffer.read_into(self.host_read,size=size)
        result=np.frombuffer(self.host_read,np.uint8,count=size).reshape(h,w,4)[...,:3].copy()
        return result

    def collect_queries(self):
        times={}
        for name,query in self.queries:
            times[name]=times.get(name,0.)+query.elapsed/1e9
        self.queries.clear()
        return times

    def run(self,name,source,count,w,h,bindings,local=256,**uniforms):
        if name not in self.programs:self.programs[name]=self.ctx.compute_shader(source)
        p=self.programs[name]
        for binding,b in bindings.items():b.bind_to_storage_buffer(binding)
        for key,val in dict(width=w,height=h,count=count,**uniforms).items():
            if key in p:p[key].value=val
        query=self.ctx.query(time=True) if os.environ.get('CAMERALOOK_GPU_TIMING','1')!='0' else None
        if query:query.__enter__()
        try:
            for base in range(0,count,local*32768):
                if 'base' in p:p['base'].value=base
                p.run(group_x=(min(count-base,local*32768)+local-1)//local)
            self.ctx.memory_barrier()
        finally:
            if query:
                query.__exit__(None,None,None);self.queries.append((name,query))

    def denoise_buffer(self,src,out,w,h,finish=False,cancelled=None,*,m3_prepare=False,exact_divisions=False):
        if w<2 or h<2 or w>16384 or h>16384:
            self.ctx.copy_buffer(out,src,size=w*h*4);return
        histogram=self.buffer('histogram',1024);histogram.clear()
        step=8 if w*h>16000000 else 4;nx=max(0,(w-4)//step+1);ny=max(0,(h-4)//step+1)
        self.run('histogram',HISTOGRAM,nx*ny,w,h,{0:src,2:histogram},stepSize=step,samplesX=nx)
        gpu_stats=os.environ.get('CAMERALOOK_CPU_GPU_STATS')!='1'
        bindings={}
        if gpu_stats:
            parameters=self.buffer('parameters',8)
            self.run('sigma',SIGMA_GPU,1,w,h,{2:histogram,6:parameters},local=1)
            bindings[6]=parameters;sigma=1.
        else:
            hist=np.frombuffer(histogram.read(size=1024),np.uint32);total=int(hist.sum())
            median=int(np.searchsorted(hist.cumsum(),(total+1)//2)) if total>=32 else 0
            sigma=float(np.maximum(np.float32(.7),np.minimum(np.float32(7),np.float32(median)/np.float32(2.698)))) if total>=32 else 1.
        rows=max(1,min(512,64*1024*1024//(w*24)-7))
        stats=self.buffer('statistics',(rows+7)*w*24);carry=self.buffer('carry',w*24)
        for top in range(0,h,rows):
            if cancelled and cancelled():raise Cancelled()
            bottom=min(h,top+rows)
            horizontal=HORIZONTAL_M3 if m3_prepare else HORIZONTAL
            vertical=VERTICAL_M3 if m3_prepare else VERTICAL_M3_FINISH if exact_divisions else VERTICAL
            if gpu_stats:
                vertical=vertical.replace('uniform float sigma;','layout(std430,binding=6) readonly buffer Parameters {float parameters[];};')
                vertical=vertical.replace('precise float variance=sigma*sigma','precise float sigma=parameters[0];precise float variance=sigma*sigma')
            suffix=('_m3' if m3_prepare else '_exact' if exact_divisions else '')+('_gpu_stats' if gpu_stats else '')
            self.run('horizontal'+suffix,horizontal,bottom-top+7,w,h,{0:src,2:stats},local=32,startRow=top-3)
            self.run('vertical'+suffix,vertical,w,w,h,{0:src,1:out,2:stats,3:carry,**bindings},top=top,bottom=bottom,finish=int(finish),sigma=sigma)

    def scene_buffer(self,src,out,w,h,lut,shade):
        packed=np.zeros((17,17,17,4),np.uint8);packed[...,:3]=lut
        table=self.buffer('lut',packed.nbytes);table.write(memoryview(packed))
        self.run('scene',SCENE,w*h,w,h,{0:src,1:out,2:table},shading=tuple(float(x) for x in shade))

    def texture_buffer(self,reference,src,out,w,h,strength=1,original=None):
        noise=0.
        gpu_stats=os.environ.get('CAMERALOOK_CPU_GPU_STATS')!='1'
        parameters=self.buffer('parameters',8) if gpu_stats else None
        if gpu_stats:parameters.write(b'\0\0\0\0',offset=4)
        if w>=5 and h>=5:
            step=max(1,int(math.sqrt(w*h/16000)))
            nx=(w-3)//step+1;ny=(h-3)//step+1;n=nx*ny
            samples=self.buffer('samples',n*4)
            self.run('texture_noise',TEXTURE_NOISE,n,w,h,{0:src,2:samples,4:reference},stepSize=step,samplesX=nx)
            if gpu_stats:self.run('noise_quantile',NOISE_GPU,256,w,h,{2:samples,6:parameters},sampleCount=n)
            else:
                values=np.frombuffer(samples.read(size=n*4),np.float32)
                noise=float(np.partition(values,n//5)[n//5]/np.float32(1.133))
        source=TEXTURE
        if gpu_stats:
            source=source.replace('uniform float noise,strength;','uniform float strength;layout(std430,binding=6) readonly buffer Parameters {float parameters[];};')
            source=source.replace('void main(){','void main(){float noise=parameters[1];')
        self.run('texture_gpu_stats' if gpu_stats else 'texture',source,w*h,w,h,
                 {0:src,1:out,4:reference,5:original or reference,**({6:parameters} if gpu_stats else {})},noise=noise,strength=float(strength))

    def denoise(self,rgb,finish=False,cancelled=None,*,m3_prepare=False,exact_divisions=False):
        if cancelled and cancelled():raise Cancelled()
        h,w=rgb.shape[:2];src=self.upload('input',rgb);out=self.buffer('work_a',w*h*4)
        self.denoise_buffer(src,out,w,h,finish,cancelled,m3_prepare=m3_prepare,exact_divisions=exact_divisions)
        if cancelled and cancelled():raise Cancelled()
        result=self.read(out,w,h);self.last_report={'gpu_seconds':self.collect_queries()};return result

    def prepare(self,rgb,cancelled=None):
        if cancelled and cancelled():raise Cancelled()
        h,w=rgb.shape[:2];src=self.upload('original',rgb);out=self.buffer('work_a',w*h*4)
        self.denoise_buffer(src,out,w,h,False,cancelled)
        reference=self.buffer('reference',w*h*4)
        self.ctx.copy_buffer(reference,out,size=w*h*4)
        self.prepared_shape=(h,w)
        result=self.read(out,w,h);self.last_report={'gpu_seconds':self.collect_queries()};return result

    def scene(self,rgb,lut,shade):
        h,w=rgb.shape[:2];src=self.upload('input',rgb);out=self.buffer('work_a',w*h*4)
        self.scene_buffer(src,out,w,h,lut,shade);return self.read(out,w,h)

    def texture(self,reference,processed):
        h,w=reference.shape[:2];ref=self.upload('reference',reference);src=self.upload('input',processed)
        out=self.buffer('work_a',w*h*4);self.texture_buffer(ref,src,out,w,h)
        return self.read(out,w,h)

    def finish(self,result,prepared,original,lut,shade,strength,cancelled=None,reuse_prepared=False):
        times={};start=time.perf_counter()
        def mark(name):
            nonlocal start
            now=time.perf_counter();times[name]=round(now-start,4);start=now
        h,w=result.shape[:2];src=self.upload('input',result)
        reusable=reuse_prepared and getattr(self,'prepared_shape',None)==(h,w)
        ref=self.buffers['reference'] if reusable else self.upload('reference',prepared)
        orig=(self.buffers['original'] if reusable else self.upload('original',original)) if strength!=1 else ref
        a=self.buffer('work_a',w*h*4);b=self.buffer('work_b',w*h*4)
        mark('upload')
        if cancelled and cancelled():raise Cancelled()
        self.scene_buffer(src,a,w,h,lut,shade);mark('scene_dispatch')
        self.denoise_buffer(a,b,w,h,True,cancelled);mark('denoise')
        self.texture_buffer(ref,b,a,w,h,strength,orig);mark('texture_blend_dispatch')
        if cancelled and cancelled():raise Cancelled()
        out=self.read(a,w,h);mark('readback')
        self.last_report={'stages':times,'gpu_seconds':self.collect_queries(),
            'timing_scope':'stages are CPU submission/waits; gpu_seconds are elapsed queries collected after final readback',
            'statistics_backend':'GPU' if os.environ.get('CAMERALOOK_CPU_GPU_STATS')!='1' else 'CPU reference',
            'retained_megabytes':round(sum(x.size for x in self.buffers.values())/1024**2,1)}
        return out

    def close(self):
        for b in self.buffers.values():b.release()
        for p in self.programs.values():p.release()
        self.buffers.clear();self.programs.clear()
        self.host_read=None;self.queries.clear()
