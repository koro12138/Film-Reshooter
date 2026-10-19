package com.codex.cameralook;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class ToneExif {
    ToneExif() {
    }

    static long read(byte[] bArr, int i, int i2, boolean z) {
        long j = 0;
        for (int i3 = 0; i3 < i2; i3++) {
            j = (j << 8) | ((long) (bArr[(z ? (i2 - 1) - i3 : i3) + i] & 255));
        }
        return j;
    }

    /* JADX WARN: Type inference failed for: r7v18 */
    /* JADX WARN: Type inference failed for: r7v19, types: [boolean, int] */
    /* JADX WARN: Type inference failed for: r7v22 */
    static byte[] upright(byte[] bArr) {
        byte[] bArrSrgb = srgb(bArr);
        if (bArrSrgb.length < 4 || (bArrSrgb[0] & 255) != 255 || (bArrSrgb[1] & 255) != 216) {
            return bArrSrgb;
        }
        int i = 2;
        while (i + 3 < bArrSrgb.length) {
            int i2 = i + 1;
            if ((bArrSrgb[i] & 255) != 255) {
                return bArrSrgb;
            }
            while (i2 < bArrSrgb.length && (bArrSrgb[i2] & 255) == 255) {
                i2++;
            }
            if (i2 >= bArrSrgb.length) {
                return bArrSrgb;
            }
            i = i2 + 1;
            int i3 = bArrSrgb[i2] & 255;
            if (i3 == 218 || i3 == 217) {
                return bArrSrgb;
            }
            if (i3 != 1 && (i3 < 208 || i3 > 215)) {
                int i4 = i + 2;
                if (i4 > bArrSrgb.length) {
                    return bArrSrgb;
                }
                int i5 = ((bArrSrgb[i] & 255) * 256) + (bArrSrgb[i + 1] & 255);
                if (i5 < 2 || i5 > bArrSrgb.length - i) {
                    return bArrSrgb;
                }
                i += i5;
                if (i3 == 225 && i5 >= 16 && bArrSrgb[i4] == 69 && bArrSrgb[i4 + 1] == 120 && bArrSrgb[i4 + 2] == 105 && bArrSrgb[i4 + 3] == 102 && bArrSrgb[i4 + 4] == 0 && bArrSrgb[i4 + 5] == 0) {
                    int i6 = i4 + 6;
                    ?? r7 = (bArrSrgb[i6] == 73 && bArrSrgb[i6 + 1] == 73) ? 1 : 0;
                    if ((r7 == 0 && (bArrSrgb[i6] != 77 || bArrSrgb[i6 + 1] != 77)) || read(bArrSrgb, i6 + 2, 2, r7) != 42) {
                        return bArrSrgb;
                    }
                    long j = read(bArrSrgb, i6 + 4, 4, r7);
                    if (j < 8 || j > (i - i6) - 2) {
                        return bArrSrgb;
                    }
                    int i7 = i6 + ((int) j);
                    long j2 = read(bArrSrgb, i7, 2, r7);
                    if (j2 > ((i - i7) - 2) / 12) {
                        return bArrSrgb;
                    }
                    for (int i8 = 0; i8 < j2; i8++) {
                        int i9 = i7 + 2 + (i8 * 12);
                        if (read(bArrSrgb, i9, 2, r7) == 274 && read(bArrSrgb, i9 + 2, 2, r7) == 3 && read(bArrSrgb, i9 + 4, 4, r7) == 1) {
                            byte[] bArr2 = (byte[]) bArrSrgb.clone();
                            bArr2[i9 + 8] = (byte) r7;
                            bArr2[i9 + 9] = (byte) (r7 ^ 1);
                            return srgb(bArr2);
                        }
                    }
                }
            }
        }
        return srgb(bArrSrgb);
    }

    /* JADX WARN: Code duplicated, block: B:76:0x00e0  */
    static byte[] srgb(byte[] bArr) {
        int i;
        int i2;
        if (bArr.length < 4 || (bArr[0] & 255) != 255 || (bArr[1] & 255) != 216) {
            return bArr;
        }
        byte[] bArr2 = (byte[]) bArr.clone();
        int i3 = 2;
        while (i3 + 3 < bArr2.length) {
            int i4 = i3 + 1;
            if ((bArr2[i3] & 255) == 255) {
                while (i4 < bArr2.length && (bArr2[i4] & 255) == 255) {
                    i4++;
                }
                if (i4 < bArr2.length) {
                    i3 = i4 + 1;
                    int i5 = bArr2[i4] & 255;
                    if (i5 != 218 && i5 != 217) {
                        if (i5 != 1 && (i5 < 208 || i5 > 215)) {
                            int i6 = i3 + 2;
                            if (i6 > bArr2.length || (i = ((bArr2[i3] & 255) * 256) + (bArr2[i3 + 1] & 255)) < 2 || i > bArr2.length - i3) {
                                break;
                            }
                            int i7 = i3 + i;
                            if (i5 == 225 && i >= 16 && bArr2[i6] == 69 && bArr2[i6 + 1] == 120 && bArr2[i6 + 2] == 105 && bArr2[i6 + 3] == 102 && bArr2[i6 + 4] == 0 && bArr2[i6 + 5] == 0) {
                                int i8 = i6 + 6;
                                boolean z = bArr2[i8] == 73 && bArr2[i8 + 1] == 73;
                                if ((z || (bArr2[i8] == 77 && bArr2[i8 + 1] == 77)) && read(bArr2, i8 + 2, 2, z) == 42) {
                                    i2 = i7;
                                    patchIfd(bArr2, i8, i2, read(bArr2, i8 + 4, 4, z), z, 0);
                                } else {
                                    i2 = i7;
                                }
                            } else {
                                i2 = i7;
                            }
                            i3 = i2;
                        }
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        return bArr2;
    }

    /* JADX WARN: Type inference failed for: r5v1, types: [boolean, int] */
    /* JADX WARN: Type inference failed for: r5v2 */
    /* JADX WARN: Type inference failed for: r5v3 */
    private static void patchIfd(byte[] bArr, int i, int i2, long j, boolean z, int i3) {
        ?? r5;
        byte[] bArr2 = bArr;
        boolean z2 = z;
        int i4 = 2;
        if (i3 > 2 || j < 8 || j > (i2 - i) - 2) {
            return;
        }
        int i5 = i + ((int) j);
        int i6 = (int) read(bArr2, i5, 2, z2);
        if (i6 > ((i2 - i5) - 2) / 12) {
            return;
        }
        int i7 = 0;
        while (i7 < i6) {
            int i8 = i5 + 2 + (i7 * 12);
            int i9 = (int) read(bArr2, i8, i4, r5);
            int i10 = (int) read(bArr2, i8 + 2, i4, r5);
            long j2 = read(bArr2, i8 + 4, 4, r5);
            if (i9 == 40961 && i10 == 3 && j2 == 1) {
                r5 = z2;
                bArr2[i8 + 8] = (byte) r5;
                bArr2[i8 + 9] = (byte) (r5 ^ 1);
            }
            r5 = z2;
            r5 = z2;
            r5 = z2;
            if (i9 == 34665 && i10 == 4 && j2 == 1) {
                patchIfd(bArr2, i, i2, read(bArr2, i8 + 8, 4, r5), r5, i3 + 1);
            }
            i7++;
            i4 = 2;
            bArr2 = bArr;
            r5 = z;
        }
        r5 = z2;
    }
}
