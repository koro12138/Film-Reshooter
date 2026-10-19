package com.codex.cameralook;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.media.ExifInterface;
import android.os.Build;
import android.util.Log;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.lang.ref.WeakReference;
import java.lang.reflect.Field;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
public final class WatermarkLast {
    private static final ThreadLocal<State> STATE = new ThreadLocal<>();

    private static final class State {
        boolean finalized;
        boolean hdr;
        WeakReference<Bitmap> output;
        final WeakReference<Bitmap> photo;
        final int style;

        State(Bitmap bitmap, int i) {
            this.photo = new WeakReference<>(bitmap);
            this.style = i;
        }
    }

    public static void clear() {
        STATE.remove();
        NightHighlights.clear();
    }

    public static boolean already(Bitmap bitmap) {
        State state = STATE.get();
        if (state != null && state.photo.get() == bitmap && state.finalized && state.hdr && Build.VERSION.SDK_INT >= 34) {
            return Api34.valid(state.output == null ? null : state.output.get());
        }
        return false;
    }

    static int style() {
        try {
            Field declaredField = Class.forName("com.codex.fullm9.OutputQuality").getDeclaredField("STYLE");
            declaredField.setAccessible(true);
            Object obj = ((ThreadLocal) declaredField.get(null)).get();
            if (obj instanceof Integer) {
                return ((Integer) obj).intValue();
            }
            return 0;
        } catch (Exception e) {
            return 0;
        } catch (LinkageError e2) {
            return 0;
        }
    }

    static void generate(Bitmap bitmap, int i) {
        String str;
        try {
            if (i < 1 || i > 8) {
                ToneHdr.finish(bitmap);
                return;
            }
            State state = STATE.get();
            STATE.remove();
            try {
                ToneReflect.call(Class.forName("com.codex.fullm9.FullM9Hdr"), "finish", new Class[]{Bitmap.class, Bitmap.class, Integer.TYPE}, bitmap, bitmap, Integer.valueOf(i));
            } finally {
                if (state != null) {
                    STATE.set(state);
                }
            }
        } catch (Exception e) {
            e = e;
            str = "Photo HDR unavailable";
            Log.w("WatermarkLast", str, e);
        } catch (LinkageError e2) {
            e = e2;
            str = "Photo HDR API unavailable";
            Log.w("WatermarkLast", str, e);
        } catch (OutOfMemoryError e3) {
            e = e3;
            str = "Photo HDR memory";
            Log.w("WatermarkLast", str, e);
        }
    }

    static State prepare(Bitmap bitmap) {
        String str;
        NightHighlights.prepare(bitmap);
        State state = new State(bitmap, style());
        if (Build.VERSION.SDK_INT >= 34) {
            try {
                if (!Api34.valid(bitmap)) {
                    generate(bitmap, state.style);
                }
                NightHighlights.limit(bitmap);
            } catch (Exception e) {
                e = e;
                str = "HDR preparation";
                Log.w("WatermarkLast", str, e);
            } catch (LinkageError e2) {
                e = e2;
                str = "HDR API";
                Log.w("WatermarkLast", str, e);
            } catch (OutOfMemoryError e3) {
                e = e3;
                str = "HDR memory";
                Log.w("WatermarkLast", str, e);
            }
        }
        STATE.set(state);
        return state;
    }

