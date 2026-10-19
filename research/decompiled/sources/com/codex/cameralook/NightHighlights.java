package com.codex.cameralook;

import android.graphics.Bitmap;
import android.graphics.Gainmap;
import android.os.Build;
import android.util.Log;
import java.lang.ref.WeakReference;
import java.lang.reflect.Field;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
public final class NightHighlights {
    private static final ThreadLocal<State> STATE = new ThreadLocal<>();

    static final class State {
        final boolean night;
        final WeakReference<Bitmap> photo;

        State(Bitmap bitmap, boolean z) {
            this.photo = new WeakReference<>(bitmap);
            this.night = z;
        }
    }

    public static void clear() {
        STATE.remove();
    }

    public static boolean night(Bitmap bitmap) {
        State state = STATE.get();
        return state != null && state.photo.get() == bitmap && state.night;
    }

    static boolean raw() {
        try {
            Field declaredField = Class.forName("com.codex.fullm9.FullM9Hdr").getDeclaredField("RAW_BOOST");
            declaredField.setAccessible(true);
            return ((ThreadLocal) declaredField.get(null)).get() != null;
        } catch (Exception e) {
            return false;
        } catch (LinkageError e2) {
            return false;
        }
    }

    static float shoulder(float f) {
        if (f <= 0.72f) {
            return f;
        }
        float f2 = (f - 0.72f) / 0.28f;
        return ((0.28f * f2) / ((f2 * 0.32f) + 1.0f)) + 0.72f;
    }

    /* JADX WARN: Code duplicated, block: B:29:0x0079  */
    /* JADX WARN: Multi-variable type inference failed */
    public static void prepare(Bitmap bitmap) {
        boolean z;
        Bitmap bitmap2 = bitmap;
        if (bitmap2 == null || bitmap2.isRecycled()) {
            return;
        }
        State state = STATE.get();
        if (state != null && state.photo.get() == bitmap2) {
            return;
        }
        int i = 0;
        if (raw()) {
            STATE.set(new State(bitmap2, false));
            return;
        }
        try {
            int width = bitmap2.getWidth();
            int height = bitmap2.getHeight();
            int i2 = 1;
            int iMax = Math.max(1, (width + 255) / 256);
            int iMax2 = Math.max(1, (height + 255) / 256);
            int[] iArr = new int[width];
            long j = 0;
            int i3 = 0;
            int i4 = 0;
            int i5 = 0;
            for (int i6 = 0; i6 < height; i6 += iMax2) {
                int i7 = i4;
                int i8 = i3;
                int i9 = i5;
                bitmap2 = bitmap;
                bitmap2.getPixels(iArr, 0, width, 0, i6, width, 1);
                int i10 = i;
                i3 = i8;
                i4 = i7;
                i5 = i9;
                while (i10 < width) {
                    int i11 = iArr[i10];
                    int i12 = (i11 >>> 16) & 255;
                    int i13 = height;
                    int i14 = (i11 >>> 8) & 255;
                    int i15 = i11 & 255;
                    int[] iArr2 = iArr;
                    int iRound = Math.round((i12 * 0.2126f) + (i14 * 0.7152f) + (i15 * 0.0722f));
                    int i16 = width;
                    j += (long) iRound;
                    i3++;
                    if (iRound < 77) {
                        i4++;
                    }
                    if (Math.max(i12, Math.max(i14, i15)) >= 204) {
                        i5++;
                    }
                    i10 += iMax;
                    height = i13;
                    width = i16;
                    iArr = iArr2;
                    i = 0;
                    i2 = 1;
                }
            }
            if (i3 > 0) {
                float f = i3;
                if (i4 < 0.65f * f || j >= 76.5f * f || i5 <= 0 || i5 > f * 0.15f) {
                    z = i;
                } else {
                    z = i2;
                }
            } else {
                z = i;
            }
            try {
                STATE.set(new State(bitmap2, z));
                if (z != 0 && bitmap2.isMutable() && bitmap2.getConfig() == Bitmap.Config.ARGB_8888) {
                    int i17 = i;
                    while (i17 < height) {
                        bitmap2.getPixels(iArr, 0, width, 0, i17, width, 1);
                        int i18 = i;
                        int i19 = i18;
                        while (i18 < width) {
                            int i20 = iArr[i18];
                            int i21 = (i20 >>> 16) & 255;
                            int i22 = (i20 >>> 8) & 255;
                            int i23 = i20 & 255;
                            int iMax3 = Math.max(i21, Math.max(i22, i23));
                            if (iMax3 > 183) {
                                float f2 = iMax3 / 255.0f;
                                float fShoulder = shoulder(f2) / f2;
                                iArr[i18] = (Math.round(i21 * fShoulder) << 16) | ((-16777216) & i20) | (Math.round(i22 * fShoulder) << 8) | Math.round(i23 * fShoulder);
                                i19 |= iArr[i18] != i20 ? i2 : i;
                            }
                            i18++;
                        }
                        if (i19 != 0) {
                            bitmap.setPixels(iArr, 0, width, 0, i17, width, 1);
                        }
                        i17++;
                        bitmap2 = bitmap;
                    }
                }
            } catch (Exception e) {
                e = e;
                bitmap2 = bitmap;
                if (STATE.get() == null) {
                    STATE.set(new State(bitmap2, false));
                }
                Log.w("NightHighlights", "Keep image when highlight protection unavailable", e);
            } catch (LinkageError e2) {
                e = e2;
                bitmap2 = bitmap;
                STATE.set(new State(bitmap2, false));
                Log.w("NightHighlights", "Keep image without optional API", e);
            } catch (OutOfMemoryError e3) {
                e = e3;
                bitmap2 = bitmap;
                if (STATE.get() == null) {
                    STATE.set(new State(bitmap2, false));
                }
                Log.w("NightHighlights", "Keep image at memory limit", e);
            }
        } catch (Exception e4) {
            e = e4;
        } catch (LinkageError e5) {
            e = e5;
        } catch (OutOfMemoryError e6) {
            e = e6;
        }
    }

