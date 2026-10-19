package com.codex.cameralook;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.GradientDrawable;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import com.codex.fullm9.CloudGalleryAdapter;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Field;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
public final class ToneGallery {
    private static boolean cleaned;

    static int dp(Context context, float f) {
        return Math.max(1, Math.round(f * context.getResources().getDisplayMetrics().density));
    }

    static GradientDrawable border(Context context, boolean z) {
        GradientDrawable gradientDrawable = new GradientDrawable();
        gradientDrawable.setColor(-16777216);
        gradientDrawable.setCornerRadius(dp(context, 8.0f));
        if (z) {
            gradientDrawable.setStroke(dp(context, 3.0f), -1);
        }
        return gradientDrawable;
    }

    static int selection(Object obj) throws Exception {
        Field declaredField = obj.getClass().getDeclaredField("selected");
        declaredField.setAccessible(true);
        return declaredField.getInt(obj);
    }

    static void selection(Object obj, int i) throws Exception {
        Field declaredField = obj.getClass().getDeclaredField("selected");
        declaredField.setAccessible(true);
        declaredField.setInt(obj, i);
    }

    static synchronized void prune(Context context) {
        if (cleaned) {
            return;
        }
        String[] strArr = {"tone-ui-diagnostic.txt", "cameralook-last-render.txt"};
        for (int i = 0; i < 2; i++) {
            try {
                new File(context.getFilesDir(), strArr[i]).delete();
            } catch (RuntimeException e) {
            }
        }
        cleaned = true;
    }

    public static View card(Activity activity, Gallery gallery, int i, int i2) {
        prune(activity);
        FrameLayout frameLayout = new FrameLayout(activity);
        frameLayout.setLayerType(1, null);
        int iMax = Math.max(1, Math.min(Math.max(dp(activity, 80.0f), activity.getResources().getDisplayMetrics().widthPixels - dp(activity, 100.0f)), (int) Math.min(2147483647L, (((long) Math.max(dp(activity, 120.0f), gallery.getHeight() > 0 ? gallery.getHeight() - dp(activity, 12.0f) : dp(activity, 450.0f))) * 3) / 2)));
        frameLayout.setLayoutParams(new Gallery.LayoutParams(dp(activity, 6.0f) + iMax, Math.max(1, (iMax * 2) / 3) + dp(activity, 6.0f)));
        frameLayout.setPadding(dp(activity, 3.0f), dp(activity, 3.0f), dp(activity, 3.0f), dp(activity, 3.0f));
        frameLayout.setBackground(border(activity, i == i2));
        frameLayout.setSelected(i == i2);
        String strName = ToneCatalog.name(CloudGalleryAdapter.model(i));
        frameLayout.setContentDescription(String.valueOf(strName) + " 影调");
        try {
            Bitmap bitmapSample = CloudGalleryAdapter.sample(activity, i);
            ImageView imageView = new ImageView(activity);
            imageView.setScaleType(ImageView.ScaleType.FIT_CENTER);
            imageView.setImageBitmap(bitmapSample);
            frameLayout.addView(imageView, new FrameLayout.LayoutParams(-1, -1));
        } catch (Exception | LinkageError | OutOfMemoryError e) {
            unavailable(activity, frameLayout, strName, i, e);
        }
        return frameLayout;
    }

    static void unavailable(Activity activity, FrameLayout frameLayout, String str, int i, Throwable th) {
        TextView textView = new TextView(activity);
        textView.setText(String.valueOf(str) + "\n介绍图暂不可用，影调仍可选择");
        textView.setTextColor(-1);
        textView.setGravity(17);
        frameLayout.addView(textView, new FrameLayout.LayoutParams(-1, -1));
    }

    public static void selected(Object obj, ImageView imageView, TextView textView, ScrollView scrollView, Gallery gallery, int i) {
        Throwable th;
        Context context = imageView.getContext();
        try {
            try {
                if (CloudGalleryAdapter.position(i)) {
                    try {
                        try {
                            selection(obj);
                            String strName = ToneCatalog.name(CloudGalleryAdapter.model(i));
                            String strIntro = ToneCatalog.intro(String.valueOf(strName) + "_intro");
                            if (strIntro != null) {
                                imageView.setLayerType(1, null);
                                try {
                                    imageView.setImageBitmap(CloudGalleryAdapter.label(i));
                                } catch (LinkageError e) {
                                    imageView.setImageBitmap(null);
                                } catch (OutOfMemoryError e2) {
                                    imageView.setImageBitmap(null);
                                } catch (RuntimeException e3) {
                                    imageView.setImageBitmap(null);
                                }
                                imageView.setContentDescription(String.valueOf(strName) + " 影调");
                                textView.setText(strIntro);
                                scrollView.scrollTo(0, 0);
                                selection(obj, i);
                                for (int i2 = 0; i2 < gallery.getChildCount(); i2++) {
                                    View childAt = gallery.getChildAt(i2);
                                    if (childAt != null) {
                                        boolean z = gallery.getPositionForView(childAt) == i;
                                        childAt.setBackground(border(context, z));
                                        childAt.setSelected(z);
                                    }
                                }
                                return;
                            }
                            throw new IOException("Introduction missing: " + strName);
                        } catch (Exception e4) {
                            th = e4;
                            failed(context, obj, -1, textView, i, th);
                        }
                    } catch (LinkageError e5) {
                        th = e5;
                        failed(context, obj, -1, textView, i, th);
                    }
                }
            } catch (OutOfMemoryError e6) {
                i = i;
                th = e6;
                textView = textView;
                failed(context, obj, -1, textView, i, th);
            }
        } catch (Exception e7) {
            th = e7;
        } catch (LinkageError e8) {
            th = e8;
        }
    }

    static void failed(Context context, Object obj, int i, TextView textView, int i2, Throwable th) {
        if (i >= 0) {
            try {
                selection(obj, i);
            } catch (Exception e) {
            }
        }
        textView.setText("影调介绍加载失败，保留先前选择。请重新选择。");
        Toast.makeText(context, "影调页面加载失败，请重新选择", 1).show();
    }
}
