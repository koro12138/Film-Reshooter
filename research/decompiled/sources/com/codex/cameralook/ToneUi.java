package com.codex.cameralook;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ColorSpace;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.util.LinkedHashMap;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
public final class ToneUi {
    static final String PREF = "lmoment_v101";
    private static final LinkedHashMap<Integer, Bitmap> samples = new LinkedHashMap<>(4, 0.75f, true);

    public static int selected(Context context) {
        if (context == null) {
            return -1;
        }
        SharedPreferences sharedPreferences = context.getSharedPreferences(PREF, 0);
        if (!sharedPreferences.getBoolean("fullm9_defaults_v1", false)) {
            return -1;
        }
        int i = sharedPreferences.getInt("style", 8);
        if (ToneCatalog.valid(i)) {
            return i;
        }
        return -1;
    }

    public static int[] choice(Context context) {
        int iSelected = selected(context);
        if (iSelected < 0) {
            return null;
        }
        return new int[]{iSelected, 0};
    }

    public static int selection(Context context) {
        int iSelected = selected(context);
        if (iSelected < 0) {
            return -1;
        }
        return (iSelected - 16) + 3;
    }

    public static boolean position(int i) {
        return i >= 3 && i < 26;
    }

    public static int model(int i) {
        return (i - 3) + 16;
    }

    public static String name(int i) {
        if (ToneCatalog.valid(i)) {
            return ToneCatalog.name(i);
        }
        return null;
    }

    public static String intro(String str) {
        return ToneCatalog.intro(str);
    }

    public static String[] append(String[] strArr) {
        String[] strArrNames = ToneCatalog.names();
        String[] strArr2 = new String[strArr.length + strArrNames.length];
        System.arraycopy(strArr, 0, strArr2, 0, strArr.length);
        System.arraycopy(strArrNames, 0, strArr2, strArr.length, strArrNames.length);
        return strArr2;
    }

    public static synchronized Bitmap sample(Context context, int i) throws IOException {
        if (!position(i)) {
            throw new IOException("Invalid tone image");
        }
        int i2 = i - 3;
        Bitmap bitmap = samples.get(Integer.valueOf(i2));
        if (bitmap != null && !bitmap.isRecycled()) {
            return bitmap;
        }
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inSampleSize = 4;
        options.inMutable = true;
        options.inPreferredConfig = Bitmap.Config.ARGB_8888;
        options.inPreferredColorSpace = ColorSpace.get(ColorSpace.Named.SRGB);
        Throwable th = null;
        try {
            InputStream inputStreamOpen = context.getAssets().open("cameralook/intro-" + i2 + ".jpg");
            try {
                Bitmap bitmapDecodeStream = BitmapFactory.decodeStream(inputStreamOpen, null, options);
                if (inputStreamOpen != null) {
                    inputStreamOpen.close();
                }
                if (bitmapDecodeStream == null) {
                    throw new IOException("Tone image unavailable");
                }
                samples.put(Integer.valueOf(i2), bitmapDecodeStream);
                while (samples.size() > 3) {
                    samples.remove(samples.keySet().iterator().next());
                }
                return bitmapDecodeStream;
            } catch (Throwable th2) {
                if (inputStreamOpen != null) {
                    inputStreamOpen.close();
                }
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

    public static Bitmap label(int i) {
        Bitmap bitmapCreateBitmap = Bitmap.createBitmap(640, 72, Bitmap.Config.ARGB_8888);
        Paint paint = new Paint(3);
        paint.setColor(-1);
        paint.setTypeface(Typeface.DEFAULT_BOLD);
        paint.setTextAlign(Paint.Align.CENTER);
        paint.setTextSize(42.0f);
        new Canvas(bitmapCreateBitmap).drawText(ToneCatalog.name(model(i)), 320.0f, 53.0f, paint);
        return bitmapCreateBitmap;
    }

    static void previewNeutral() throws Exception {
        ToneReflect.call(Class.forName("com.codex.lmport.PreviewTone"), "select", new Class[]{Integer.TYPE}, 0);
    }

    public static void apply(final Activity activity, Object obj, int i) {
        if (activity == null || !position(i)) {
            return;
        }
        if (obj != null) {
            try {
                ToneReflect.call(obj, "v43Select", new Class[]{String.class}, "M9");
            } catch (Exception e) {
                Log.e("CameraLook", "Tone selection failed", e);
                Toast.makeText(activity, "影调选择失败，已保留原选择", 1).show();
                return;
            } catch (LinkageError e2) {
                Log.e("CameraLook", "Tone selection unavailable", e2);
                Toast.makeText(activity, "影调暂不可用，已保留原选择", 1).show();
                return;
            }
        }
        previewNeutral();
        activity.getSharedPreferences(PREF, 0).edit().putInt("style", model(i)).putBoolean("fullm9_defaults_v1", true).apply();
        activity.getWindow().getDecorView().post(new Runnable() { // from class: com.codex.cameralook.ToneUi.1
            @Override // java.lang.Runnable
            public void run() {
                ToneUi.badge(activity.getWindow().getDecorView());
            }
        });
    }

    public static void badge(View view) {
        String str;
        Bitmap bitmapSample;
        int iSelected = selected(view.getContext());
        if (iSelected < 0) {
            return;
        }
        try {
            previewNeutral();
            View viewFindViewById = view.findViewById(2131430434);
            if (viewFindViewById instanceof ImageView) {
                ImageView imageView = (ImageView) viewFindViewById;
                try {
                    bitmapSample = sample(view.getContext(), (iSelected - 16) + 3);
                } catch (IOException e) {
                    Log.w("CameraLook", "Tone badge image", e);
                    bitmapSample = null;
                }
                Constructor<?> constructor = Class.forName("com.codex.lmport.ToneBadge").getConstructor(Context.class, Integer.TYPE, String.class, Bitmap.class);
                imageView.clearColorFilter();
                imageView.setScaleType(ImageView.ScaleType.FIT_CENTER);
                imageView.setImageDrawable((Drawable) constructor.newInstance(view.getContext(), Integer.valueOf(iSelected), ToneCatalog.name(iSelected), bitmapSample));
                imageView.setContentDescription(String.valueOf(ToneCatalog.name(iSelected)) + " 影调，点击切换");
                View viewFindViewById2 = view.findViewById(2131430433);
                if (viewFindViewById2 != null) {
                    viewFindViewById2.setContentDescription(String.valueOf(ToneCatalog.name(iSelected)) + " 影调，点击切换");
                }
            }
        } catch (Exception e2) {
            e = e2;
            str = "Tone badge unavailable";
            Log.w("CameraLook", str, e);
        } catch (LinkageError e3) {
            e = e3;
            str = "Tone badge API unavailable";
            Log.w("CameraLook", str, e);
        } catch (OutOfMemoryError e4) {
            e = e4;
            str = "Tone badge memory";
            Log.w("CameraLook", str, e);
        }
    }

    public static boolean activityResult(Activity activity, int i, int i2, Intent intent) {
        if (i != 19533) {
            return false;
        }
        Toast.makeText(activity, "新增影调用于相机拍摄成片，暂不支持此导入入口", 1).show();
        return true;
    }
}
