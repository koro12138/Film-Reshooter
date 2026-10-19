package com.codex.cameralook;

import android.content.Context;
import android.graphics.Bitmap;
import android.hardware.camera2.CaptureResult;
import android.util.Log;
import android.util.Size;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
public final class ToneEngine {
    private static ToneTable cached;
    private static final Object LOCK = new Object();
    private static int cachedId = -1;

    static void recycle(Bitmap bitmap) {
        if (bitmap == null || bitmap.isRecycled()) {
            return;
        }
        bitmap.recycle();
    }

    static ToneTable table(Context context, int i) throws IOException {
        if (cachedId == i && cached != null) {
            return cached;
        }
        Throwable th = null;
        try {
            InputStream inputStreamOpen = context.getAssets().open("cameralook/tone-" + i + ".lut");
            try {
                ToneTable toneTable = new ToneTable(inputStreamOpen);
                if (inputStreamOpen != null) {
                    inputStreamOpen.close();
                }
                cached = toneTable;
                cachedId = i;
                return toneTable;
            } catch (Throwable th2) {
                if (inputStreamOpen == null) {
                    throw th2;
                }
                inputStreamOpen.close();
                throw th2;
            }
        } catch (Throwable th3) {
            if (0 == 0) {
                throw th3;
            }
            if (null != th3) {
                th.addSuppressed(th3);
            }
            throw null;
        }
    }

    static void tone(Bitmap bitmap, ToneTable toneTable, ToneMath.Params params, int i) {
        ToneMath.Params params2 = params;
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int[] iArr = new int[width];
        float[] fArr = new float[3];
        int i2 = 0;
        int i3 = 0;
        while (i3 < height) {
            int i4 = height;
            int i5 = width;
            int i6 = i2;
            bitmap.getPixels(iArr, 0, i5, 0, i3, i5, 1);
            for (int i7 = i6; i7 < i5; i7++) {
                iArr[i7] = ToneMath.toned(iArr[i7], toneTable, params, fArr);
            }
            bitmap.setPixels(iArr, 0, i5, 0, i3, i5, 1);
            i3++;
            params2 = params;
            i2 = i6;
            height = i4;
            width = i5;
        }
        if (params2.grain == 0.0f && params2.vignette == 0.0f && params2.clarity == 0.0f) {
            return;
        }
        int[][] iArr2 = new int[3][];
        iArr2[i2] = new int[width];
        int i8 = 1;
        iArr2[1] = new int[width];
        iArr2[2] = new int[width];
        int i9 = width;
        bitmap.getPixels(iArr2[i2], 0, width, 0, 0, i9, 1);
        System.arraycopy(iArr2[i2], i2, iArr2[1], i2, width);
        bitmap.getPixels(iArr2[2], 0, width, 0, Math.min(1, height - 1), i9, 1);
        int i10 = i2;
        while (i10 < height) {
            int[] iArr3 = iArr;
            int i11 = i2;
            while (i11 < width) {
                int[][] iArr4 = iArr2;
                int[] iArr5 = iArr3;
                int i12 = i10;
                int iMax = Math.max(i2, i11 - 1);
                int i13 = i11 + 1;
                int iMin = Math.min(width - 1, i13);
                int i14 = i2;
                float fLuma = 0.0f;
                while (i14 < 3) {
                    int[][] iArr6 = iArr4;
                    int i15 = height;
                    int i16 = i8;
                    int i17 = width;
                    int i18 = i2;
                    fLuma += (ToneMath.luma(iArr6[i14][iMax]) + (ToneMath.luma(iArr6[i14][i11]) * 2.0f) + ToneMath.luma(iArr6[i14][iMin])) * (i14 == i16 ? 2 : i16);
                    i14++;
                    params2 = params;
                    i2 = i18;
                    i8 = i16;
                    height = i15;
                    width = i17;
                    iArr4 = iArr6;
                }
                int[][] iArr7 = iArr4;
                int i19 = width;
                iArr5[i11] = ToneMath.film(iArr4[i8][i11], i11, i12, i19, height, i, params2, fLuma / 16.0f);
                params2 = params;
                i10 = i12;
                i11 = i13;
                i2 = i2;
                i8 = i8;
                iArr2 = iArr7;
                iArr3 = iArr5;
                width = i19;
            }
            bitmap.setPixels(iArr3, 0, width, 0, i10, width, 1);
            int[][] iArr8 = iArr2;
            int[] iArr9 = iArr3;
            int i20 = i10;
            int[] iArr10 = iArr8[i2];
            iArr8[i2] = iArr8[i8];
            iArr8[i8] = iArr8[2];
            iArr8[2] = iArr10;
            int i21 = i20 + 2;
            if (i21 < height) {
                bitmap.getPixels(iArr8[2], 0, width, 0, i21, width, 1);
            } else {
                System.arraycopy(iArr8[i8], i2, iArr8[2], i2, width);
            }
            i10 = i20 + 1;
            iArr2 = iArr8;
            iArr = iArr9;
        }
    }

