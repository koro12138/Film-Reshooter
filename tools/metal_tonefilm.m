/* Metal backend for CameraLook's LUT tone + film stages.
 *
 * Mirrors engine.tone_cpu / engine.film_cpu exactly (same operation order, same
 * tetrahedral interpolation, same separable [1 2 1] blur, same grain hash).
 * The Metal Shading Language source is compiled at runtime with
 * newLibraryWithSource: so the build only needs Command Line Tools, not Xcode's
 * `metal` compiler.
 *
 * Layout: buffers stay in unified memory (MTLResourceStorageModeShared) so no
 * explicit blit is required; the tiling/strip logic of the NumPy path collapses
 * into one whole-image dispatch.
 */
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "metal_tonefilm.h"

static const char *kSource = R"MSL(
#include <metal_stdlib>
using namespace metal;

struct Params {
    int width, height, n, rgb_count, luma_count, seed, y0, out_rows, first, tone_rows;
    int pad0, pad1;
    float strength, clarity, midpoint, vignette, shadows, midtones, highlights;
    float grain, grainSize, roughness, colorVariation;
    float ui_strength;
};

constant float3 LUMA = float3(0.2126f, 0.7152f, 0.0722f);

inline float curveAt(float x, device const float2* pts, int len) {
    float v = clamp(x, 0.0f, 1.0f) * 255.0f;
    float2 prev = pts[0];
    if (v <= prev.x) return prev.y * (1.0f/255.0f);
    for (int j = 1; j < len; ++j) {
        float2 p = pts[j];
        if (v <= p.x) {
            return (prev.y + (p.y - prev.y) * (v - prev.x) / (p.x - prev.x)) * (1.0f/255.0f);
        }
        prev = p;
    }
    return prev.y * (1.0f/255.0f);
}

inline float hashNoise(int2 p, int z) {
    uint v = uint(p.x)*521288629u + uint(p.y)*1597334677u + uint(z)*1821285621u;
    v = (v ^ (v >> 16u)) * 2146121005u;
    v = (v ^ (v >> 15u)) * 2221713035u;
    return float((v ^ (v >> 16u)) & 16777215u) / 8388607.5f - 1.0f;
}

inline float noiseAt(int2 p, int z, float grainSize, float roughness) {
    float scale = max(0.0f, grainSize) / 25.0f + 1.0f;
    float2 f = float2(p) / scale;
    int2 b = int2(f);
    f -= float2(b);
    float s = (hashNoise(b, z)*(1.0f-f.x) + hashNoise(b+int2(1,0), z)*f.x)*(1.0f-f.y)
            + (hashNoise(b+int2(0,1), z)*(1.0f-f.x) + hashNoise(b+int2(1,1), z)*f.x)*f.y;
    float r = clamp(roughness/100.0f, 0.0f, 0.7f);
    return s*(1.0f-r) + hashNoise(p, z+83)*r;
}

inline float3 tonePixel(float3 original, device const float4* lut,
                        device const float2* rgbc, device const float2* lumac,
                        constant Params& P) {
    float3 coord = clamp(original, 0.0f, 1.0f) * float(P.n - 1);
    int3 base = min(int3(coord), int3(P.n - 2));
    float3 f = coord - float3(base);
    int3 s = int3(1, P.n, P.n*P.n);
    if (f.x < f.y) { float t=f.x; f.x=f.y; f.y=t; int a=s.x; s.x=s.y; s.y=a; }
    if (f.y < f.z) { float t=f.y; f.y=f.z; f.z=t; int a=s.y; s.y=s.z; s.z=a; }
    if (f.x < f.y) { float t=f.x; f.x=f.y; f.y=t; int a=s.x; s.x=s.y; s.y=a; }
    int i0 = base.x + base.y*P.n + base.z*P.n*P.n;
    float3 c0 = lut[i0].rgb;
    float3 c1 = lut[i0+s.x].rgb;
    float3 c2 = lut[i0+s.x+s.y].rgb;
    float3 c3 = lut[i0+1+P.n+P.n*P.n].rgb;
    float3 outc = clamp(c0 + (c1-c0)*f.x + (c2-c1)*f.y + (c3-c2)*f.z, 0.0f, 1.0f);

    if (P.rgb_count > 2) {
        outc = float3(curveAt(outc.x, rgbc, P.rgb_count),
                      curveAt(outc.y, rgbc, P.rgb_count),
                      curveAt(outc.z, rgbc, P.rgb_count));
    }
    float lum = dot(outc, LUMA);
    if (P.luma_count > 2) {
        float mapped = curveAt(lum, lumac, P.luma_count);
        outc = lum > 1e-6f ? outc * (mapped/lum) : float3(mapped);
    }
    outc = clamp(outc, 0.0f, 1.0f);

    float3 delta = (clamp(P.strength, 1.0f, 1.8f) - 1.0f) * (outc - original);
    for (int c = 0; c < 3; ++c) {
        float room = delta[c] >= 0.0f ? 1.0f - outc[c] : outc[c];
        outc[c] += room > 0.0f ? delta[c]*room / (room + fabs(delta[c])) : 0.0f;
    }
    return clamp(outc, 0.0f, 1.0f);
}

