package com.codex.cameralook;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class ToneMath {

    static final class Params {
        float clarity;
        float colorVariation;
        float grain;
        float grainSize;
        float highlights;
        float[] luma;
        float midpoint;
        float midtones;
        float[] rgb;
        float roughness;
        float shadows;
        float strength = 1.0f;
        float vignette;

        Params() {
        }
    }

    ToneMath() {
    }

    static float clamp(float f) {
        return Math.max(0.0f, Math.min(1.0f, f));
    }

    static float curve(float f, float[] fArr) {
        float fClamp = clamp(f) * 255.0f;
        if (fClamp <= fArr[0]) {
            return clamp(fArr[1] / 255.0f);
        }
        for (int i = 2; i < fArr.length; i += 2) {
            if (fClamp <= fArr[i]) {
                int i2 = i - 2;
                int i3 = i - 1;
                return clamp((fArr[i3] + (((fArr[i + 1] - fArr[i3]) * (fClamp - fArr[i2])) / (fArr[i] - fArr[i2]))) / 255.0f);
            }
        }
        return clamp(fArr[fArr.length - 1] / 255.0f);
    }

    static float luma(int i) {
        return (((((i >>> 16) & 255) * 0.2126f) + (((i >>> 8) & 255) * 0.7152f)) + ((i & 255) * 0.0722f)) / 255.0f;
    }

    static int channel(float f) {
        return Math.max(0, Math.min(255, Math.round(f * 255.0f)));
    }

    static int color(float[] fArr) {
        return channel(fArr[2]) | (channel(fArr[0]) << 16) | (-16777216) | (channel(fArr[1]) << 8);
    }

    static int toned(int i, ToneTable toneTable, Params params, float[] fArr) {
        toneTable.map(((i >>> 16) & 255) / 255.0f, ((i >>> 8) & 255) / 255.0f, (i & 255) / 255.0f, fArr);
        for (int i2 = 0; i2 < 3; i2++) {
            fArr[i2] = curve(fArr[i2], params.rgb);
        }
        float f = (fArr[0] * 0.2126f) + (fArr[1] * 0.7152f) + (fArr[2] * 0.0722f);
        float fCurve = curve(f, params.luma);
        for (int i3 = 0; i3 < 3; i3++) {
            fArr[i3] = intensify(((i >>> (16 - (i3 * 8))) & 255) / 255.0f, clamp(f > 1.0E-6f ? (fArr[i3] * fCurve) / f : fCurve), params.strength);
        }
        return color(fArr);
    }

    static float intensify(float f, float f2, float f3) {
        float fMax = (Math.max(1.0f, Math.min(1.8f, f3)) - 1.0f) * (f2 - f);
        float f4 = fMax >= 0.0f ? 1.0f - f2 : f2;
        if (f4 > 0.0f) {
            f2 += (fMax * f4) / (f4 + Math.abs(fMax));
        }
        return clamp(f2);
    }

    static float hash(int i, int i2, int i3) {
        int i4 = (i * 521288629) + (i2 * 1597334677) + (i3 * 1821285621);
        int i5 = (i4 ^ (i4 >>> 16)) * 2146121005;
        int i6 = (i5 ^ (i5 >>> 15)) * (-2073254261);
        return (((i6 ^ (i6 >>> 16)) & 16777215) / 8388607.5f) - 1.0f;
    }

    static float noise(int i, int i2, int i3, float f, float f2) {
        float fMax = (Math.max(0.0f, f) / 25.0f) + 1.0f;
        float f3 = i / fMax;
        float f4 = i2 / fMax;
        int i4 = (int) f3;
        int i5 = (int) f4;
        float f5 = f3 - i4;
        float f6 = f4 - i5;
        float f7 = 1.0f - f5;
        int i6 = i4 + 1;
        float fHash = ((hash(i4, i5, i3) * f7) + (hash(i6, i5, i3) * f5)) * (1.0f - f6);
        int i7 = i5 + 1;
        float fHash2 = fHash + (((hash(i4, i7, i3) * f7) + (hash(i6, i7, i3) * f5)) * f6);
        float fMin = Math.min(0.7f, Math.max(0.0f, f2) / 100.0f);
        return (fHash2 * (1.0f - fMin)) + (hash(i, i2, i3 + 83) * fMin);
    }

    static int film(int i, int i2, int i3, int i4, int i5, int i6, Params params, float f) {
        float f2;
        float f3;
        float f4;
        float f5 = ((i >>> 16) & 255) / 255.0f;
        float f6 = ((i >>> 8) & 255) / 255.0f;
        float f7 = (i & 255) / 255.0f;
        float f8 = (0.2126f * f5) + (0.7152f * f6) + (0.0722f * f7);
        float fMax = (f8 - f) * (Math.max(-20.0f, Math.min(0.0f, params.clarity)) / 100.0f);
        float fMax2 = (((i2 * 2.0f) + 1.0f) - i4) / Math.max(1, i4);
        float fMax3 = (((i3 * 2.0f) + 1.0f) - i5) / Math.max(1, i5);
        float fMax4 = Math.max(0.0f, Math.min(0.85f, params.midpoint / 100.0f));
        float fClamp = clamp(((((fMax2 * fMax2) + (fMax3 * fMax3)) * 0.5f) - fMax4) / (1.0f - fMax4));
        float fPow = (float) Math.pow(2.0d, Math.max(-1.25f, Math.min(1.25f, params.vignette / 100.0f)) * fClamp * fClamp * (3.0f - (fClamp * 2.0f)));
        if (f8 < 0.5f) {
            f2 = params.shadows;
            f3 = params.midtones - params.shadows;
            f4 = f8 * 2.0f;
        } else {
            f2 = params.midtones;
            f3 = params.highlights - params.midtones;
            f4 = (f8 * 2.0f) - 1.0f;
        }
        float fMax5 = (((Math.max(0.0f, Math.min(100.0f, params.grain)) / 100.0f) * Math.max(0.0f, f2 + (f3 * f4))) / 100.0f) * 0.06f;
        float fNoise = noise(i2, i3, i6, params.grainSize, params.roughness) * fMax5;
        float fMin = Math.min(1.0f, Math.max(0.0f, params.colorVariation) / 100.0f);
        float fNoise2 = ((f5 + fMax) * fPow) + fNoise + (noise(i2, i3, i6 + 1, params.grainSize, params.roughness) * fMax5 * fMin);
        float fNoise3 = ((f6 + fMax) * fPow) + fNoise + (noise(i2, i3, i6 + 2, params.grainSize, params.roughness) * fMax5 * fMin);
        return channel(((f7 + fMax) * fPow) + fNoise + (noise(i2, i3, i6 + 3, params.grainSize, params.roughness) * fMax5 * fMin)) | (channel(fNoise2) << 16) | (-16777216) | (channel(fNoise3) << 8);
    }
}