    private static final class Api34 {
        private Api34() {
        }

        static void limit(Bitmap bitmap) {
            if (bitmap.hasGainmap()) {
                Gainmap gainmap = bitmap.getGainmap();
                float[] ratioMax = gainmap.getRatioMax();
                float[] ratioMin = gainmap.getRatioMin();
                if (ratioMax == null || ratioMin == null || ratioMax.length < 3 || ratioMin.length < 3) {
                    return;
                }
                for (int i = 0; i < 3; i++) {
                    if (!Float.isFinite(ratioMax[i]) || !Float.isFinite(ratioMin[i]) || ratioMin[i] <= 0.0f || ratioMin[i] > 1.2f || ratioMax[i] < ratioMin[i]) {
                        return;
                    }
                }
                gainmap.setRatioMax(Math.min(ratioMax[0], 1.2f), Math.min(ratioMax[1], 1.2f), Math.min(ratioMax[2], 1.2f));
                gainmap.setDisplayRatioForFullHdr(Math.max(gainmap.getMinDisplayRatioForHdrTransition(), Math.min(gainmap.getDisplayRatioForFullHdr(), 1.2f)));
            }
        }
    }

    public static void limit(Bitmap bitmap) {
        String str;
        if (Build.VERSION.SDK_INT < 34 || !night(bitmap) || raw()) {
            return;
        }
        try {
            Api34.limit(bitmap);
        } catch (Exception e) {
            e = e;
            str = "Keep original HDR range";
            Log.w("NightHighlights", str, e);
        } catch (LinkageError e2) {
            e = e2;
            str = "HDR limit unavailable";
            Log.w("NightHighlights", str, e);
        } catch (OutOfMemoryError e3) {
            e = e3;
            str = "HDR limit memory";
            Log.w("NightHighlights", str, e);
        }
    }
}