// ---- pass 1: LUT tone (uint8 in -> uint8 mid) ----
kernel void tone8(device const uchar* src [[buffer(0)]],
                  device       uchar* mid [[buffer(1)]],
                  device const float4* lut [[buffer(2)]],
                  device const float2* rgbc [[buffer(3)]],
                  device const float2* lumac [[buffer(4)]],
                  constant Params& P [[buffer(5)]],
                  uint gid [[thread_position_in_grid]])
{
    int idx = int(gid);
    if (idx >= P.tone_rows * P.width) return;
    int o = idx * 3;                       /* src starts at absolute row P.first */
    int d = idx * 3;
    float3 original = float3(src[o], src[o+1], src[o+2]) * (1.0f/255.0f);
    float3 outc = tonePixel(original, lut, rgbc, lumac, P);
    mid[d]   = uchar(floor(outc.r * 255.0f + 0.5f));
    mid[d+1] = uchar(floor(outc.g * 255.0f + 0.5f));
    mid[d+2] = uchar(floor(outc.b * 255.0f + 0.5f));
}

// ---- pass 1b: LUT tone (float in -> float mid) ----
kernel void tonef(device const float* src [[buffer(0)]],
                  device       float* mid [[buffer(1)]],
                  device const float4* lut [[buffer(2)]],
                  device const float2* rgbc [[buffer(3)]],
                  device const float2* lumac [[buffer(4)]],
                  constant Params& P [[buffer(5)]],
                  uint gid [[thread_position_in_grid]])
{
    int idx = int(gid);
    if (idx >= P.tone_rows * P.width) return;
    int o = idx * 3;                       /* src starts at absolute row P.first */
    float3 original = clamp(float3(src[o], src[o+1], src[o+2]), 0.0f, 1.0f);
    float3 outc = tonePixel(original, lut, rgbc, lumac, P);
    mid[o] = outc.r; mid[o+1] = outc.g; mid[o+2] = outc.b;
}

// ---- pass 2: clarity / vignette / grain / quantize ----
kernel void film8(device const uchar* mid [[buffer(0)]],
                  device const uchar* photo [[buffer(1)]],
                  device       uchar* dst [[buffer(2)]],
                  constant Params& P [[buffer(3)]],
                  uint gid [[thread_position_in_grid]])
{
    int idx = int(gid);
    if (idx >= P.out_rows * P.width) return;
    int x = idx % P.width;
    int row = idx / P.width;                 // 0..out_rows-1 within the output
    int y = P.y0 + row;                      // absolute row
    int w = P.width, h = P.height;
    int last = P.tone_rows - 1;

    int mrow = y - P.first;
    int lo = clamp(mrow - 1, 0, last), md = clamp(mrow, 0, last), hi = clamp(mrow + 1, 0, last);

    // separable [1 2 1] x [1 2 1] / 16, vertical first (matches engine.film_cpu)
    float v[3];
    for (int i = 0; i < 3; ++i) {
        int xx = clamp(x - 1 + i, 0, w - 1);
        float a = dot(float3(mid[(lo*w+xx)*3], mid[(lo*w+xx)*3+1], mid[(lo*w+xx)*3+2])*(1.0f/255.0f), LUMA);
        float b = dot(float3(mid[(md*w+xx)*3], mid[(md*w+xx)*3+1], mid[(md*w+xx)*3+2])*(1.0f/255.0f), LUMA);
        float c = dot(float3(mid[(hi*w+xx)*3], mid[(hi*w+xx)*3+1], mid[(hi*w+xx)*3+2])*(1.0f/255.0f), LUMA);
        v[i] = (a + 2.0f*b + c) * 0.25f;
    }
    float blurred = (v[0] + 2.0f*v[1] + v[2]) * 0.25f;

    int m = (md*w + x) * 3;
    float3 rgb = float3(mid[m], mid[m+1], mid[m+2]) * (1.0f/255.0f);
    float lum = dot(rgb, LUMA);
    float detail = (lum - blurred) * clamp(P.clarity, -20.0f, 0.0f) / 100.0f;

    float2 pos = float2((float(x)*2.0f + 1.0f - float(w)) / float(w),
                        (float(y)*2.0f + 1.0f - float(h)) / float(h));
    float midp = clamp(P.midpoint/100.0f, 0.0f, 0.85f);
    float radius = clamp((dot(pos,pos)*0.5f - midp) / (1.0f - midp), 0.0f, 1.0f);
    float vig = exp2(clamp(P.vignette/100.0f, -1.25f, 1.25f) * radius*radius * (3.0f - 2.0f*radius));

    float level = lum < 0.5f ? P.shadows + (P.midtones-P.shadows)*lum*2.0f
                             : P.midtones + (P.highlights-P.midtones)*(lum*2.0f - 1.0f);
    float amp = clamp(P.grain, 0.0f, 100.0f)/100.0f * max(0.0f, level)/100.0f * 0.06f;
    int2 pixel = int2(x, y);
    float g = (P.grain != 0.0f) ? noiseAt(pixel, P.seed, P.grainSize, P.roughness) * amp : 0.0f;

    float3 outc = (rgb + float3(detail)) * vig + float3(g);
    if (P.colorVariation != 0.0f) {
        float k = clamp(P.colorVariation/100.0f, 0.0f, 1.0f);
        for (int c = 0; c < 3; ++c)
            outc[c] += noiseAt(pixel, P.seed + c + 1, P.grainSize, P.roughness) * amp * k;
    }
    float3 q = floor(clamp(outc, 0.0f, 1.0f) * 255.0f + 0.5f);

    int o = (y*w + x) * 3;
    if (P.ui_strength != 1.0f && photo != nullptr) {
        for (int c = 0; c < 3; ++c) {
            float orig = float(photo[o+c]);
            q[c] = floor(clamp(orig + (q[c] - orig) * P.ui_strength, 0.0f, 255.0f) + 0.5f);
        }
    }
    dst[o] = uchar(q.r); dst[o+1] = uchar(q.g); dst[o+2] = uchar(q.b);
}

