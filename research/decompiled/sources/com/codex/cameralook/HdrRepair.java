package com.codex.cameralook;

import android.graphics.Bitmap;
import android.graphics.Gainmap;
import java.util.Arrays;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class HdrRepair {
    HdrRepair() {
    }

    static boolean valid(Bitmap bitmap) {
        if (bitmap != null && !bitmap.isRecycled() && bitmap.hasGainmap()) {
            Gainmap gainmap = bitmap.getGainmap();
            Bitmap gainmapContents = gainmap == null ? null : gainmap.getGainmapContents();
            if (gainmapContents != null && !gainmapContents.isRecycled() && gainmapContents.getWidth() >= 1 && gainmapContents.getHeight() >= 1) {
                float[] ratioMin = gainmap.getRatioMin();
                float[] ratioMax = gainmap.getRatioMax();
                float[] gamma = gainmap.getGamma();
                float[] epsilonSdr = gainmap.getEpsilonSdr();
                float[] epsilonHdr = gainmap.getEpsilonHdr();
                if (!finite(ratioMin, true) || !finite(ratioMax, true) || !finite(gamma, true) || !finite(epsilonSdr, false) || !finite(epsilonHdr, false)) {
                    return false;
                }
                for (int i = 0; i < 3; i++) {
                    if (ratioMax[i] < ratioMin[i]) {
                        return false;
                    }
                }
                float minDisplayRatioForHdrTransition = gainmap.getMinDisplayRatioForHdrTransition();
                float displayRatioForFullHdr = gainmap.getDisplayRatioForFullHdr();
                return Float.isFinite(minDisplayRatioForHdrTransition) && Float.isFinite(displayRatioForFullHdr) && minDisplayRatioForHdrTransition > 0.0f && displayRatioForFullHdr >= minDisplayRatioForHdrTransition;
            }
        }
        return false;
    }

    static boolean finite(float[] fArr, boolean z) {
        if (fArr != null && fArr.length >= 3) {
            for (int i = 0; i < 3; i++) {
                if (Float.isFinite(fArr[i])) {
                    if (z) {
                        if (fArr[i] > 0.0f) {
                        }
                    } else if (fArr[i] >= 0.0f) {
                    }
                }
            }
            return true;
        }
        return false;
    }

    static int difference(int i, int i2) {
        return Math.max(Math.abs(((i >>> 16) & 255) - ((i2 >>> 16) & 255)), Math.max(Math.abs(((i >>> 8) & 255) - ((i2 >>> 8) & 255)), Math.abs((i & 255) - (i2 & 255))));
    }

    static int[] offsets(int i) {
        if (i == 0) {
            return new int[1];
        }
        return i == 1 ? new int[]{0, 1} : new int[]{0, i / 2, i};
    }

    static int[] locate(Bitmap bitmap, Bitmap bitmap2) {
        boolean z;
        int width = bitmap2.getWidth() - bitmap.getWidth();
        int height = bitmap2.getHeight() - bitmap.getHeight();
        if (width < 0 || height < 0 || width > bitmap.getWidth() || height > bitmap.getHeight()) {
            return null;
        }
        int width2 = bitmap.getWidth();
        int height2 = bitmap.getHeight();
        int[] iArr = new int[121];
        int i = 0;
        int i2 = 0;
        while (true) {
            z = true;
            if (i >= 11) {
                break;
            }
            int i3 = width;
            int i4 = 0;
            while (i4 < 11) {
                int[] iArr2 = new int[1];
                bitmap.getPixels(iArr2, 0, 1, ((width2 - 1) * i4) / 10, ((height2 - 1) * i) / 10, 1, 1);
                iArr[i2] = iArr2[0];
                i4++;
                i2++;
            }
            i++;
            width = i3;
        }
        int[] iArr3 = new int[1];
        int[] iArrOffsets = offsets(height);
        int length = iArrOffsets.length;
        int i5 = -1;
        int i6 = -1;
        int i7 = 0;
        int i8 = 0;
        int i9 = 0;
        while (i8 < length) {
            int i10 = iArrOffsets[i8];
            int[] iArrOffsets2 = offsets(width);
            boolean z2 = z;
            int length2 = iArrOffsets2.length;
            int i11 = i9;
            int i12 = 0;
            while (i12 < length2) {
                int i13 = iArrOffsets2[i12];
                int i14 = width;
                int i15 = i8;
                int i16 = 0;
                int i17 = 0;
                int i18 = 0;
                while (i17 < 11) {
                    int i19 = i18;
                    int i20 = i6;
                    int i21 = 0;
                    while (i21 < 11) {
                        int i22 = i20;
                        int i23 = i12;
                        int i24 = i21;
                        int i25 = i17;
                        int i26 = i15;
                        int i27 = i5;
                        bitmap2.getPixels(iArr3, 0, 1, i13 + (((width2 - 1) * i21) / 10), i10 + (((height2 - 1) * i17) / 10), 1, 1);
                        int i28 = i19 + 1;
                        if (difference(iArr[i19], iArr3[0]) <= 2) {
                            i16++;
                        }
                        i21 = i24 + 1;
                        i19 = i28;
                        i15 = i26;
                        i5 = i27;
                        i12 = i23;
                        i20 = i22;
                        i17 = i25;
                    }
                    i17++;
                    i6 = i20;
                    i18 = i19;
                }
                if (i16 > i5) {
                    i6 = i5;
                    i7 = i10;
                    i11 = i13;
                    i5 = i16;
                } else if (i16 > i6) {
                    i6 = i16;
                }
                i12++;
                i8 = i15;
                width = i14;
            }
            i8++;
            z = z2;
            i9 = i11;
        }
        if (i5 < i2 * 0.9f || i6 >= i5 - 3) {
            return null;
        }
        return new int[]{i9, i7};
    }

    static Gainmap copy(Gainmap gainmap, Bitmap bitmap) {
        Gainmap gainmap2 = new Gainmap(bitmap);
        float[] ratioMin = gainmap.getRatioMin();
        gainmap2.setRatioMin(ratioMin[0], ratioMin[1], ratioMin[2]);
        float[] ratioMax = gainmap.getRatioMax();
        gainmap2.setRatioMax(ratioMax[0], ratioMax[1], ratioMax[2]);
        float[] gamma = gainmap.getGamma();
        gainmap2.setGamma(gamma[0], gamma[1], gamma[2]);
        float[] epsilonSdr = gainmap.getEpsilonSdr();
        gainmap2.setEpsilonSdr(epsilonSdr[0], epsilonSdr[1], epsilonSdr[2]);
        float[] epsilonHdr = gainmap.getEpsilonHdr();
        gainmap2.setEpsilonHdr(epsilonHdr[0], epsilonHdr[1], epsilonHdr[2]);
        gainmap2.setMinDisplayRatioForHdrTransition(gainmap.getMinDisplayRatioForHdrTransition());
        gainmap2.setDisplayRatioForFullHdr(gainmap.getDisplayRatioForFullHdr());
        return gainmap2;
    }

    static boolean repair(Bitmap bitmap, Bitmap bitmap2) {
        if (!valid(bitmap)) {
            return false;
        }
        if (bitmap == bitmap2) {
            return true;
        }
        if (valid(bitmap2) && bitmap2.getGainmap() != bitmap.getGainmap()) {
            return true;
        }
        int[] iArrLocate = locate(bitmap, bitmap2);
        if (iArrLocate == null) {
            return false;
        }
        return mapped(bitmap, bitmap2, iArrLocate[0], iArrLocate[1]);
    }

    static boolean knownCopy(Bitmap bitmap, Bitmap bitmap2) {
        return valid(bitmap) && bitmap.getWidth() == bitmap2.getWidth() && bitmap.getHeight() == bitmap2.getHeight() && mapped(bitmap, bitmap2, 0, 0);
    }

    /* JADX WARN: Code duplicated, block: B:34:0x01c0  */
    /* JADX WARN: Multi-variable type inference failed */
    /* JADX WARN: Type inference failed for: r11v11 */
    /* JADX WARN: Type inference failed for: r11v5 */
    /* JADX WARN: Type inference failed for: r11v6, types: [int] */
    /* JADX WARN: Type inference failed for: r15v12 */
    /* JADX WARN: Type inference failed for: r15v4 */
    /* JADX WARN: Type inference failed for: r15v5, types: [int] */
    /* JADX WARN: Type inference failed for: r1v11, types: [int] */
    private static boolean mapped(Bitmap bitmap, Bitmap bitmap2, int i, int i2) throws Throwable {
        Gainmap gainmap;
        int i3;
        int i4;
        int i5;
        int width = bitmap2.getWidth();
        int height = bitmap2.getHeight();
        int width2 = bitmap.getWidth();
        int height2 = bitmap.getHeight();
        Gainmap gainmap2 = bitmap.getGainmap();
        Bitmap gainmapContents = gainmap2.getGainmapContents();
        int width3 = gainmapContents.getWidth();
        int height3 = gainmapContents.getHeight();
        boolean z = false;
        if (((long) width3) * ((long) height3) > 1048576) {
            return false;
        }
        float fMin = Math.min(1.0f, 384.0f / Math.max(width, height));
        int iMax = Math.max(1, Math.round(width * fMin));
        int iMax2 = Math.max(1, Math.round(height * fMin));
        int[] iArr = new int[width3 * height3];
        gainmapContents.getPixels(iArr, 0, width3, 0, 0, width3, height3);
        int i6 = iMax * iMax2;
        int[] iArr2 = new int[i6];
        Arrays.fill(iArr2, -16777216);
        boolean[] zArr = new boolean[i6];
        int[] iArr3 = new int[width2];
        int i7 = -16777216;
        int[] iArr4 = new int[width2];
        boolean z2 = true;
        int i8 = 0;
        while (i8 < height2) {
            int i9 = height2;
            Gainmap gainmap3 = gainmap2;
            int i10 = width3;
            int i11 = height3;
            int i12 = iMax2;
            int[] iArr5 = iArr2;
            int i13 = iMax;
            int[] iArr6 = iArr4;
            boolean z3 = z2;
            int i14 = i7;
            boolean[] zArr2 = zArr;
            int i15 = i8;
            bitmap.getPixels(iArr3, 0, width2, 0, i15, width2, 1);
            int i16 = i2 + i15;
            int i17 = width2;
            bitmap2.getPixels(iArr6, 0, i17, i, i16, width2, 1);
            int iMin = Math.min(i12 - 1, (int) ((((long) i16) * ((long) i12)) / ((long) height)));
            int i18 = 0;
            while (i18 < i17) {
                if (difference(iArr3[i18], iArr6[i18]) > 2) {
                    i5 = iMin;
                    zArr2[(i5 * i13) + Math.min(i13 - 1, (int) ((((long) (i + i18)) * ((long) i13)) / ((long) width)))] = z3;
                } else {
                    i5 = iMin;
                }
                i18++;
                iArr6 = iArr6;
                iMin = i5;
            }
            i8 = i15 + 1;
            height2 = i9;
            iArr4 = iArr6;
            iMax = i13;
            iMax2 = i12;
            width3 = i10;
            gainmap2 = gainmap3;
            z = false;
            iArr2 = iArr5;
            zArr = zArr2;
            i7 = i14;
            z2 = z3;
            width2 = i17;
            height3 = i11;
        }
        for (?? r11 = z; r11 < iMax2; r11++) {
            for (?? r15 = z; r15 < iMax; r15++) {
                int i19 = iMax;
                double d = (double) r15;
                double d2 = width;
                double d3 = d * d2;
                int[] iArr7 = iArr2;
                double d4 = i19;
                double d5 = d3 / d4;
                double d6 = ((d + 1.0d) * d2) / d4;
                double d7 = (double) r11;
                double d8 = height;
                double d9 = d7 * d8;
                double d10 = iMax2;
                double d11 = d9 / d10;
                double d12 = ((d7 + 1.0d) * d8) / d10;
                double d13 = i;
                if (d5 >= d13) {
                    gainmap = gainmap2;
                    i4 = iMax2;
                    if (d6 <= i + width2) {
                        double d14 = i2;
                        if (d11 < d14 || d12 > i2 + height2) {
                            i3 = width3;
                        } else {
                            ?? r1 = (r11 * i19) + r15;
                            if (zArr[r1]) {
                                i3 = width3;
                            } else {
                                double d15 = (((((d5 + d6) * 0.5d) - d13) * ((double) width3)) / ((double) width2)) - 0.5d;
                                double d16 = (((((d11 + d12) * 0.5d) - d14) * ((double) height3)) / ((double) height2)) - 0.5d;
                                int i20 = width3 - 1;
                                int iMax3 = Math.max(0, Math.min(i20, (int) Math.floor(d15)));
                                int i21 = height3 - 1;
                                int iMax4 = Math.max(0, Math.min(i21, (int) Math.floor(d16)));
                                int iMin2 = Math.min(i20, iMax3 + 1);
                                int iMin3 = Math.min(i21, iMax4 + 1);
                                i3 = width3;
                                double dMax = Math.max(0.0d, Math.min(1.0d, d15 - ((double) iMax3)));
                                double dMax2 = Math.max(0.0d, Math.min(1.0d, d16 - ((double) iMax4)));
                                int i22 = iMax4 * i3;
                                double d17 = 1.0d - dMax;
                                double d18 = ((((double) (iArr[i22 + iMax3] & 255)) * d17) + (((double) (iArr[i22 + iMin2] & 255)) * dMax)) * (1.0d - dMax2);
                                int i23 = iMin3 * i3;
                                int iRound = (int) Math.round(d18 + (((((double) (iArr[iMax3 + i23] & 255)) * d17) + (((double) (iArr[i23 + iMin2] & 255)) * dMax)) * dMax2));
                                iArr7[r1] = iRound | (iRound << 16) | i7 | (iRound << 8);
                            }
                        }
                    } else {
                        i3 = width3;
                    }
                } else {
                    gainmap = gainmap2;
                    i3 = width3;
                    i4 = iMax2;
                }
                i = i;
                iMax = i19;
                gainmap2 = gainmap;
                height2 = height2;
                iArr2 = iArr7;
                width3 = i3;
                height3 = height3;
                iMax2 = i4;
                z = false;
            }
        }
        Bitmap bitmapCreateBitmap = Bitmap.createBitmap(iArr2, iMax, iMax2, Bitmap.Config.ARGB_8888);
        try {
            bitmap2.setGainmap(copy(gainmap2, bitmapCreateBitmap));
            try {
                return valid(bitmap2);
            } catch (Throwable th) {
                th = th;
                z = z2;
                if (!z) {
                    bitmapCreateBitmap.recycle();
                }
                throw th;
            }
        } catch (Throwable th2) {
            th = th2;
        }
    }

    static void clear(Bitmap bitmap) {
        if (bitmap == null || bitmap.isRecycled()) {
            return;
        }
        bitmap.setGainmap(null);
    }
}
