/* Desktop implementations of the recovered Leica image math.
 * No fast-math: rounding and operation order are part of the image pipeline.
 * Reference: research/native_denoise.c (original libleicadenoise.so).
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "native_threads.h"
#ifdef _WIN32
#define API __declspec(dllexport)
#else
#define API __attribute__((visibility("default")))
#endif
#ifdef CAMERALOOK_M3_PROBE
static int core_probe_x=-1,core_probe_y=-1;
static float *core_probe_output;
#endif
static int clampi(int v,int hi) { return v<0?0:(v>hi?hi:v); }
static float lum(const uint8_t *p) {
    return fmaf((float)p[2],.0722f,fmaf((float)p[0],.2126f,(float)p[1]*.7152f));
}
static uint8_t byte(float x) { return (uint8_t)clampi((int)(x+.5f),255); }
static float sigma(const uint8_t *p,int w,int h) {
    unsigned hist[256]={0},count=0;
    int step=(int64_t)w*h>16000000?8:4;
    for(int y=1;y<h-2;y+=step) for(int x=1;x<w-2;x+=step) {
        const uint8_t *a=p+((size_t)y*w+x)*3;
        float aa=lum(a);
        if(aa<8.f || aa>246.f)continue;
        float ab=lum(a+3),ba=lum(a+(size_t)w*3),bb=lum(a+((size_t)w+1)*3);
        if(fabsf(aa-ab)>12.f || fabsf(aa-ba)>12.f || fabsf(bb-ab)>12.f || fabsf(bb-ba)>12.f)continue;
        int bin=clampi((int)fmaf(fabsf(((aa-ab)-ba)+bb),2.f,.5f),255);
        hist[bin]++;count++;
    }
    if(count<32)return 1.f;
    unsigned total=0;int mid=0;
    for(;mid<255;mid++){total+=hist[mid];if(total>=(count+1)/2)break;}
    return fmaxf(.7f,fminf(7.f,(float)mid/2.698f));
}
static void horizontal(const uint8_t *p,int w,int h,int y,float *out) {
    const uint8_t *row=p+(size_t)clampi(y,h-1)*w*3;
    float a[7],u[7],v[7],sy=0,su=0,sv=0,yy=0,uu=0,vv=0;
    for(int j=0;j<7;j++) {
        const uint8_t *q=row+clampi(j-3,w-1)*3;
        a[j]=lum(q);u[j]=(float)q[0]-a[j];v[j]=(float)q[2]-a[j];
        sy+=a[j];yy=fmaf(a[j],a[j],yy);
        uu=fmaf(u[j],u[j],uu);vv=fmaf(v[j],v[j],vv);
    }
    /* The disassembler shows four left-edge copies accumulated first.
     * Ghidra's flattened expression misleadingly appears reversed. */
#ifdef CAMERALOOK_M3_EXACT_PREPARE
    for(int j=0;j<7;j++){su+=u[j];sv+=v[j];}
#else
    for(int j=6;j>=0;j--){su+=u[j];sv+=v[j];}
#endif
    for(int x=0;x<w;x++) {
        out[x*6]=sy;out[x*6+1]=yy;out[x*6+2]=su;
        out[x*6+3]=uu;out[x*6+4]=sv;out[x*6+5]=vv;
        const uint8_t *old=row+clampi(x-3,w-1)*3,*next=row+clampi(x+4,w-1)*3;
        float ay=lum(old),by=lum(next),au=(float)old[0]-ay,bu=(float)next[0]-by;
        float av=(float)old[2]-ay,bv=(float)next[2]-by;
        sy+=by-ay;yy+=fmaf(by,by,-(ay*ay));
        su+=bu-au;sv=(bv-av)+sv;
        uu=fmaf(bu,bu,-(au*au))+uu;vv=fmaf(bv,bv,-(av*av))+vv;
    }
}
/* Row streaming preserves the original in-place boundary behaviour and uses
 * O(width) scratch space, not six full-resolution float images.
 * The ring update is fused: `sum - slot` (the rounding of the removal) and
 * `slot + that` (the rounding of the insertion) are the same two float
 * operations as the two separate passes, so folding them into one pass that
 * also refills the slot changes no bit and touches each array once. */