// ---- pass 2b: float variant (no quantize, no 8-bit strength blend) ----
kernel void filmf(device const float* mid [[buffer(0)]],
                  device       float* dst [[buffer(1)]],
                  constant Params& P [[buffer(2)]],
                  uint gid [[thread_position_in_grid]])
{
    int idx = int(gid);
    if (idx >= P.out_rows * P.width) return;
    int x = idx % P.width;
    int row = idx / P.width;
    int y = P.y0 + row;
    int w = P.width, h = P.height;
    int last = P.tone_rows - 1;
    int mrow = y - P.first;
    int lo = clamp(mrow - 1, 0, last), md = clamp(mrow, 0, last), hi = clamp(mrow + 1, 0, last);

    float v[3];
    for (int i = 0; i < 3; ++i) {
        int xx = clamp(x - 1 + i, 0, w - 1);
        float a = dot(float3(mid[(lo*w+xx)*3], mid[(lo*w+xx)*3+1], mid[(lo*w+xx)*3+2]), LUMA);
        float b = dot(float3(mid[(md*w+xx)*3], mid[(md*w+xx)*3+1], mid[(md*w+xx)*3+2]), LUMA);
        float c = dot(float3(mid[(hi*w+xx)*3], mid[(hi*w+xx)*3+1], mid[(hi*w+xx)*3+2]), LUMA);
        v[i] = (a + 2.0f*b + c) * 0.25f;
    }
    float blurred = (v[0] + 2.0f*v[1] + v[2]) * 0.25f;

    int m = (md*w + x) * 3;
    float3 rgb = float3(mid[m], mid[m+1], mid[m+2]);
    float lum = dot(rgb, LUMA);
    float detail = (lum - blurred) * clamp(P.clarity, -20.0f, 0.0f) / 100.0f;

    float2 pos = float2((float(x)*2.0f + 1.0f - float(w)) / float(w),
                        (float(y)*2.0f + 1.0f - float(h)) / float(h));
    float midp = clamp(P.midpoint/100.0f, 0.0f, 0.85f);
    float radius = clamp((dot(pos,pos)*0.5f - midp) / (1.0f - midp), 0.0f, 1.0f);
    float vig = exp2(clamp(P.vignette/100.0f, -1.25f, 1.25f) * radius*radius * (3.0f - 2.0f*radius));

    float level = lum < 0.5f ? P.shadows + (P.midtones-P.shadows)*lum*2.0f
                             : P.midtones + (P.highlights-P.midtones)*(lum*2.0f - 1.0f);
    float amp = clamp(P.grain, 0.0f, 100.0f)/100.0f * max(0.0f, level)/100.0f * 0.06f;
    int2 pixel = int2(x, y);
    float g = (P.grain != 0.0f) ? noiseAt(pixel, P.seed, P.grainSize, P.roughness) * amp : 0.0f;

    float3 outc = (rgb + float3(detail)) * vig + float3(g);
    if (P.colorVariation != 0.0f) {
        float k = clamp(P.colorVariation/100.0f, 0.0f, 1.0f);
        for (int c = 0; c < 3; ++c)
            outc[c] += noiseAt(pixel, P.seed + c + 1, P.grainSize, P.roughness) * amp * k;
    }
    int o = (y*w + x) * 3;
    dst[o] = clamp(outc.r, 0.0f, 1.0f);
    dst[o+1] = clamp(outc.g, 0.0f, 1.0f);
    dst[o+2] = clamp(outc.b, 0.0f, 1.0f);
}

