package com.codex.lmoments;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ColorSpace;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.os.SystemClock;
import com.codex.lmport.DenoiseFlow;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes15.dex */
public final class LegendaryPostProcessor {
    private static String cachePath;
    private static String m3ModelPath;
    private static String m9ModelPath;
    private static boolean modelsReady = false;
    private static String monopanRunner;
    private static String styleModels;
    private static String styleRunner;

    private static native boolean applyMonochrome(Bitmap bitmap, String str, String str2);

    private static native boolean applyOriginalFilter(Bitmap bitmap, String str, float f, float f2, float f3, float f4);

    private static native boolean applyStyle(Bitmap bitmap, String str, String str2, String str3, int i, int i2, int i3);

    private static native boolean applyWarmOriginalFilter(Bitmap bitmap, String str, float f, float f2, float f3, float f4, float f5, float f6, float f7);

    static {
        System.loadLibrary("zxicamodelembed");
    }

    private LegendaryPostProcessor() {
    }

    public static synchronized void ensureModels(Context ctx) {
        if (modelsReady) {
            return;
        }
        try {
            String nativeDir = ctx.getApplicationInfo().nativeLibraryDir;
            styleRunner = nativeDir + "/libzxyletrans_runner.so";
            File v4 = new File(ctx.getFilesDir(), "lm_leica-v4");
            if (!new File(v4, ".ready").isFile()) {
                copyTree(ctx, "lm_leica-v4", v4);
                new File(v4, ".ready").createNewFile();
            }
            styleModels = v4.getAbsolutePath();
            monopanRunner = nativeDir + "/libzxnopan_runner.so";
            cachePath = ctx.getCacheDir().getAbsolutePath();
            m3ModelPath = copyAsset(ctx, "lm_leica_filter_param_m3.bin");
            m9ModelPath = copyAsset(ctx, "lm_leica_filter_param_m9_snapshot.bin");
            modelsReady = true;
        } catch (Throwable th) {
        }
    }

    private static String copyAsset(Context ctx, String name) throws IOException {
        File f = new File(ctx.getFilesDir(), name);
        if (f.exists() && f.length() > 4096) {
            return f.getAbsolutePath();
        }
        InputStream in = ctx.getAssets().open(name);
        FileOutputStream out = new FileOutputStream(f);
        byte[] buf = new byte[32768];
        while (true) {
            int n = in.read(buf);
            if (n <= 0) {
                out.close();
                in.close();
                return f.getAbsolutePath();
            }
            out.write(buf, 0, n);
        }
    }

    private static void copyTree(Context ctx, String assetPath, File dest) throws IOException {
        String[] names = ctx.getAssets().list(assetPath);
        if (names != null && names.length > 0) {
            dest.mkdirs();
            for (String n : names) {
                copyTree(ctx, assetPath + "/" + n, new File(dest, n));
            }
            return;
        }
        File parent = dest.getParentFile();
        if (parent != null) {
            parent.mkdirs();
        }
        InputStream in = ctx.getAssets().open(assetPath);
        FileOutputStream out = new FileOutputStream(dest);
        byte[] buf = new byte[65536];
        while (true) {
            int n2 = in.read(buf);
            if (n2 > 0) {
                out.write(buf, 0, n2);
            } else {
                out.close();
                in.close();
                return;
            }
        }
    }

    public static byte[] processM3(Context ctx, byte[] jpeg) {
        ensureModels(ctx);
        if (m3ModelPath == null) {
            return null;
        }
        try {
            Bitmap bmp = decode(jpeg);
            if (bmp == null) {
                return null;
            }
            float time = SystemClock.uptimeMillis() % 60000;
            boolean ok = applyOriginalFilter(bmp, m3ModelPath, 200.0f, 5500.0f, 1.0f, time);
            if (!ok) {
                DenoiseFlow.recycle(bmp);
                return null;
            }
            applyMonochrome(bmp, monopanRunner, cachePath);
            byte[] out = encode(bmp, jpeg);
            DenoiseFlow.recycle(bmp);
            return out;
        } catch (Throwable th) {
            return null;
        }
    }