API int cl_denoise(uint8_t *rgb,int w,int h,int finish) {
    if(!rgb || w<2 || h<2 || w>16384 || h>16384)return 0;
    size_t n=(size_t)w*6;
    float *ring=malloc(n*7*sizeof(float)),*sum=calloc(n,sizeof(float));
    if(!ring || !sum){free(ring);free(sum);return 0;}
    float s=sigma(rgb,w,h);s=s*s;
    float ny=(finish?1.f:2.4f)*s,nc=(finish?2.f:4.f)*s;
    float ky=(finish?.4f:.88f)*ny,kc=(finish?.65f:.95f)*nc;
    float edge=fmaf(s,9.f,4.f);
    for(int j=0;j<7;j++) {
        float *slot=ring+n*j;horizontal(rgb,w,h,j-3,slot);
        for(size_t i=0;i<n;i++)sum[i]=slot[i]+sum[i];
    }
    int vector_end=w>8?w-(w%8?w%8:8):0;
    {
        for(int y=0;y<h;y++) {
        for(int x=0;x<w;x++) {
            uint8_t *p=rgb+((size_t)y*w+x)*3;float *m=sum+x*6;
            float my=m[0]/49.f,mu=m[2]/49.f,mv=m[4]/49.f;
#ifdef CAMERALOOK_M3_EXACT_PREPARE
            /* NEON FMLS/FMLA in the original prepare path. Rounding the
             * multiply separately changes guard decisions at rare pixels. */
            float vy=fmaxf(0.f,fmaf(-my,my,m[1]/49.f));
            float vu=fmaxf(0.f,fmaf(-mu,mu,m[3]/49.f));
            float vv=fmaxf(0.f,fmaf(-mv,mv,m[5]/49.f));
            float yy=lum(p),u=(float)p[0]-yy,v=(float)p[2]-yy;
            float d=yy-my,e=1.f/(d*d/edge+1.f);
            float outy=fmaf(my-yy,(ky/(ny+vy))*e,yy);
            float outu=fmaf(mu-u,(kc/(nc+vu))*e,u);
            float outv=fmaf(mv-v,(kc/(nc+vv))*e,v);
            float r=outy+outu,b=outy+outv;
            float g=fmaf(b,-.0722f,fmaf(r,-.2126f,outy))/.7152f;
#ifdef CAMERALOOK_M3_PROBE
            if(x==core_probe_x && y==core_probe_y){
                float values[]={my,mu,mv,vy,vu,vv,yy,u,v,e,outy,outu,outv,r,g,b,s,ny,nc,ky,kc,edge};
                memcpy(core_probe_output,m,6*sizeof(float));memcpy(core_probe_output+6,values,sizeof(values));
            }
#endif
            p[0]=byte(r);p[1]=byte(g);p[2]=byte(b);
#else
            float vy=fmaxf(0.f,m[1]/49.f-my*my),vu=fmaxf(0.f,m[3]/49.f-mu*mu),vv=fmaxf(0.f,m[5]/49.f-mv*mv);
            if(x>=vector_end)vu=fmaxf(0.f,fmaf(-mu,mu,m[3]/49.f));
            float yy=x<vector_end?((float)p[1]*.7152f+(float)p[0]*.2126f)+(float)p[2]*.0722f:lum(p);
            float u=(float)p[0]-yy,v=(float)p[2]-yy;
            float d=yy-my,e=1.f/(d*d/edge+1.f);
            float outy=yy+(my-yy)*(ky/(ny+vy))*e;
            float ku=(kc/(nc+vu))*e,kv=(kc/(nc+vv))*e;
            float outv=(outy+v)+((mv-v)*(kc/(nc+vv)))*e;
            float r=x<vector_end?(outy+u)+((mu-u)*(kc/(nc+vu)))*e:outy+fmaf(ku,mu-u,u);
            float g=x<vector_end?((outy+r*-.2126f)+outv*-.0722f)/.7152f:fmaf(outv,-.0722f,fmaf(r,-.2126f,outy))/.7152f;
            p[0]=byte(r);p[1]=byte(g);p[2]=byte(outv);
#endif
        }
        if(y+1<h) {
            /* Horizontal row y+4 folded into the ring update: same running
             * sums, same order, but the 6 floats never touch a scratch row. */
            float *slot=ring+n*(y%7);
            int target=y+4<h?y+4:h-1;
            const uint8_t *row=rgb+(size_t)target*w*3;
            float a[7],u[7],v[7],sy=0,su=0,sv=0,yy=0,uu=0,vv=0;
            for(int j=0;j<7;j++) {
                const uint8_t *q=row+clampi(j-3,w-1)*3;
                a[j]=lum(q);u[j]=(float)q[0]-a[j];v[j]=(float)q[2]-a[j];
                sy+=a[j];yy=fmaf(a[j],a[j],yy);
                uu=fmaf(u[j],u[j],uu);vv=fmaf(v[j],v[j],vv);
            }
#ifdef CAMERALOOK_M3_EXACT_PREPARE
            for(int j=0;j<7;j++){su+=u[j];sv+=v[j];}
#else
            for(int j=6;j>=0;j--){su+=u[j];sv+=v[j];}
#endif
#define FUSE(c,val) do { float *p6=slot+x*6; float *ps=sum+x*6; \
    float _r=ps[c]-p6[c]; p6[c]=(val); ps[c]=(val)+_r; } while(0)
            for(int x=0;x<w;x++) {
                FUSE(0,sy);FUSE(1,yy);FUSE(2,su);
                FUSE(3,uu);FUSE(4,sv);FUSE(5,vv);
                const uint8_t *old=row+clampi(x-3,w-1)*3,*nextp=row+clampi(x+4,w-1)*3;
                float ay=lum(old),by=lum(nextp),au=(float)old[0]-ay,bu=(float)nextp[0]-by;
                float av=(float)old[2]-ay,bv=(float)nextp[2]-by;
                sy+=by-ay;yy+=fmaf(by,by,-(ay*ay));
                su+=bu-au;sv=(bv-av)+sv;
                uu=fmaf(bu,bu,-(au*au))+uu;vv=fmaf(bv,bv,-(av*av))+vv;
            }
#undef FUSE
        }
        }
    }
    free(ring);free(sum);return 1;
}