// ---- input/output denoise: 3x3 edge-aware weighted mean ----
struct DParams {
    int width, height, pad0, pad1;
    float noise[3], alpha[3], range[3], pad[3];
};

inline int clampi(int v, int hi) { return v < 0 ? 0 : (v > hi ? hi : v); }
inline float plainLum(device const uchar* p) {
    return ((float)p[0]*0.2126f + (float)p[1]*0.7152f) + (float)p[2]*0.0722f;
}
inline float fourth(float x) { return ((x*x)*x)*x; }

kernel void denoise(device const uchar* src [[buffer(0)]],
                    device       uchar* dst [[buffer(1)]],
                    constant DParams& P [[buffer(2)]],
                    uint gid [[thread_position_in_grid]])
{
    int idx = int(gid);
    if (idx >= P.width * P.height) return;
    int x = idx % P.width, y = idx / P.width;
    int w = P.width, h = P.height;
    device const uchar* p = src + idx*3;
    float yy = plainLum(p), u = float(p[0]) - yy, v = float(p[2]) - yy;
    float sy=0, su=0, sv=0, wy=0, wu=0, wv=0;
    for (int j = -1; j <= 1; ++j) {
        float vals[3][3], weights[3][3];
        for (int i = -1; i <= 1; ++i) {
            device const uchar* q = src + (clampi(y+j, h-1)*w + clampi(x+i, w-1))*3;
            float qy = plainLum(q), qu = float(q[0]) - qy, qv = float(q[2]) - qy;
            float weight = (j == 0 ? 2.0f : 1.0f) * (i == 0 ? 2.0f : 1.0f)
                         / (fourth((qy-yy)/P.range[0]) + 1.0f);
            int k = i + 1;
            vals[k][0] = qy; vals[k][1] = qu; vals[k][2] = qv;
            weights[k][0] = weight;
            weights[k][1] = weight / (fourth((qu-u)/P.range[1]) + 1.0f);
            weights[k][2] = weight / (fourth((qv-v)/P.range[2]) + 1.0f);
        }
        sy = ((sy + vals[0][0]*weights[0][0]) + vals[1][0]*weights[1][0]) + vals[2][0]*weights[2][0];
        su = ((su + vals[0][1]*weights[0][1]) + vals[1][1]*weights[1][1]) + vals[2][1]*weights[2][1];
        sv = ((sv + vals[0][2]*weights[0][2]) + vals[1][2]*weights[1][2]) + vals[2][2]*weights[2][2];
        wy = ((wy + weights[0][0]) + weights[1][0]) + weights[2][0];
        wu = ((wu + weights[0][1]) + weights[1][1]) + weights[2][1];
        wv = ((wv + weights[0][2]) + weights[1][2]) + weights[2][2];
    }
    float dy = clamp(P.alpha[0]*(sy/wy - yy), -4.0f, 4.0f);
    float du = clamp(P.alpha[1]*(su/wu - u), -8.0f, 8.0f);
    float dv = clamp(P.alpha[2]*(sv/wv - v), -8.0f, 8.0f);
    float head = clamp(min(yy*0.125f, (255.0f-yy)*0.125f), 0.0f, 1.0f);
    float r = head*(du+dy) + float(p[0]);
    float g = head*(dy + (dv*0.0722f + du*0.2126f)/-0.7152f) + float(p[1]);
    float b = head*(dv+dy) + float(p[2]);
    int o = idx*3;
    dst[o]   = uchar(clampi(int(rint(r)), 255));
    dst[o+1] = uchar(clampi(int(rint(g)), 255));
    dst[o+2] = uchar(clampi(int(rint(b)), 255));
}

// ---- Monopan mode-0 grain (m3.grain_cpu) ----
kernel void monopan(device const uchar* rgb [[buffer(0)]],
                    device       uchar* out [[buffer(1)]],
                    device const uchar* pixmap [[buffer(2)]],
                    device const ushort* batchmap [[buffer(3)]],
                    device const uchar* lutmap [[buffer(4)]],
                    device const uchar* randmap [[buffer(5)]],
                    device const float* sqrt16 [[buffer(6)]],
                    device const uchar* mixedmap [[buffer(7)]],
                    constant int& width [[buffer(8)]],
                    constant int& height [[buffer(9)]],
                    uint gid [[thread_position_in_grid]])
{
    int i = int(gid);
    if (i >= width*height) return;
    uint x = uint(i % width), y = uint(i / width);
    int o = i*3;
    uint a0 = rgb[o], a1 = rgb[o+1], a2 = rgb[o+2];
    uint lum = (((a0*66u + a1*129u + a2*25u + 128u) >> 8u) + 16u);
    uint r1 = randmap[(y % 4096u)*3072u + (x % 3072u)];
    uint r2 = randmap[((uint(height)-1u-y) % 4096u)*3072u + ((uint(width)-1u-x) % 3072u)];
    uint pix = pixmap[lum*256u + r1];
    uint bat = uint(batchmap[pix*256u + r2]);
    float v = float(lutmap[bat]) * sqrt16[lum];
    float value = min(255.0f, floor(v + 0.5f));
    /* value*0.3 + lum*0.7 in float32, precomputed: fast-math reassociation
     * would otherwise disagree with numpy on the exact .5/1.0 boundaries. */
    int mixed = int(mixedmap[lum*256u + uint(value)]);
    int gray = ((mixed*298) - 4640) >> 8;
    uchar g = uchar(clamp(gray, 0, 255));
    out[o] = g; out[o+1] = g; out[o+2] = g;
}
)MSL";

