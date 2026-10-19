package com.codex.fullm9;

import android.graphics.Bitmap;
import android.os.Build;
import android.util.Log;
import com.codex.lmport.DenoiseFlow;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes17.dex */
public final class OutputQuality {
    private static final ThreadLocal<Integer> STYLE = new ThreadLocal<>();

    static void begin(int[] iArr) {
        ThreadLocal<Integer> threadLocal = STYLE;
        int i = 0;
        if (iArr != null && iArr.length > 0) {
            i = iArr[0];
        }
        threadLocal.set(Integer.valueOf(i));
    }

    static void end() {
        STYLE.remove();
    }

    static void removeSourceHdr(Bitmap bitmap) {
        if (Build.VERSION.SDK_INT < 34 || bitmap == null || bitmap.isRecycled()) {
            return;
        }
        Api34.clear(bitmap);
    }

    public static Bitmap prepare(Bitmap bitmap) {
        removeSourceHdr(bitmap);
        return DenoiseFlow.prepareLegacy(bitmap);
    }

    /* JADX WARN: Code duplicated, block: B:33:0x0067  */
    public static Bitmap finish(Bitmap bitmap) {
        removeSourceHdr(bitmap);
        Bitmap bitmapFinishLegacy = DenoiseFlow.finishLegacy(bitmap);
        Integer num = STYLE.get();
        if (bitmapFinishLegacy == null || num == null || num.intValue() < 1 || num.intValue() >= 8) {
            return bitmapFinishLegacy;
        }
        Bitmap bitmapCopy = null;
        try {
            if (!(bitmapFinishLegacy.isMutable() && bitmapFinishLegacy.getConfig() == Bitmap.Config.ARGB_8888) && (bitmapCopy = bitmapFinishLegacy.copy(Bitmap.Config.ARGB_8888, true)) == null) {
                return bitmapFinishLegacy;
            }
            NativeM9.outputDenoise(bitmapCopy == null ? bitmapFinishLegacy : bitmapCopy, num.intValue());
            if (bitmapCopy == null) {
                return bitmapFinishLegacy;
            }
            bitmapFinishLegacy.recycle();
            return bitmapCopy;
        } catch (Exception e) {
            Log.w("M9Quality", "Keep original denoise output", e);
            if (bitmapCopy != null) {
                bitmapCopy.recycle();
            }
            return bitmapFinishLegacy;
        } catch (LinkageError e2) {
            Log.w("M9Quality", "Residual filter unavailable", e2);
            if (bitmapCopy != null) {
                bitmapCopy.recycle();
            }
            return bitmapFinishLegacy;
        } catch (OutOfMemoryError e3) {
            Log.w("M9Quality", "Residual filter memory limit", e3);
            if (bitmapCopy != null) {
                bitmapCopy.recycle();
            }
            return bitmapFinishLegacy;
        }
    }

    private static final class Api34 {
        private Api34() {
        }

        static void clear(Bitmap bitmap) {
            try {
                bitmap.setGainmap(null);
            } catch (RuntimeException e) {
                Log.w("M9Quality", "Source HDR clear", e);
            }
        }
    }
}
