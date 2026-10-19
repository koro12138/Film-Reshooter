package com.codex.cameralook;

import android.graphics.Bitmap;
import android.graphics.Gainmap;
import android.os.Build;
import android.util.Log;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class ToneHdr {
    ToneHdr() {
    }

    private static final class Api34 {
        private Api34() {
        }

        static void clear(Bitmap bitmap) {
            try {
                bitmap.setGainmap(null);
            } catch (RuntimeException e) {
                Log.w("CameraLookHDR", "Gain map clear", e);
            }
        }

        static void generate(Bitmap bitmap) throws Exception {
            clear(bitmap);
            float fMin = Math.min(1.0f, 384.0f / Math.max(bitmap.getWidth(), bitmap.getHeight()));
            int iMax = Math.max(1, Math.round(bitmap.getWidth() * fMin));
            int iMax2 = Math.max(1, Math.round(bitmap.getHeight() * fMin));
            Gainmap gainmap = new Gainmap(Bitmap.createBitmap(GainPlane.fromPixels((int[]) ToneReflect.call(Class.forName("com.codex.fullm9.NativeM9"), "hdrSample", new Class[]{Bitmap.class, Integer.TYPE, Integer.TYPE}, bitmap, Integer.valueOf(iMax), Integer.valueOf(iMax2)), iMax, iMax2), iMax, iMax2, Bitmap.Config.ARGB_8888));
            gainmap.setRatioMin(1.0f, 1.0f, 1.0f);
            gainmap.setRatioMax(2.0f, 2.0f, 2.0f);
            gainmap.setGamma(1.0f, 1.0f, 1.0f);
            gainmap.setEpsilonSdr(0.0f, 0.0f, 0.0f);
            gainmap.setEpsilonHdr(0.0f, 0.0f, 0.0f);
            gainmap.setMinDisplayRatioForHdrTransition(1.0f);
            gainmap.setDisplayRatioForFullHdr(2.0f);
            bitmap.setGainmap(gainmap);
        }
    }

    static void finish(Bitmap bitmap) {
        String str;
        NightHighlights.prepare(bitmap);
        if (Build.VERSION.SDK_INT < 34) {
            return;
        }
        try {
            Api34.generate(bitmap);
            NightHighlights.limit(bitmap);
        } catch (Exception e) {
            e = e;
            Api34.clear(bitmap);
            str = "Keep SDR after HDR failure";
            Log.w("CameraLookHDR", str, e);
        } catch (LinkageError e2) {
            Log.w("CameraLookHDR", "Keep SDR without HDR API", e2);
        } catch (OutOfMemoryError e3) {
            e = e3;
            Api34.clear(bitmap);
            str = "Keep SDR at memory limit";
            Log.w("CameraLookHDR", str, e);
        }
    }
}