static id<MTLDevice> gDevice = nil;
static id<MTLCommandQueue> gQueue = nil;
static id<MTLComputePipelineState> gTone8 = nil, gToneF = nil, gFilm8 = nil, gFilmF = nil;
static id<MTLComputePipelineState> gDenoise = nil;
static id<MTLComputePipelineState> gMonopan = nil;
static id<MTLBuffer> gPixMap = nil, gBatchMap = nil, gLutMap = nil, gRandMap = nil, gSqrt16 = nil, gMixedMap = nil;
static id<MTLBuffer> gPhoto = nil, gMid = nil, gOut = nil, gLut = nil, gRgbC = nil, gLumaC = nil;
static NSUInteger gPhotoCap = 0, gMidCap = 0, gOutCap = 0, gLutCap = 0;
static char gLastError[512] = {0};

static void set_err(NSString *msg) {
    const char *text = msg ? [msg UTF8String] : NULL;
    if (!text) { gLastError[0] = 0; return; }
    strncpy(gLastError, text, sizeof(gLastError) - 1);
    gLastError[sizeof(gLastError) - 1] = 0;
}

static id<MTLBuffer> ensure(id<MTLBuffer> buf, NSUInteger cap, NSUInteger need, NSUInteger *newCap) {
    if (buf && cap >= need) { *newCap = cap; return buf; }
    NSUInteger size = need < 4096 ? 4096 : need;
    id<MTLBuffer> made = [gDevice newBufferWithLength:size options:MTLResourceStorageModeShared];
    *newCap = made ? size : 0;
    return made;
}

int cl_metal_params_size(void) { return (int)sizeof(cl_metal_params); }

int cl_metal_available(void) {
    if (gDevice) return 1;
    @autoreleasepool {
        gDevice = MTLCreateSystemDefaultDevice();
        return gDevice != nil;
    }
}

int cl_metal_device_name(char *buf, int len) {
    if (!cl_metal_available()) return 0;
    @autoreleasepool {
        const char *n = [[gDevice name] UTF8String];
        snprintf(buf, (size_t)len, "%s", n ? n : "Metal");
    }
    return 1;
}

int cl_metal_init(void) {
    if (gTone8) return 1;
    if (!cl_metal_available()) { set_err(@"no Metal device"); return 0; }
    @autoreleasepool {
        NSError *err = nil;
        /* Two libraries from the same source:
         *  - "precise" (fastMath off) for tone, film and denoise, so float
         *    reassociation/reassociation cannot drift from numpy's operation
         *    order. Denoise feeds every filter, so it must be precise too:
         *    with fast math it was off by 1 LSB and that propagated to 3 LSB
         *    at the output.
         *  - "fast" for Monopan, which is integer-only table lookups where
         *    fast math changes nothing but keeps the compiler off the
         *    critical path.
         * Measured at 24 MP: precise costs ~50 ms per frame over fast math
         * and holds max |diff| at 2 (the project's acceptance bound). */
        MTLCompileOptions *optPrecise = [MTLCompileOptions new];
        optPrecise.fastMathEnabled = NO;
        id<MTLLibrary> precise = [gDevice newLibraryWithSource:[NSString stringWithUTF8String:kSource]
                                                       options:optPrecise error:&err];
        if (!precise) { set_err(err ? [err description] : nil); return 0; }
        MTLCompileOptions *optFast = [MTLCompileOptions new];
        optFast.fastMathEnabled = YES;
        id<MTLLibrary> fast = [gDevice newLibraryWithSource:[NSString stringWithUTF8String:kSource]
                                                    options:optFast error:&err];
        if (!fast) { set_err(err ? [err description] : nil); return 0; }
        gTone8 = [gDevice newComputePipelineStateWithFunction:[precise newFunctionWithName:@"tone8"] error:&err];
        gToneF = [gDevice newComputePipelineStateWithFunction:[precise newFunctionWithName:@"tonef"] error:&err];
        gFilm8 = [gDevice newComputePipelineStateWithFunction:[precise newFunctionWithName:@"film8"] error:&err];
        gFilmF = [gDevice newComputePipelineStateWithFunction:[precise newFunctionWithName:@"filmf"] error:&err];
        gDenoise = [gDevice newComputePipelineStateWithFunction:[precise newFunctionWithName:@"denoise"] error:&err];
        gMonopan = [gDevice newComputePipelineStateWithFunction:[fast newFunctionWithName:@"monopan"] error:&err];
        if (!gTone8 || !gToneF || !gFilm8 || !gFilmF || !gDenoise || !gMonopan) {
            set_err(err ? [err description] : nil);
            return 0;
        }
        gQueue = [gDevice newCommandQueue];
        if (!gQueue) { set_err(@"no command queue"); return 0; }
    }
    return 1;
}