static float sat(float x) { return fminf(1.f,fmaxf(0.f,x)); }
/* Exact trilinear order, coordinate convention, and hash constant from
 * leica_params.pixels. Double-precision sin matches the reference path. */
API void cl_scene(const uint8_t *rgb,uint8_t *dst,int w,int h,int top,int bottom,
                  const uint8_t *lut,const float *s) {
    union { uint32_t u;float f; } multiplier={.u=0x472aee8c};
    for(int y=top;y<bottom;y++)for(int x=0;x<w;x++) {
        size_t pos=((size_t)y*w+x)*3;
        int b[3];float f[3],out[3]={0};
        for(int c=0;c<3;c++) {
            float v=((float)rgb[pos+c]/255.f)*16.f;
            b[c]=(int)v;if(b[c]>15)b[c]=15;f[c]=v-(float)b[c];
        }
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++) {
            float weight=((i?f[0]:1.f-f[0])*(j?f[1]:1.f-f[1]))*(k?f[2]:1.f-f[2]);
            int offset=(((b[0]+i)*17+b[1]+j)*17+b[2]+k)*3;
            for(int c=0;c<3;c++)out[c]+=(weight*(float)lut[offset+2-c])/255.f;
        }
        float xx=((((((float)x+.5f)/(float)w)-.5f)*(float)w)/(float)h+.5f)-.5f;
        float yy=((float)y+.5f)/(float)h-.5f;
        float angle=(yy-.5f)*78.233f+(xx-.5f)*12.9898f;
        float n=(float)sin((double)angle)*multiplier.f;
        float radial=sat(((sqrtf(yy*yy+xx*xx)+((n-floorf(n))*.04f)*s[2])-s[0])/(s[1]-s[0]));
        float lum=(out[0]*.499f+out[1]*.387f)+out[2]*.114f;
        float gain=s[7]+s[6]/(expf(s[4]*(s[5]-lum))+1.f);
        float delta=((out[0]*.299f+out[1]*.587f)+out[2]*.114f)*
                    (s[3]*(gain+((radial*radial)*(3.f-(radial+radial)))*(1.f-gain))-1.f);
        for(int c=0;c<3;c++)dst[pos+c]=(uint8_t)nearbyintf(sat(out[c]+delta)*255.f);
    }
}