    static void ensure(State state, Bitmap bitmap, Bitmap bitmap2) {
        String str;
        if (Build.VERSION.SDK_INT < 34) {
            state.finalized = true;
            state.hdr = false;
            state.output = new WeakReference<>(bitmap2);
            return;
        }
        try {
            if (!Api34.valid(bitmap)) {
                generate(bitmap, state.style);
            }
            NightHighlights.limit(bitmap);
            if (!Api34.repair(bitmap, bitmap2)) {
                Api34.clear(bitmap2);
                Log.w("WatermarkLast", "HDR watermark geometry could not be verified");
            }
            state.hdr = Api34.valid(bitmap2);
        } catch (Exception e) {
            e = e;
            safeClear(bitmap2);
            state.hdr = false;
            str = "Optional HDR repair failed";
            Log.w("WatermarkLast", str, e);
        } catch (LinkageError e2) {
            e = e2;
            safeClear(bitmap2);
            state.hdr = false;
            str = "HDR repair API";
            Log.w("WatermarkLast", str, e);
        } catch (OutOfMemoryError e3) {
            e = e3;
            safeClear(bitmap2);
            state.hdr = false;
            str = "HDR repair memory";
            Log.w("WatermarkLast", str, e);
        }
        state.output = new WeakReference<>(bitmap2);
        state.finalized = true;
    }

    static void safeClear(Bitmap bitmap) {
        if (Build.VERSION.SDK_INT >= 34) {
            try {
                Api34.clear(bitmap);
            } catch (Exception | LinkageError | OutOfMemoryError e) {
            }
        }
    }

    public static boolean complete(Bitmap bitmap, Bitmap bitmap2, int i) {
        State state = STATE.get();
        if (state == null || state.photo.get() != bitmap) {
            return false;
        }
        if (state.finalized && state.output != null && state.output.get() == bitmap2) {
            if (!state.hdr) {
                return true;
            }
            if (Build.VERSION.SDK_INT >= 34 && Api34.valid(bitmap2)) {
                return true;
            }
        }
        ensure(state, bitmap, bitmap2);
        return true;
    }

    public static synchronized Bitmap apply(Bitmap bitmap, Object obj, byte[] bArr, Object obj2) throws Exception {
        Class<?> cls;
        Bitmap bitmap2;
        String str;
        String str2;
        Bitmap bitmapFallback;
        State statePrepare = prepare(bitmap);
        try {
            cls = Class.forName("com.codex.lmport.WatermarkCompatA1");
        } catch (ClassNotFoundException e) {
            cls = null;
        }
        bitmap2 = cls != null ? (Bitmap) ToneReflect.call(cls, "applyBeforeHdrLast", new Class[]{Bitmap.class, Object.class, byte[].class, Object.class}, bitmap, obj, bArr, obj2) : (Bitmap) ToneReflect.call(Class.forName("com.codex.leicaapp.OriginalWatermark"), "applyBeforeHdrLast", new Class[]{Bitmap.class, Object.class, byte[].class, Class.forName("android.hardware.camera2.CaptureResult")}, bitmap, obj, bArr, obj2);
        if (bitmap2 == null) {
            throw new IOException("Watermark output missing");
        }
        ensure(statePrepare, bitmap, bitmap2);
        if (Build.VERSION.SDK_INT >= 34 && !statePrepare.hdr) {
            try {
                if (Api34.valid(bitmap) && (bitmapFallback = Api34.fallback(bitmap, bArr, statePrepare.style)) != null) {
                    if (bitmap2 != bitmap && bitmap2 != bitmapFallback) {
                        bitmap2.recycle();
                    }
                    try {
                        statePrepare.output = new WeakReference<>(bitmapFallback);
                        statePrepare.hdr = true;
                        statePrepare.finalized = true;
                        Log.w("WatermarkLast", "Use basic watermark to preserve photo HDR");
                        bitmap2 = bitmapFallback;
                    } catch (Exception e2) {
                        e = e2;
                        bitmap2 = bitmapFallback;
                        str = "WatermarkLast";
                        str2 = "HDR watermark fallback unavailable";
                        Log.w(str, str2, e);
                    } catch (LinkageError e3) {
                        e = e3;
                        bitmap2 = bitmapFallback;
                        str = "WatermarkLast";
                        str2 = "HDR watermark fallback API";
                        Log.w(str, str2, e);
                    } catch (OutOfMemoryError e4) {
                        e = e4;
                        bitmap2 = bitmapFallback;
                        str = "WatermarkLast";
                        str2 = "HDR watermark fallback memory";
                        Log.w(str, str2, e);
                    }
                }
            } catch (Exception e5) {
                e = e5;
            } catch (LinkageError e6) {
                e = e6;
            } catch (OutOfMemoryError e7) {
                e = e7;
            }
        }
        return bitmap2;
    }

