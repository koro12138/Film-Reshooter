/* Desktop implementations of the recovered Leica image math. */
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "native_threads.h"
#ifdef _WIN32
#define API __declspec(dllexport)
#else
#define API __attribute__((visibility("default")))
#endif

#define HDR_R 0.2126
#define HDR_G 0.7152
#define HDR_B 0.0722

API int cl_hdr_version(void) { return 1; }

/* IEEE binary32 -> binary16, round-to-nearest ties-even, independent of F16C.
 * Table entries are supplied by NumPy's original sRGB function, not powf. */
static uint16_t hdr_half(float value) {
    uint32_t bits;memcpy(&bits,&value,4);
    uint32_t sign=(bits>>16)&0x8000u,a=bits&0x7fffffffu;
    if(a>=0x7f800000u){uint32_t m=(a&0x7fffffu)>>13;return (uint16_t)(sign|0x7c00u|(a>0x7f800000u?(m?m:0x200u):0u));}
    if(a<0x38800000u){
        uint32_t e=a>>23;if(e<102u)return (uint16_t)sign;
        uint32_t m=(a&0x7fffffu)|0x800000u,shift=126u-e;
        uint32_t q=m>>shift,remainder=m&((1u<<shift)-1u),half=1u<<(shift-1u);
        q+=(remainder>half||(remainder==half&&(q&1u)));
        return (uint16_t)(sign|q);
    }
    if(a>=0x47800000u)return (uint16_t)(sign|0x7c00u);
    uint32_t rounded=a+0xfffu+((a>>13)&1u);
    return (uint16_t)(sign|((rounded-0x38000000u)>>13));
}

typedef struct {const uint8_t *src;const float *gain,*table;uint16_t *out;int width,step;} HdrPack;
static void hdr_pack_rows(void *arg,int top,int bottom){
    HdrPack *p=arg;size_t begin=(size_t)top*p->width,end=(size_t)bottom*p->width;
    for(size_t i=begin;i<end;i++){
        for(int c=0;c<3;c++){
            float product=p->table[p->src[i*p->step+c]]*p->gain[i];
            p->out[i*4+c]=hdr_half(product);
        }
        p->out[i*4+3]=0x3c00u;
    }
}

API int cl_hdr_pack_u8(const uint8_t *src,const float *gain,const float *linear_table,
                       int width,int height,int step,uint16_t *out){
    if(!src||!gain||!linear_table||!out||width<1||height<1||(step!=3&&step!=4))return 0;
    HdrPack job={src,gain,linear_table,out,width,step};
    if((size_t)width*height>=262144)cl_run_rows(hdr_pack_rows,&job,height);
    else hdr_pack_rows(&job,0,height);
    return 1;
}

/* Exact area-weighted (fractional box) Rec.709 luma downscale used by
 * NativeM9.hdrSample.  `step` is 3 for RGB and 4 for RGBA source pixels.
 * Mirrors the ARM routine bit for bit: double precision, same accumulation
 * order, float cast before frinti (nearest, ties to even), then clamp 0..255.
 * Returns 0 for inputs the original routine rejects (out of 1..384 range or
 * source smaller than the requested sample), so callers keep their fallback.
 */