/* libfullm9 uses separate mul/add instructions, unlike DenoiseFlow's FMA. */
static float plain_lum(const uint8_t *p) {
    return ((float)p[0]*.2126f+(float)p[1]*.7152f)+(float)p[2]*.0722f;
}
static int cmp_float(const void *a,const void *b) {
    float x=*(const float *)a,y=*(const float *)b;return (x>y)-(x<y);
}
static float at(const float *a,int w,int h,int x,int y) {
    return a[(size_t)clampi(y,h-1)*w+clampi(x,w-1)];
}
static float blur3(const float *a,int w,int h,int x,int y) {
    float v=at(a,w,h,x-1,y-1)*.0625f+0.f;
    v+=at(a,w,h,x,y-1)*.125f;v+=at(a,w,h,x+1,y-1)*.0625f;
    v+=at(a,w,h,x-1,y)*.125f;v+=at(a,w,h,x,y)*.25f;
    v+=at(a,w,h,x+1,y)*.125f;v+=at(a,w,h,x-1,y+1)*.0625f;
    v+=at(a,w,h,x,y+1)*.125f;v+=at(a,w,h,x+1,y+1)*.0625f;return v;
}
API int cl_texture(const uint8_t *src,uint8_t *dst,int w,int h) {
    if(w<5 || h<5)return 1;
    size_t n=(size_t)w*h;
    float *a=malloc(n*sizeof(float)),*b=malloc(n*sizeof(float));
    int step=(int)sqrt((double)n/16000.);if(step<2)step=1;
    size_t max_samples=((size_t)(w-2)+step-1)/step*((h-2+step-1)/step);
    float *samples=malloc(max_samples*sizeof(float));
    if(!a || !b || !samples){free(a);free(b);free(samples);return 0;}
    for(size_t i=0;i<n;i++){a[i]=plain_lum(src+i*3);b[i]=plain_lum(dst+i*3);}
    size_t count=0;
    for(int y=1;y<h-1;y+=step)for(int x=1;x<w-1;x+=step) {
        uint32_t hash=(uint32_t)y*0x9e3779b1u+(uint32_t)x*0x85ebca77u;
        hash=(hash^(hash>>13))*0xc2b2ae3du;
        int xx=clampi(x+(int)(hash%(uint32_t)step),w-2),yy=clampi(y+(int)((hash>>16)%(uint32_t)step),h-2);
        samples[count++]=fabsf((((at(a,w,h,xx,yy)*4.f-at(a,w,h,xx-1,yy))-at(a,w,h,xx+1,yy))-at(a,w,h,xx,yy-1))-at(a,w,h,xx,yy+1));
    }
    qsort(samples,count,sizeof(float),cmp_float);
    float noise=samples[count/5]/1.133f;
    free(samples);
    for(int y=0;y<h;y++)for(int x=0;x<w;x++) {
        float center=at(a,w,h,x,y),smooth=blur3(a,w,h,x,y),detail=center-smooth;
        if(!(noise*.8f+.75f<fabsf(detail)))continue;
        float target_smooth=blur3(b,w,h,x,y),target_detail=at(b,w,h,x,y)-target_smooth;
        float gain=fmaxf(.5f,fminf(1.5f,(target_smooth*(255.f-target_smooth))/fmaxf(64.f,smooth*(255.f-smooth))));
        float wanted=gain*detail;
        if(!(fabsf(target_detail)+.5f<fabsf(wanted) && wanted*target_detail>=-.25f))continue;
        float dx[9],dy[9];int j=0;
        for(int yy=y-1;yy<=y+1;yy++)for(int xx=x-1;xx<=x+1;xx++) {
            dx[j]=at(a,w,h,xx+1,yy)-at(a,w,h,xx-1,yy);
            dy[j]=at(a,w,h,xx,yy+1)-at(a,w,h,xx,yy-1);j++;
        }
        float ex=dx[0]*dx[0],ey=dy[0]*dy[0],cross=dx[0]*dy[0]+0.f;
        for(int j=1;j<9;j++){ex+=dx[j]*dx[j];ey+=dy[j]*dy[j];cross+=dx[j]*dy[j];}
        float d=ex-ey;
        float coherence=sat((sqrtf(d*d+cross*cross*4.f)/((noise*noise)*36.f+(ex+ey)+1.f)-.35f)/.4f);
        float headroom=sat(fminf(target_smooth*.0625f,(255.f-target_smooth)*.0625f));
        float smooth_coherence=(coherence*coherence)*(3.f-(coherence+coherence));
        float delta=headroom*(fmaxf(-12.f,fminf(wanted-target_detail,12.f))*smooth_coherence);
        uint8_t *p=dst+((size_t)y*w+x)*3;
        int lo=p[0]<p[1]?p[0]:p[1];if(p[2]<lo)lo=p[2];
        int hi=p[0]>p[1]?p[0]:p[1];if(p[2]>hi)hi=p[2];
        delta=fmaxf((float)-lo,fminf((float)(255-hi),delta));
        for(int c=0;c<3;c++)p[c]=(uint8_t)clampi((int)nearbyintf((float)p[c]+delta),255);
    }
    free(a);free(b);return 1;
}

