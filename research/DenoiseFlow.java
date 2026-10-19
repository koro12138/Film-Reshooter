package com.codex.lmport;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import com.codex.fullm9.OutputQuality;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes15.dex */
public final class DenoiseFlow {
    private static volatile int library;
    private static final ThreadLocal<State> scope = new ThreadLocal<>();

    private static native boolean filter(Bitmap bitmap, boolean z);

    public static Bitmap finish(Bitmap bitmap) {
        return OutputQuality.finish(bitmap);
    }

    public static Bitmap prepare(Bitmap bitmap) {
        return OutputQuality.prepare(bitmap);
    }

    private static final class State {
        boolean prepared;
        Bitmap retained;
        int style;

        private State() {
        }

        /* synthetic */ State(State state) {
            this();
        }
    }

    public static void begin(int[] iArr) {
        end();
        State state = new State(null);
        int i = 0;
        if (iArr != null && iArr.length != 0) {
            i = iArr[0];
        }
        state.style = i;
        scope.set(state);
    }

    private static synchronized boolean available() {
        if (library == 0) {
            try {
                System.loadLibrary("leicadenoise");
                library = 1;
            } catch (LinkageError e) {
                library = -1;
                Log.w("LeicaDenoise", "Native filter unavailable", e);
            }
        }
        return library == 1;
    }

    /* JADX WARN: Code duplicated, block: B:39:0x004b A[ADDED_TO_REGION] */
    private static Bitmap apply(Bitmap bitmap, boolean z) {
        Bitmap bitmapCopy;
        if (bitmap == null || bitmap.isRecycled() || !available()) {
            return bitmap;
        }
        try {
            if (bitmap.isMutable() && bitmap.getConfig() == Bitmap.Config.ARGB_8888) {
                bitmapCopy = bitmap;
            } else {
                bitmapCopy = bitmap.copy(Bitmap.Config.ARGB_8888, true);
                if (bitmapCopy == null) {
                    return bitmap;
                }
            }
            try {
                if (!filter(bitmapCopy, z)) {
                    if (bitmapCopy != bitmap) {
                        bitmapCopy.recycle();
                    }
                    return bitmap;
                }
                if (bitmapCopy != bitmap) {
                    bitmap.recycle();
                }
                return bitmapCopy;
            } catch (LinkageError e) {
                e = e;
                if (bitmapCopy != bitmap && bitmapCopy != null) {
                    bitmapCopy.recycle();
                }
                Log.w("LeicaDenoise", "Preserve image after filter failure", e);
                return bitmap;
            } catch (OutOfMemoryError e2) {
                e = e2;
                if (bitmapCopy != bitmap) {
                    bitmapCopy.recycle();
                }
                Log.w("LeicaDenoise", "Preserve image after filter failure", e);
                return bitmap;
            } catch (RuntimeException e3) {
                e = e3;
                if (bitmapCopy != bitmap) {
                    bitmapCopy.recycle();
                }
                Log.w("LeicaDenoise", "Preserve image after filter failure", e);
                return bitmap;
            }
        } catch (LinkageError | OutOfMemoryError | RuntimeException e4) {
            e = e4;
            bitmapCopy = bitmap;
        }
    }

    public static Bitmap prepareLegacy(Bitmap bitmap) {
        State state = scope.get();
        if (state == null || state.prepared || bitmap == null) {
            return bitmap;
        }
        Bitmap bitmapApply = apply(bitmap, false);
        state.prepared = true;
        return bitmapApply;
    }

    public static Bitmap finishLegacy(Bitmap bitmap) {
        return scope.get() == null ? bitmap : apply(bitmap, true);
    }

    public static byte[] defer(Bitmap bitmap, byte[] bArr) {
        State state = scope.get();
        if (state == null || state.style != 2 || bitmap == null || bitmap.isRecycled() || bArr == null) {
            return null;
        }
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeByteArray(bArr, 0, bArr.length, options);
        if (options.outWidth != bitmap.getWidth() || options.outHeight != bitmap.getHeight()) {
            return null;
        }
        byte[] bArr2 = (byte[]) bArr.clone();
        if (state.retained != null && state.retained != bitmap) {
            state.retained.recycle();
        }
        state.retained = bitmap;
        return bArr2;
    }

    public static Bitmap take() {
        State state = scope.get();
        if (state == null) {
            return null;
        }
        Bitmap bitmap = state.retained;
        state.retained = null;
        return bitmap;
    }

    public static void recycle(Bitmap bitmap) {
        State state = scope.get();
        if (bitmap != null) {
            if (state == null || state.retained != bitmap) {
                bitmap.recycle();
            }
        }
    }

    public static void end() {
        State state = scope.get();
        scope.remove();
        if (state == null || state.retained == null || state.retained.isRecycled()) {
            return;
        }
        state.retained.recycle();
    }
}