const char *cl_metal_last_error(void) { return gLastError; }

int cl_metal_reserve(int photo_bytes, int float_bytes) {
    if (!cl_metal_init()) return 0;
    NSUInteger need = (NSUInteger)(float_bytes > photo_bytes ? float_bytes : photo_bytes);
    gPhoto = ensure(gPhoto, gPhotoCap, (NSUInteger)photo_bytes, &gPhotoCap);
    gMid   = ensure(gMid,   gMidCap,   need, &gMidCap);
    gOut   = ensure(gOut,   gOutCap,   need, &gOutCap);
    return gPhoto && gMid && gOut;
}

int cl_metal_set_lut(const float *lut_rgba, int n) {
    if (!cl_metal_init()) return 0;
    NSUInteger bytes = (NSUInteger)n * n * n * 4 * sizeof(float);
    /* Always re-upload: every filter's LUT has the same byte size, so a
     * size-based cache would silently keep the previous filter's table. */
    if (gLut && gLutCap == bytes) {
        memcpy(gLut.contents, lut_rgba, (size_t)bytes);
        return 1;
    }
    gLut = [gDevice newBufferWithBytes:lut_rgba length:bytes options:MTLResourceStorageModeShared];
    gLutCap = gLut ? bytes : 0;
    return gLut != nil;
}

int cl_metal_set_curves(const float *rgb_curve, int rgb_count,
                        const float *luma_curve, int luma_count) {
    if (!cl_metal_init()) return 0;
    float rgbp[16] = {0}, lumap[16] = {0};
    for (int i = 0; i < rgb_count * 2 && i < 16; ++i) rgbp[i] = rgb_curve[i];
    for (int i = 0; i < luma_count * 2 && i < 16; ++i) lumap[i] = luma_curve[i];
    gRgbC = [gDevice newBufferWithBytes:rgbp length:sizeof(rgbp) options:MTLResourceStorageModeShared];
    gLumaC = [gDevice newBufferWithBytes:lumap length:sizeof(lumap) options:MTLResourceStorageModeShared];
    return gRgbC && gLumaC;
}

int cl_metal_upload(const void *rgb, int bytes) {
    if (!cl_metal_init()) return 0;
    gPhoto = ensure(gPhoto, gPhotoCap, (NSUInteger)bytes, &gPhotoCap);
    if (!gPhoto) return 0;
    if (rgb) memcpy(gPhoto.contents, rgb, (size_t)bytes);
    return 1;
}

int cl_metal_download(void *dst, int bytes) {
    if (!gOut || !dst) return 0;
    if ((NSUInteger)bytes > gOutCap) return 0;
    memcpy(dst, gOut.contents, (size_t)bytes);
    return 1;
}

/* Encode tone+film. `floatPass` selects the float pipelines (padded float in,
 * float interior out); otherwise the resident uint8 photo is the source.
 * When `blend` is 0 the uint8 film pass skips the UI strength blend. */
static int dispatch(const cl_metal_params *P, int floatPass, int blend) {
    if (!cl_metal_init()) return 0;
    NSUInteger threads = (NSUInteger)P->out_rows * P->width;
    NSUInteger toneThreads = (NSUInteger)P->tone_rows * P->width;
    id<MTLComputePipelineState> pt = floatPass ? gToneF : gTone8;
    id<MTLComputePipelineState> pf = floatPass ? gFilmF : gFilm8;

    @autoreleasepool {
        id<MTLCommandBuffer> cb = [gQueue commandBuffer];
        id<MTLComputeCommandEncoder> e = [cb computeCommandEncoder];
        [e setComputePipelineState:pt];
        [e setBuffer:gPhoto offset:0 atIndex:0];
        [e setBuffer:gMid offset:0 atIndex:1];
        [e setBuffer:gLut offset:0 atIndex:2];
        [e setBuffer:gRgbC offset:0 atIndex:3];
        [e setBuffer:gLumaC offset:0 atIndex:4];
        [e setBytes:P length:sizeof(*P) atIndex:5];
        NSUInteger tg = pt.maxTotalThreadsPerThreadgroup;
        if (tg > 256) tg = 256;
        [e dispatchThreads:MTLSizeMake(toneThreads, 1, 1) threadsPerThreadgroup:MTLSizeMake(tg, 1, 1)];
        [e endEncoding];

        e = [cb computeCommandEncoder];
        [e setComputePipelineState:pf];
        [e setBuffer:gMid offset:0 atIndex:0];
        if (floatPass) {
            [e setBuffer:gOut offset:0 atIndex:1];
            [e setBytes:P length:sizeof(*P) atIndex:2];
        } else {
            [e setBuffer:gPhoto offset:0 atIndex:1];
            [e setBuffer:gOut offset:0 atIndex:2];
            [e setBytes:P length:sizeof(*P) atIndex:3];
        }
        NSUInteger tg2 = pf.maxTotalThreadsPerThreadgroup;
        if (tg2 > 256) tg2 = 256;
        [e dispatchThreads:MTLSizeMake(threads, 1, 1) threadsPerThreadgroup:MTLSizeMake(tg2, 1, 1)];
        [e endEncoding];
        [cb commit];
        [cb waitUntilCompleted];
        if (cb.status == MTLCommandBufferStatusError) {
            set_err(cb.error ? [cb.error description] : nil);
            return 0;
        }
    }
    (void)blend;
    return 1;
}

