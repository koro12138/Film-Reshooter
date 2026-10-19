package com.codex.cameralook;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class HdrMath {
    private HdrMath() {
    }

    static float clamp(float f, float f2, float f3) {
        return Math.max(f2, Math.min(f3, f));
    }

    static float smooth(float f, float f2, float f3) {
        float fClamp = clamp((f3 - f) / (f2 - f), 0.0f, 1.0f);
        return fClamp * fClamp * (3.0f - (fClamp * 2.0f));
    }

    static float luma(int i) {
        return (((((i >>> 16) & 255) * 0.2126f) + (((i >>> 8) & 255) * 0.7152f)) + ((i & 255) * 0.0722f)) / 255.0f;
    }

    static float limit(boolean z) {
        return z ? 1.8f : 2.0f;
    }

    static int generated(int i) {
        return gray(Math.round(smooth(0.36f, 0.94f, luma(i)) * 255.0f));
    }

    static int gray(int i) {
        int iMax = Math.max(0, Math.min(255, i));
        return iMax | (iMax << 16) | (-16777216) | (iMax << 8);
    }

    static int source(int i, boolean z, float[] fArr, float[] fArr2, float[] fArr3, int i2, boolean z2) {
        float[] fArr4 = {0.2126f, 0.7152f, 0.0722f};
        int i3 = 0;
        double dLog = 0.0d;
        for (int i4 = 3; i3 < i4; i4 = 3) {
            if (fArr[i3] <= 0.0f || fArr2[i3] <= 0.0f || fArr3[i3] <= 0.0f || !Float.isFinite(fArr[i3]) || !Float.isFinite(fArr2[i3]) || !Float.isFinite(fArr3[i3])) {
                throw new IllegalArgumentException("Invalid gain range");
            }
            dLog += ((double) fArr4[i3]) * (Math.log(fArr[i3]) + ((Math.log(fArr2[i3]) - Math.log(fArr[i3])) * Math.pow(((double) ((i >>> (z ? 24 : 16 - (i3 * 8))) & 255)) / 255.0d, fArr3[i3])));
            i3++;
            fArr4 = fArr4;
        }
        return gray((int) Math.round(((Math.max(0.0d, Math.min(Math.log(limit(z2)), dLog)) * ((double) smooth(0.1f, 0.55f, luma(i2)))) * 255.0d) / Math.log(limit(z2))));
    }

    static int difference(int i, int i2) {
        return Math.max(Math.abs(((i >>> 16) & 255) - ((i2 >>> 16) & 255)), Math.max(Math.abs(((i >>> 8) & 255) - ((i2 >>> 8) & 255)), Math.abs((i & 255) - (i2 & 255))));
    }
}
