/* Native desktop implementation of the exact M3 configuration in the APK.
 * The original M3 resource disables the colour LUT/colour corrections and
 * fixes exposure=-1, shading seed=0, lux=200, CCT=5500, zoom=1.
 * The dormant branches for other filters are not part of this entry point.
 */
#define cl_denoise cl_m3_prepare
#define CAMERALOOK_M3_EXACT_PREPARE 1
#include "native_post.c"
#undef cl_denoise
#include "m3_core_math.h"

API int cl_m3_core_version(void){return 1;}

API void cl_m3_math(const float *in,float *s,float *e,int n) {
    for(int i=0;i<n;i++){s[i]=core_sinf(in[i]);e[i]=core_expf(in[i]);}
}
#ifdef CAMERALOOK_M3_PROBE
API void cl_m3_horizontal_probe(const uint8_t *src,int w,int h,int y,float *out){horizontal(src,w,h,y,out);}
API int cl_m3_prepare_probe(uint8_t *src,int w,int h,int x,int y,float *out) {
    core_probe_x=x;core_probe_y=y;core_probe_output=out;
    int result=cl_m3_prepare(src,w,h,0);core_probe_x=-1;return result;
}
#endif

API int cl_m3_base(const uint8_t *src,uint8_t *dst,int w,int h,int top,int bottom,const float *shade) {
    if(!src||!dst||!shade||w<1||h<1||w>32768||h>32768||top<0||bottom>h||top>bottom)return 0;
    union{uint32_t u;float f;} hash={.u=0x472aee8c};
    for(int y=top;y<bottom;y++) {
        float ny=((float)y+.5f)/(float)h-.5f;
        for(int x=0;x<w;x++) {
            float nx=fmaf((float)w,-.5f,(float)x+.5f)/(float)h;
            float angle=fmaf(12.9898f,nx-.5f,(ny-.5f)*78.233f);
            float v=core_sinf(angle)*hash.f;
            float noise=v-floorf(v);
            float sum=noise+0.f;
            for(int j=1;j<6;j++)sum+=noise;
            float radius=sqrtf(fmaf(nx,nx,ny*ny));
            float radial=(fmaf((sum/6.f)*.04f,shade[2],radius)-shade[0])/(shade[1]-shade[0]);
            radial=fmaxf(0.f,fminf(1.f,radial));
            float smooth=(radial*radial)*fmaf(radial,-2.f,3.f);
            size_t pos=((size_t)y*w+x)*3;
            float r=(float)src[pos]/255.f,g=(float)src[pos+1]/255.f,b=(float)src[pos+2]/255.f;
            float lum=fmaf(b,.114f,fmaf(r,.499f,g*.387f));
            float gain=shade[7]+shade[6]/(core_expf(shade[4]*(shade[5]-lum))+1.f);
            float delta=fmaf(fmaf(1.f-gain,smooth,gain),shade[3],-1.f)*fmaf(b,.114f,fmaf(r,.299f,g*.587f));
            delta*=255.f;
            for(int c=0;c<3;c++) {
                float value=roundf((float)src[pos+c]+delta);
                dst[pos+c]=(uint8_t)fmaxf(0.f,fminf(255.f,value));
            }
        }
    }
    return 1;
}
