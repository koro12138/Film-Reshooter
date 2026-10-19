/* M9 frame packing, identical float32 operation order to FrameProtocol.
 * No fast-math or implicit multiply/add contraction. */
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "native_threads.h"
#ifdef _WIN32
#define API __declspec(dllexport)
#else
#define API __attribute__((visibility("default")))
#endif

API int cl_m9_tiles_version(void) { return 2; }

/* Reflection-101 frame gather at the fixed 4096x3072 canvas. Two int32 index
 * maps skip the 12.6M-element fancy-index gather NumPy does here (~0.25s).
 * Rows are independent, so the band split is bit-identical. */
typedef struct { const uint8_t *src;int w;uint8_t *dst;const int32_t *xs;const int32_t *ys; } FrameJob;
static void frame_rows(void *ctx, int y0, int y1) {
    FrameJob *j = (FrameJob *)ctx;
    for (int y = y0; y < y1; ++y) {
        const uint8_t *row = j->src + (size_t)j->ys[y] * j->w * 3;
        uint8_t *out = j->dst + (size_t)y * 4096 * 3;
        for (int x = 0; x < 4096; ++x) {
            const uint8_t *s = row + (size_t)j->xs[x] * 3;
            out[0] = s[0]; out[1] = s[1]; out[2] = s[2];
            out += 3;
        }
    }
}
API int cl_m9_frame(const uint8_t *src, int w, int h, uint8_t *dst,
                    const int32_t *xs, const int32_t *ys) {
    if (!src || !dst || !xs || !ys || w < 1 || h < 1) return 0;
    (void)h;
    FrameJob job = {src, w, dst, xs, ys};
    cl_run_rows(frame_rows, &job, 3072);
    return 1;
}

/* 4x4 box mean of the frame (finite float math, round-half-to-even like np.rint). */
typedef struct { const uint8_t *src;uint8_t *dst; } ReduceJob;
static void reduce_rows(void *ctx, int y0, int y1) {
    ReduceJob *j = (ReduceJob *)ctx;
    for (int y = y0; y < y1; ++y) {
        for (int x = 0; x < 1024; ++x) {
            const uint8_t *base = j->src + ((size_t)(y * 4) * 4096 + x * 4) * 3;
            for (int c = 0; c < 3; ++c) {
                unsigned sum = 0;
                for (int yy = 0; yy < 4; ++yy) {
                    const uint8_t *p = base + (size_t)yy * 4096 * 3 + c;
                    sum += ((unsigned)p[0] + p[3]) + ((unsigned)p[6] + p[9]);
                }
                j->dst[((size_t)y * 1024 + x) * 3 + c] = (uint8_t)nearbyintf((float)sum / 16.0f);
            }
        }
    }
}
API int cl_m9_reduce(const uint8_t *original, uint8_t *reduced) {
    if (!original || !reduced) return 0;
    ReduceJob job = {original, reduced};
    cl_run_rows(reduce_rows, &job, 768);
    return 1;
}

API int cl_m9_pack(const uint8_t *original, const uint8_t *styled,
                   int index, float *output) {
    if (!original || !styled || !output || index < 0 || index >= 48) return 0;
    const int count = 544 * 544;
    const int left = (index % 8) * 512 - 16, top = (index / 8) * 512 - 16;
    for (int y = 0; y < 544; ++y) {
        int gy = y + top, cy = gy < 0 ? 0 : gy >= 3072 ? 3071 : gy;
        for (int x = 0; x < 544; ++x) {
            int gx = x + left, cx = gx < 0 ? 0 : gx >= 4096 ? 4095 : gx;
            int pos = y * 544 + x;
            int valid = gx >= 0 && gx < 4096 && gy >= 0 && gy < 3072;
            const uint8_t *s = styled + ((cy / 4) * 1024 + cx / 4) * 3;
            const uint8_t *o = original + (cy * 4096 + cx) * 3;
            for (int c = 0; c < 3; ++c) {
                output[c * count + pos] = ((float)(valid ? s[c] : 0) - 128.0f) / 127.5f;
                output[(c + 3) * count + pos] = ((float)(valid ? o[c] : 0) - 128.0f) / 127.5f;
            }
        }
    }
    return 1;
}

API int cl_m9_unpack(const float *tensor, int index, uint8_t *output) {
    if (!tensor || !output || index < 0 || index >= 48) return 0;
    const int left = (index % 8) * 512, top = (index / 8) * 512;
    for (int y = 0; y < 512; ++y) {
        for (int x = 0; x < 512; ++x) {
            for (int c = 0; c < 3; ++c) {
                float v = tensor[c * 544 * 544 + (y + 16) * 544 + x + 16];
                if (!isfinite(v)) return 0;
                v = v * 127.5f;
                v = v + 128.0f;
                v = v < 0 ? 0 : v > 255 ? 255 : v;
                output[((top + y) * 4096 + left + x) * 3 + c] = (uint8_t)nearbyintf(v);
            }
        }
    }
    return 1;
}