int cl_metal_render_u8(const cl_metal_params *P) { return dispatch(P, 0, 1); }
int cl_metal_render_f32(const cl_metal_params *P) { return dispatch(P, 1, 0); }

/* Same median-statistics pass as native_post.c cl_output_denoise; it only
 * visits ~16000 samples so the CPU is the right place for the sort. */
static int cmp_float(const void *a, const void *b) {
    float fa = *(const float *)a, fb = *(const float *)b;
    return fa < fb ? -1 : (fa > fb ? 1 : 0);
}
static float plain_lum_c(const unsigned char *p) {
    return ((float)p[0]*.2126f + (float)p[1]*.7152f) + (float)p[2]*.0722f;
}
static int clampi_c(int v, int hi) { return v < 0 ? 0 : (v > hi ? hi : v); }

int cl_metal_output_denoise(const unsigned char *src, unsigned char *dst,
                            int w, int h, int style) {
    if (w < 3 || h < 3 || style < 1 || style > 8) return 1;
    if (!cl_metal_init()) return 0;
    int step = (int)sqrt(((double)w * h) / 16000.);
    if (step < 2) step = 1;
    size_t max_samples = ((size_t)(w - 2) + step - 1) / step * ((h - 2 + step - 1) / step);
    float *samples = malloc(max_samples * 3 * sizeof(float));
    if (!samples) return 0;
    size_t count = 0;
    for (int y = 1; y < h - 1; y += step) for (int x = 1; x < w - 1; x += step) {
        const unsigned char *p = src + ((size_t)y * w + x) * 3;
        float lap = (((plain_lum_c(p) * 4.f - plain_lum_c(p - 3)) - plain_lum_c(p + 3))
                     - plain_lum_c(p - (size_t)w * 3)) - plain_lum_c(p + (size_t)w * 3);
        samples[count] = fabsf(lap);
        samples[max_samples + count] = fabsf((float)((int)p[0] * 4 - ((int)p[-3] + p[3] + p[-w*3] + p[w*3])) - lap);
        samples[2 * max_samples + count] = fabsf((float)((int)p[2] * 4 - ((int)p[-1] + p[5] + p[2-w*3] + p[2+w*3])) - lap);
        count++;
    }
    cl_metal_denoise_params P;
    memset(&P, 0, sizeof(P));
    P.width = w; P.height = h;
    int active = 0;
    for (int c = 0; c < 3; c++) {
        qsort(samples + c * max_samples, count, sizeof(float), cmp_float);
        P.noise[c] = fminf(samples[c * max_samples + count/2] / 3.016f, 12.f);
        P.alpha[c] = fminf(fmaxf((P.noise[c] - 1.25f) / 5.f, 0.f) * (c ? .6f : .42f), c ? .6f : .42f);
    }
    free(samples);
    if ((style & 13) == 4 || (style & 11) == 1) P.alpha[0] = 0.f;
    for (int c = 0; c < 3; c++) if (P.alpha[c] != 0.f) active = 1;
    if (!active) { memcpy(dst, src, (size_t)w * h * 3); return 1; }
    for (int c = 0; c < 3; c++) P.range[c] = fmaxf(P.noise[c] * 2.5f, 2.f);

    NSUInteger bytes = (NSUInteger)w * h * 3;
    gPhoto = ensure(gPhoto, gPhotoCap, bytes, &gPhotoCap);
    gOut = ensure(gOut, gOutCap, bytes, &gOutCap);
    if (!gPhoto || !gOut) { set_err(@"denoise buffers"); return 0; }
    memcpy(gPhoto.contents, src, bytes);

    @autoreleasepool {
        id<MTLCommandBuffer> cb = [gQueue commandBuffer];
        id<MTLComputeCommandEncoder> e = [cb computeCommandEncoder];
        [e setComputePipelineState:gDenoise];
        [e setBuffer:gPhoto offset:0 atIndex:0];
        [e setBuffer:gOut offset:0 atIndex:1];
        [e setBytes:&P length:sizeof(P) atIndex:2];
        NSUInteger tg = gDenoise.maxTotalThreadsPerThreadgroup;
        if (tg > 256) tg = 256;
        [e dispatchThreads:MTLSizeMake(bytes / 3, 1, 1) threadsPerThreadgroup:MTLSizeMake(tg, 1, 1)];
        [e endEncoding];
        [cb commit];
        [cb waitUntilCompleted];
        if (cb.status != MTLCommandBufferStatusCompleted) {
            set_err(cb.error ? [cb.error description] : nil);
            return 0;
        }
    }
    memcpy(dst, gOut.contents, bytes);
    return 1;
}

