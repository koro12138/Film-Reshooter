package com.codex.cameralook;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class GainPlane {
    GainPlane() {
    }

    static int[] fromPixels(int[] iArr, int i, int i2) {
        int length = iArr.length;
        int[] iArr2 = new int[length];
        for (int i3 = 0; i3 < length; i3++) {
            iArr2[i3] = HdrMath.generated(iArr[i3]);
        }
        return smooth(iArr2, i, i2);
    }

    static int[] smooth(int[] iArr, int i, int i2) {
        if (i < 1 || i2 < 1 || iArr.length != ((long) i) * ((long) i2)) {
            throw new IllegalArgumentException("Gain plane dimensions");
        }
        int[] iArr2 = new int[iArr.length];
        int[] iArr3 = new int[iArr.length];
        for (int i3 = 0; i3 < i2; i3++) {
            int i4 = 0;
            while (i4 < i) {
                int i5 = i3 * i;
                int i6 = i5 + i4;
                int i7 = (iArr[Math.max(0, i4 - 1) + i5] & 255) + ((iArr[i6] & 255) * 2);
                i4++;
                iArr2[i6] = ((i7 + (iArr[i5 + Math.min(i - 1, i4)] & 255)) + 2) / 4;
            }
        }
        for (int i8 = 0; i8 < i2; i8++) {
            for (int i9 = 0; i9 < i; i9++) {
                int i10 = (i8 * i) + i9;
                iArr3[i10] = HdrMath.gray((((iArr2[(Math.max(0, i8 - 1) * i) + i9] + (iArr2[i10] * 2)) + iArr2[(Math.min(i2 - 1, i8 + 1) * i) + i9]) + 2) / 4);
            }
        }
        return iArr3;
    }
}