    public static byte[] processM9(Context ctx, byte[] jpeg) {
        ensureModels(ctx);
        if (m9ModelPath == null || styleModels == null) {
            return null;
        }
        try {
            Bitmap bmp = decode(jpeg);
            if (bmp == null) {
                return null;
            }
            int rotation = readOrientation(jpeg);
            float time = SystemClock.uptimeMillis() % 60000;
            boolean ok = applyStyleOriented(bmp, rotation, 200, 5500);
            if (ok) {
                boolean ok2 = applyWarmOriginalFilter(bmp, m9ModelPath, 200, 5500, 1.0f, time, 0.6f, -0.95f, 0.3f);
                if (!ok2) {
                    DenoiseFlow.recycle(bmp);
                    return null;
                }
                try {
                    byte[] out = encode(bmp, jpeg);
                    DenoiseFlow.recycle(bmp);
                    return out;
                } catch (Throwable th) {
                    return null;
                }
            }
            DenoiseFlow.recycle(bmp);
            return null;
        } catch (Throwable th2) {
        }
    }

    public static byte[] applyWarmLut(Context ctx, byte[] jpeg, float denoise, float ev, float warmth) {
        ensureModels(ctx);
        if (m9ModelPath == null) {
            return null;
        }
        try {
            Bitmap bmp = decode(jpeg);
            if (bmp == null) {
                return null;
            }
            float time = SystemClock.uptimeMillis() % 60000;
            boolean ok = applyWarmOriginalFilter(bmp, m9ModelPath, 200.0f, 5500.0f, 1.0f, time, denoise, ev, warmth);
            if (!ok) {
                DenoiseFlow.recycle(bmp);
                return null;
            }
            try {
                byte[] out = encode(bmp, jpeg);
                DenoiseFlow.recycle(bmp);
                return out;
            } catch (Throwable th) {
            }
        } catch (Throwable th2) {
        }
        return null;
    }

    private static boolean applyStyleOriented(Bitmap b, int rotation, int lux, int cct) {
        if (b.getWidth() >= b.getHeight()) {
            return applyStyle(b, styleRunner, cachePath, styleModels, rotation, lux, cct);
        }
        Matrix m = new Matrix();
        m.setRotate(-90.0f);
        Bitmap rotated = Bitmap.createBitmap(b, 0, 0, b.getWidth(), b.getHeight(), m, false);
        boolean ok = applyStyle(rotated, styleRunner, cachePath, styleModels, (rotation + 90) % 360, lux, cct);
        if (!ok) {
            DenoiseFlow.recycle(rotated);
            return false;
        }
        Matrix m2 = new Matrix();
        m2.setRotate(90.0f);
        m2.postTranslate(b.getWidth(), 0.0f);
        Canvas c = new Canvas(b);
        c.drawBitmap(rotated, m2, null);
        DenoiseFlow.recycle(rotated);
        return true;
    }

    private static Bitmap decode(byte[] jpeg) {
        BitmapFactory.Options opts = new BitmapFactory.Options();
        opts.inMutable = true;
        opts.inPreferredConfig = Bitmap.Config.ARGB_8888;
        opts.inPreferredColorSpace = ColorSpace.get(ColorSpace.Named.SRGB);
        return DenoiseFlow.prepare(BitmapFactory.decodeByteArray(jpeg, 0, jpeg.length, opts));
    }

    private static byte[] encode(Bitmap bmp, byte[] srcJpeg) {
        byte[] bArrDefer = DenoiseFlow.defer(bmp, srcJpeg);
        if (bArrDefer != null) {
            return bArrDefer;
        }
        ByteArrayOutputStream bos = new ByteArrayOutputStream(srcJpeg.length);
        bmp.compress(Bitmap.CompressFormat.JPEG, 95, bos);
        return MadridLegendary.copyExif(srcJpeg, bos.toByteArray());
    }

    private static int readOrientation(byte[] jpeg) {
        try {
            ExifInterface exif = new ExifInterface(new ByteArrayInputStream(jpeg));
            int o = exif.getAttributeInt(lmmoment.exifinterface.media.ExifInterface.TAG_ORIENTATION, 1);
            switch (o) {
                case 3:
                case 4:
                    return 180;
                case lmmoment.exifinterface.media.ExifInterface.ORIENTATION_TRANSPOSE /* 5 */:
                case 6:
                    return 90;
                case 7:
                case 8:
                    return 270;
                default:
                    return 0;
            }
        } catch (Throwable th) {
            return 0;
        }
    }
}