int cl_metal_set_monopan(const unsigned char *pixel_map, const unsigned short *batch_map,
                         const unsigned char *lut_map, const unsigned char *rand_map,
                         const float *sqrt16, const unsigned char *mixed_map) {
    if (!cl_metal_init()) return 0;
    if (gPixMap) return 1;                       /* static tables: upload once */
    gPixMap   = [gDevice newBufferWithBytes:pixel_map length:256*256*sizeof(unsigned char) options:MTLResourceStorageModeShared];
    gBatchMap = [gDevice newBufferWithBytes:batch_map length:256*256*sizeof(unsigned short) options:MTLResourceStorageModeShared];
    gLutMap   = [gDevice newBufferWithBytes:lut_map length:256*256*sizeof(unsigned char) options:MTLResourceStorageModeShared];
    gRandMap  = [gDevice newBufferWithBytes:rand_map length:(size_t)4096*3072 options:MTLResourceStorageModeShared];
    gSqrt16   = [gDevice newBufferWithBytes:sqrt16 length:256*sizeof(float) options:MTLResourceStorageModeShared];
    gMixedMap = [gDevice newBufferWithBytes:mixed_map length:256*256 options:MTLResourceStorageModeShared];
    if (!gPixMap || !gBatchMap || !gLutMap || !gRandMap || !gSqrt16 || !gMixedMap) { set_err(@"monopan tables"); return 0; }
    return 1;
}

int cl_metal_monopan_grain(const unsigned char *rgb, unsigned char *out, int w, int h) {
    if (!cl_metal_init() || !gPixMap) { set_err(@"monopan tables not uploaded"); return 0; }
    NSUInteger bytes = (NSUInteger)w * h * 3;
    gPhoto = ensure(gPhoto, gPhotoCap, bytes, &gPhotoCap);
    gOut   = ensure(gOut, gOutCap, bytes, &gOutCap);
    if (!gPhoto || !gOut) { set_err(@"monopan buffers"); return 0; }
    memcpy(gPhoto.contents, rgb, bytes);
    @autoreleasepool {
        id<MTLCommandBuffer> cb = [gQueue commandBuffer];
        id<MTLComputeCommandEncoder> e = [cb computeCommandEncoder];
        [e setComputePipelineState:gMonopan];
        [e setBuffer:gPhoto offset:0 atIndex:0];
        [e setBuffer:gOut offset:0 atIndex:1];
        [e setBuffer:gPixMap offset:0 atIndex:2];
        [e setBuffer:gBatchMap offset:0 atIndex:3];
        [e setBuffer:gLutMap offset:0 atIndex:4];
        [e setBuffer:gRandMap offset:0 atIndex:5];
        [e setBuffer:gSqrt16 offset:0 atIndex:6];
        [e setBuffer:gMixedMap offset:0 atIndex:7];
        [e setBytes:&w length:4 atIndex:8];
        [e setBytes:&h length:4 atIndex:9];
        NSUInteger tg = gMonopan.maxTotalThreadsPerThreadgroup;
        if (tg > 256) tg = 256;
        [e dispatchThreads:MTLSizeMake((NSUInteger)w*h, 1, 1) threadsPerThreadgroup:MTLSizeMake(tg, 1, 1)];
        [e endEncoding];
        [cb commit];
        [cb waitUntilCompleted];
        if (cb.status != MTLCommandBufferStatusCompleted) {
            set_err(cb.error ? [cb.error description] : nil);
            return 0;
        }
    }
    memcpy(out, gOut.contents, bytes);
    return 1;
}

void cl_metal_shutdown(void) {
    gTone8 = gToneF = gFilm8 = gFilmF = gDenoise = gMonopan = nil;
    gPixMap = gBatchMap = gLutMap = gRandMap = gSqrt16 = gMixedMap = nil;
    gPhoto = gMid = gOut = gLut = gRgbC = gLumaC = nil;
    gPhotoCap = gMidCap = gOutCap = gLutCap = 0;
    gQueue = nil;
    gDevice = nil;
    set_err(nil);
}