    static byte[] metadata(byte[] bArr, byte[] bArr2, int i, int i2) throws Exception {
        return ToneExif.upright((byte[]) ToneReflect.call(Class.forName("com.codex.leicaapp.JpegMetadata"), "copyExif", new Class[]{byte[].class, byte[].class, Boolean.TYPE, Integer.TYPE, Integer.TYPE, Boolean.TYPE}, bArr, bArr2, true, Integer.valueOf(i), Integer.valueOf(i2), true));
    }

    static byte[] sidecar(byte[] bArr, int i, int i2) throws Exception {
        Bitmap bitmapCreateBitmap = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888);
        try {
            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            if (!bitmapCreateBitmap.compress(Bitmap.CompressFormat.JPEG, 97, byteArrayOutputStream)) {
                throw new IOException("Metadata JPEG");
            }
            byte[] bArrMetadata = metadata(bArr, byteArrayOutputStream.toByteArray(), i, i2);
            bitmapCreateBitmap.recycle();
            return bArrMetadata;
        } catch (Throwable th) {
            bitmapCreateBitmap.recycle();
            throw th;
        }
    }

    static Object result(Object obj) {
        Object objField = ToneReflect.field(obj, "f");
        Object objField2 = ToneReflect.field(objField, "b");
        if (!(objField2 instanceof CaptureResult)) {
            objField2 = ToneReflect.field(objField, "c");
        }
        if (!(objField2 instanceof CaptureResult)) {
            objField2 = ToneReflect.field(obj, "legendaryPreviewResult");
        }
        if (objField2 instanceof CaptureResult) {
            return objField2;
        }
        return null;
    }

    static void denoise(Bitmap bitmap) {
        String str;
        try {
            ToneReflect.call(Class.forName("com.codex.fullm9.NativeM9"), "outputDenoise", new Class[]{Bitmap.class, Integer.TYPE}, bitmap, 2);
        } catch (Exception e) {
            e = e;
            str = "Input denoise skipped";
            Log.w("CameraLook", str, e);
        } catch (LinkageError e2) {
            e = e2;
            str = "Denoise unavailable";
            Log.w("CameraLook", str, e);
        } catch (OutOfMemoryError e3) {
            e = e3;
            str = "Denoise memory";
            Log.w("CameraLook", str, e);
        }
    }

    /* JADX WARN: Code duplicated, block: B:79:0x01d8 A[Catch: all -> 0x01df, TryCatch #10 {, blocks: (B:10:0x0017, B:36:0x0180, B:38:0x0185, B:39:0x0188, B:40:0x018b, B:77:0x01d3, B:79:0x01d8, B:80:0x01db, B:81:0x01de), top: B:89:0x0017 }] */
    public static byte[] render(Context context, byte[] bArr, Object obj, int[] iArr) throws Exception {
        Bitmap bitmapDecode;
        Bitmap bitmap;
        Bitmap bitmap2;
        Bitmap bitmap3;
        byte[] bArrMetadata;
        if (iArr == null || iArr.length == 0 || !ToneCatalog.valid(iArr[0])) {
            throw new IllegalArgumentException("New tone selection");
        }
        synchronized (LOCK) {
            ToneState toneState = new ToneState(obj);
            long jNanoTime = System.nanoTime();
            try {
                if (bArr != null) {
                    try {
                        if (bArr.length >= 4 && (bArr[0] & 255) == 255 && (bArr[1] & 255) == 216) {
                            int i = iArr[0] - 16;
                            ToneTable toneTableTable = table(context, i);
                            bitmapDecode = ToneInput.decode(bArr, ToneInput.orientation(bArr));
                            try {
                                int width = bitmapDecode.getWidth();
                                int height = bitmapDecode.getHeight();
                                denoise(bitmapDecode);
                                tone(bitmapDecode, toneTableTable, ToneCatalog.params(i), i);
                                ToneHdr.finish(bitmapDecode);
                                byte[] bArr2 = (byte[]) ToneReflect.call(Class.forName("com.codex.lmoments.LeicaMark"), "mark", new Class[]{byte[].class}, sidecar(bArr, width, height));
                                bitmap2 = obj == null ? bitmapDecode : (Bitmap) ToneReflect.call(Class.forName("com.codex.leicaapp.OriginalWatermark"), "apply", new Class[]{Bitmap.class, Object.class, byte[].class, CaptureResult.class}, bitmapDecode, obj, bArr2, result(obj));
                                try {
                                    if (bitmap2 == null) {
                                        throw new IOException("Watermark unavailable");
                                    }
                                    ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                                    if (!bitmap2.compress(Bitmap.CompressFormat.JPEG, 98, byteArrayOutputStream)) {
                                        throw new IOException("Final JPEG encoding failed");
                                    }
                                    bArrMetadata = metadata(bArr2, byteArrayOutputStream.toByteArray(), bitmap2.getWidth(), bitmap2.getHeight());
                                    if (bArrMetadata.length < 4 || (bArrMetadata[0] & 255) != 255 || (bArrMetadata[1] & 255) != 216) {
                                        throw new IOException("Invalid final JPEG");
                                    }
                                    if (obj != null) {
                                        ToneReflect.put(ToneReflect.field(obj, "b"), "b", new Size(bitmap2.getWidth(), bitmap2.getHeight()));
                                        ToneReflect.call(Class.forName("com.codex.lmport.MomentBridge"), "uprightSource", new Class[]{Object.class, Integer.TYPE, Integer.TYPE}, ToneReflect.field(obj, "a"), Integer.valueOf(bitmap2.getWidth()), Integer.valueOf(bitmap2.getHeight()));
                                        ToneState.commitJpeg(obj, bArrMetadata);
                                    }
                                    Log.i("CameraLook", String.valueOf(ToneCatalog.name(iArr[0])) + " photo=" + width + "x" + height + " output=" + bitmap2.getWidth() + "x" + bitmap2.getHeight() + " seconds=" + ((System.nanoTime() - jNanoTime) / 1.0E9d));
                                    WatermarkLast.clear();
                                    if (bitmap2 != bitmapDecode) {
                                        recycle(bitmap2);
                                    }
                                    recycle(bitmapDecode);
                                } catch (Error e) {
                                    e = e;
                                    bitmap3 = bitmapDecode;
                                    toneState.restore();
                                    throw e;
                                } catch (Exception e2) {
                                    e = e2;
                                    toneState.restore();
                                    throw e;
                                } catch (Throwable th) {
                                    th = th;
                                    bitmap = bitmap2;
                                    WatermarkLast.clear();
                                    if (bitmap != bitmapDecode) {
                                        recycle(bitmap);
                                    }
                                    recycle(bitmapDecode);
                                    throw th;
                                }
                            } catch (Error e3) {
                                e = e3;
                                bitmap3 = bitmapDecode;
                                bitmap2 = null;
                                toneState.restore();
                                throw e;
                            } catch (Exception e4) {
                                e = e4;
                                toneState.restore();
                                throw e;
                            } catch (Throwable th2) {
                                th = th2;
                                bitmap = null;
                                WatermarkLast.clear();
                                if (bitmap != bitmapDecode) {
                                    recycle(bitmap);
                                }
                                recycle(bitmapDecode);
                                throw th;
                            }
                        }
                    } catch (Error e5) {
                        e = e5;
                        bitmap3 = null;
                    } catch (Exception e6) {
                        e = e6;
                    } catch (Throwable th3) {
                        th = th3;
                        bitmap = null;
                        bitmapDecode = null;
                    }
                }
                throw new IOException("New tones require camera JPEG input");
            } catch (Throwable th4) {
                th = th4;
                bitmapDecode = bitmap3;
            }
        }
        return bArrMetadata;
    }
}