    private static final class Api34 {
        private Api34() {
        }

        static void clear(Bitmap bitmap) {
            HdrRepair.clear(bitmap);
        }

        static boolean repair(Bitmap bitmap, Bitmap bitmap2) {
            return HdrRepair.repair(bitmap, bitmap2);
        }

        static boolean valid(Bitmap bitmap) {
            return HdrRepair.valid(bitmap);
        }

        /* JADX WARN: Code duplicated, block: B:20:0x0075 A[Catch: IOException -> 0x0071, all -> 0x008d, TRY_LEAVE, TryCatch #0 {IOException -> 0x0071, blocks: (B:16:0x0053, B:20:0x0075), top: B:40:0x0053 }] */
        static Bitmap fallback(Bitmap bitmap, byte[] bArr, int i) throws Exception {
            String attribute;
            String str;
            Bitmap bitmapCopy = bitmap.copy(Bitmap.Config.ARGB_8888, true);
            if (bitmapCopy == null) {
                return null;
            }
            try {
                try {
                    ExifInterface exifInterface = new ExifInterface(new ByteArrayInputStream(bArr));
                    attribute = exifInterface.getAttribute("Model");
                    String attribute2 = exifInterface.getAttribute("PhotographicSensitivity");
                    String attribute3 = exifInterface.getAttribute("ExposureTime");
                    String attribute4 = exifInterface.getAttribute("FNumber");
                    if (attribute == null) {
                        attribute = "";
                    }
                    if (attribute2 != null) {
                        try {
                            str = String.valueOf("") + "ISO " + attribute2;
                        } catch (IOException e) {
                            str = "";
                        }
                    } else {
                        str = "";
                    }
                    if (attribute3 != null) {
                        try {
                            str = String.valueOf(str) + "  " + attribute3 + "s";
                            if (attribute4 != null) {
                                str = String.valueOf(str) + "  f/" + attribute4;
                            }
                        } catch (IOException e2) {
                        }
                    } else if (attribute4 != null) {
                        str = String.valueOf(str) + "  f/" + attribute4;
                    }
                } catch (IOException e3) {
                    attribute = "";
                    str = attribute;
                }
                float fMax = Math.max(12.0f, Math.min(bitmapCopy.getWidth(), bitmapCopy.getHeight()) * 0.022f);
                float f = 0.8f * fMax;
                float fMax2 = Math.max(8.0f, f);
                Paint paint = new Paint(3);
                paint.setColor(-1);
                paint.setTypeface(Typeface.DEFAULT_BOLD);
                paint.setTextAlign(Paint.Align.RIGHT);
                paint.setTextSize(fMax);
                paint.setShadowLayer(Math.max(1.0f, 0.07f * fMax), 0.0f, 1.0f, -16777216);
                Canvas canvas = new Canvas(bitmapCopy);
                canvas.drawText("LEICA" + (attribute.length() != 0 ? " · " + attribute : ""), bitmapCopy.getWidth() - fMax2, (bitmapCopy.getHeight() - fMax2) - (fMax * 1.35f), paint);
                if (str.length() > 0) {
                    paint.setTypeface(Typeface.DEFAULT);
                    paint.setTextSize(f);
                    canvas.drawText(str, bitmapCopy.getWidth() - fMax2, bitmapCopy.getHeight() - fMax2, paint);
                }
                if (!HdrRepair.knownCopy(bitmap, bitmapCopy)) {
                    bitmapCopy.recycle();
                    return null;
                }
                return bitmapCopy;
            } catch (Throwable th) {
                bitmapCopy.recycle();
                throw th;
            }
        }
    }
}
