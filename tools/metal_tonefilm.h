/* C ABI shared by metal_tonefilm.mm and the Python ctypes binding.
 * Field order must match `struct Params` in the Metal source verbatim
 * (24 x 4-byte scalars, no padding). */
#ifndef CAMERALOOK_METAL_TONEFILM_H
#define CAMERALOOK_METAL_TONEFILM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int width, height, n, rgb_count, luma_count, seed, y0, out_rows, first, tone_rows;
    int pad0, pad1;
    float strength, clarity, midpoint, vignette, shadows, midtones, highlights;
    float grain, grainSize, roughness, colorVariation;
    float ui_strength;        /* UI strength applied after quantize */
} cl_metal_params;

typedef struct {
    int width, height, pad0, pad1;
    float noise[3], alpha[3], range[3], pad[3];
} cl_metal_denoise_params;

int cl_metal_params_size(void);
int cl_metal_available(void);
int cl_metal_init(void);
int cl_metal_device_name(char *buf, int len);
const char *cl_metal_last_error(void);

/* Reserve device buffers for `photo_bytes` (uint8 RGB) and `float_bytes`
 * (float32 RGB, used by the high-precision path). */
int cl_metal_reserve(int photo_bytes, int float_bytes);
int cl_metal_set_lut(const float *lut_rgba, int n);
int cl_metal_set_curves(const float *rgb_curve, int rgb_count,
                        const float *luma_curve, int luma_count);

/* Resident-photo path: upload once, render many filters, download once. */
int cl_metal_upload(const void *rgb, int bytes);
int cl_metal_download(void *dst, int bytes);

int cl_metal_render_u8(const cl_metal_params *p);
int cl_metal_render_f32(const cl_metal_params *p);

/* Input/output denoise (native_post.c cl_output_denoise): the median-statistics
 * pass stays on the CPU (about 16k samples), the 3x3 filter pass runs on Metal. */
int cl_metal_output_denoise(const unsigned char *src, unsigned char *dst,
                            int w, int h, int style);

/* Monopan mode-0 grain (m3.grain_cpu): four static 8/16-bit tables plus a
 * 256-entry sqrt table precomputed on the CPU, so the kernel is integer-only. */
int cl_metal_set_monopan(const unsigned char *pixel_map, const unsigned short *batch_map,
                         const unsigned char *lut_map, const unsigned char *rand_map,
                         const float *sqrt16, const unsigned char *mixed_map);
int cl_metal_monopan_grain(const unsigned char *rgb, unsigned char *out, int w, int h);

void cl_metal_shutdown(void);

#ifdef __cplusplus
}
#endif
#endif