API int cl_hdr_sample(const uint8_t *pixels, int width, int height, int stride,
                      int step, int outW, int outH, uint8_t *dst) {
    if (!pixels || !dst || width <= 0 || height <= 0 || stride <= 0) return 0;
    if (step != 3 && step != 4) return 0;
    if (outW <= 0 || outH <= 0 || outW > 384 || outH > 384) return 0;
    if (width < outW || height < outH) return 0;

    const double sx = (double)width / (double)outW;
    const double sy = (double)height / (double)outH;

    for (int oy = 0; oy < outH; ++oy) {
        const double y1 = sy * (double)(oy + 1);
        const double y0 = sy * (double)oy;
        const int ys = (int)y0;             /* fcvtzs: truncate toward zero */
        int ye = (int)ceil(y1);             /* fcvtps: ceil toward +inf */
        if (ye > height) ye = height;
        uint8_t *row = dst + (size_t)oy * (size_t)outW;
        for (int ox = 0; ox < outW; ++ox) {
            const double x1 = sx * (double)(ox + 1);
            const double x0 = sx * (double)ox;
            const int xs = (int)x0;
            int xe = (int)ceil(x1);
            if (xe > width) xe = width;
            double wsum = 0.0, vsum = 0.0;
            for (int y = ys; y < ye; ++y) {
                const double yw = fmin((double)y + 1.0, y1) - fmax((double)y, y0);
                const uint8_t *p = pixels + (size_t)y * (size_t)stride + (size_t)xs * (size_t)step;
                for (int x = xs; x < xe; ++x, p += step) {
                    const double xw = fmin((double)x + 1.0, x1) - fmax((double)x, x0);
                    const double w = yw * xw;
                    const double luma = ((double)p[0] * HDR_R + (double)p[1] * HDR_G) +
                                        (double)p[2] * HDR_B;
                    wsum += w;
                    vsum += w * luma;
                }
            }
            const double v = vsum / wsum;       /* NaN when the box is empty */
            const float f = (float)v;
            if (!(fabsf(f) < INFINITY)) { row[ox] = 0; continue; }
            float r = nearbyintf(f);            /* frinti: nearest, ties to even */
            if (r > 255.0f) r = 255.0f;
            if (r < 0.0f) r = 0.0f;
            row[ox] = (uint8_t)(int)r;
        }
    }
    return 1;
}

/* Highlight shoulder from the APK's NightHighlights routine.
 *
 * `hdr.protect` measured 677 ms on a 24 MP night frame because it promotes the
 * whole picture to float32 (three 96 MB temporaries). The shoulder only depends
 * on the per-pixel peak, which for 8-bit input has 256 possible values, so the
 * gain can be tabulated and the per-pixel work stays in float32 exactly as the
 * Python reference does it: s = c/255, r = s*gain, dst = floor(clip(r,0,1)*255+.5).
 * Bit-identical by construction; callers verify with max-abs-diff.
 */
API int cl_hdr_protect(const uint8_t *src, uint8_t *dst, int width, int height, int stride) {
    if (!src || !dst || width <= 0 || height <= 0 || stride < width * 3) return 0;

    float gain[256];
    for (int k = 0; k < 256; ++k) {
        const float peak = (float)k / 255.0f;
        float shoulder = peak;
        if (peak > 0.72f) {
            const float t = (peak - 0.72f) / 0.28f;
            shoulder = 0.72f + 0.28f * t / (1.0f + 0.32f * t);
        }
        gain[k] = peak > 0.0f ? shoulder / peak : 1.0f;
        if (!isfinite(gain[k])) gain[k] = 1.0f;
    }

    for (int y = 0; y < height; ++y) {
        const uint8_t *s = src + (size_t)y * (size_t)stride;
        uint8_t *d = dst + (size_t)y * (size_t)width * 3;
        for (int x = 0; x < width; ++x) {
            const uint8_t r8 = s[0], g8 = s[1], b8 = s[2];
            uint8_t peak8 = r8;
            if (g8 > peak8) peak8 = g8;
            if (b8 > peak8) peak8 = b8;
            const float k = gain[peak8];
            for (int c = 0; c < 3; ++c) {
                float v = ((float)s[c] / 255.0f) * k;
                if (!(v > 0.0f)) v = 0.0f;          /* also catches NaN */
                if (v > 1.0f) v = 1.0f;
                const float scaled = v * 255.0f + 0.5f;
                int out = (int)floorf(scaled);
                if (out > 255) out = 255;
                d[c] = (uint8_t)out;
            }
            s += 3;
            d += 3;
        }
    }
    return 1;
}