static float fourth(float x) { return ((x*x)*x)*x; }
API int cl_output_denoise(const uint8_t *src,uint8_t *dst,int w,int h,int style) {
    if(w<3 || h<3 || style<1 || style>8)return 1;
    int step=(int)sqrt(((double)w*h)/16000.);if(step<2)step=1;
    size_t max_samples=((size_t)(w-2)+step-1)/step*((h-2+step-1)/step);
    float *samples=malloc(max_samples*3*sizeof(float));if(!samples)return 0;
    size_t count=0;
    for(int y=1;y<h-1;y+=step)for(int x=1;x<w-1;x+=step) {
        const uint8_t *p=src+((size_t)y*w+x)*3;
        float lap=(((plain_lum(p)*4.f-plain_lum(p-3))-plain_lum(p+3))-plain_lum(p-(size_t)w*3))-plain_lum(p+(size_t)w*3);
        samples[count]=fabsf(lap);
        samples[max_samples+count]=fabsf((float)((int)p[0]*4-((int)p[-3]+p[3]+p[-w*3]+p[w*3]))-lap);
        samples[2*max_samples+count]=fabsf((float)((int)p[2]*4-((int)p[-1]+p[5]+p[2-w*3]+p[2+w*3]))-lap);
        count++;
    }
    float noise[3],alpha[3];
    for(int c=0;c<3;c++) {
        qsort(samples+c*max_samples,count,sizeof(float),cmp_float);
        noise[c]=fminf(samples[c*max_samples+count/2]/3.016f,12.f);
        alpha[c]=fminf(fmaxf((noise[c]-1.25f)/5.f,0.f)*(c? .6f:.42f),c?.6f:.42f);
    }
    free(samples);
    if((style&13)==4 || (style&11)==1)alpha[0]=0.f;
    if(alpha[0]==0.f && alpha[1]==0.f && alpha[2]==0.f)return 1;
    float range[3];for(int c=0;c<3;c++)range[c]=fmaxf(noise[c]*2.5f,2.f);
    for(int y=0;y<h;y++)for(int x=0;x<w;x++) {
        const uint8_t *p=src+((size_t)y*w+x)*3;
        float yy=plain_lum(p),u=(float)p[0]-yy,v=(float)p[2]-yy;
        float sy=0,su=0,sv=0,wy=0,wu=0,wv=0;
        for(int j=-1;j<=1;j++) {
            float vals[3][3],weights[3][3];
            for(int i=-1;i<=1;i++) {
                const uint8_t *q=src+((size_t)clampi(y+j,h-1)*w+clampi(x+i,w-1))*3;
                float qy=plain_lum(q),qu=(float)q[0]-qy,qv=(float)q[2]-qy;
                float weight=(j==0?2.f:1.f)*(i==0?2.f:1.f)/(fourth((qy-yy)/range[0])+1.f);
                int k=i+1;vals[k][0]=qy;vals[k][1]=qu;vals[k][2]=qv;
                weights[k][0]=weight;weights[k][1]=weight/(fourth((qu-u)/range[1])+1.f);weights[k][2]=weight/(fourth((qv-v)/range[2])+1.f);
            }
            sy=((sy+vals[0][0]*weights[0][0])+vals[1][0]*weights[1][0])+vals[2][0]*weights[2][0];
            su=((su+vals[0][1]*weights[0][1])+vals[1][1]*weights[1][1])+vals[2][1]*weights[2][1];
            sv=((sv+vals[0][2]*weights[0][2])+vals[1][2]*weights[1][2])+vals[2][2]*weights[2][2];
            wy=((wy+weights[0][0])+weights[1][0])+weights[2][0];
            wu=((wu+weights[0][1])+weights[1][1])+weights[2][1];
            wv=((wv+weights[0][2])+weights[1][2])+weights[2][2];
        }
        float dy=fmaxf(-4.f,fminf(4.f,alpha[0]*(sy/wy-yy)));
        float du=fmaxf(-8.f,fminf(8.f,alpha[1]*(su/wu-u)));
        float dv=fmaxf(-8.f,fminf(8.f,alpha[2]*(sv/wv-v)));
        float head=sat(fminf(yy*.125f,(255.f-yy)*.125f));
        float r=head*(du+dy)+(float)p[0];
        float g=head*(dy+(dv*.0722f+du*.2126f)/-.7152f)+(float)p[1];
        float b=head*(dv+dy)+(float)p[2];
        uint8_t *q=dst+((size_t)y*w+x)*3;
        q[0]=(uint8_t)clampi((int)nearbyintf(r),255);q[1]=(uint8_t)clampi((int)nearbyintf(g),255);q[2]=(uint8_t)clampi((int)nearbyintf(b),255);
    }
    return 1;
}
