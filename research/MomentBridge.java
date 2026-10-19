package com.codex.lmport;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;
import com.codex.cameralook.ToneCatalog;
import com.codex.cameralook.ToneEngine;
import com.codex.cameralook.ToneUi;
import com.codex.fullm9.BackgroundCapture;
import com.codex.fullm9.CloudCapture;
import com.codex.fullm9.CloudUi;
import com.codex.fullm9.FullM9Engine;
import com.codex.fullm9.FullM9Hdr;
import com.codex.fullm9.FullM9Ui;
import com.codex.fullm9.LegacyQuality;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.Collections;
import java.util.Locale;
import java.util.Map;
import java.util.WeakHashMap;
import lmktln.UByte;
import lmmoment.exifinterface.media.ExifInterface;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes15.dex */
public final class MomentBridge {
    private static final String PREF = "lmoment_v101";
    private static final String TAG = "LMomentPort";
    private static final String[] IDS = {"ORIGINAL", "M3", "M9"};
    private static final String[] LABELS = {"原图", "M3 · 银盐黑白", "M9 · 经典彩色"};
    private static final String[] SHORT_NAMES = {"原图", "M3", "M9"};
    private static final String[] LOOKS = {"原图", "细腻黑白层次，适合街头、人文和光影。", "温润而鲜明的经典彩色，适合风景、建筑和日常记录。"};
    private static final String[] CHAINS = {"原图", "保留现有M3处理链。", "保留现有M9处理链。"};
    private static final Object RENDER = new Object();
    private static final Map<Object, int[]> SHOTS = Collections.synchronizedMap(new WeakHashMap());
    private static final int[] GALLERY_ORDER = {2, 1};
    private static final String[] GALLERY_NAMES = {"M9", "M3"};
    private static final Bitmap[] GALLERY_SAMPLES = new Bitmap[GALLERY_ORDER.length];
    private static volatile String status = "尚未拍摄";

    public static boolean activityResult(Activity activity, int i, int i2, Intent intent) {
        return CloudUi.activityResult(activity, i, i2, intent);
    }

    public static int[] choice(Context context) {
        return CloudUi.choice(context);
    }

    public static boolean cloudPreviousActivityResult(Activity activity, int i, int i2, Intent intent) {
        return ToneUi.selected(activity) >= 0 ? ToneUi.activityResult(activity, i, i2, intent) : FullM9Ui.activityResult(activity, i, i2, intent);
    }

    public static int[] cloudPreviousChoice(Context context) {
        int[] iArrChoice = ToneUi.choice(context);
        if (iArrChoice != null) {
            return iArrChoice;
        }
        int[] iArrChoice2 = FullM9Ui.choice(context);
        int i = iArrChoice2[0];
        if (i > 2 && i != 8) {
            iArrChoice2[0] = 2;
            if (context != null) {
                context.getSharedPreferences(PREF, 0).edit().putInt("style", 2).apply();
            }
        }
        return iArrChoice2;
    }

    public static void cloudPreviousGalleryApply(Activity activity, Object obj, int i) {
        if (ToneUi.position(i)) {
            ToneUi.apply(activity, obj, i);
        } else {
            FullM9Ui.galleryApply(activity, obj, i);
        }
    }

    public static String cloudPreviousGalleryIntro(String str) {
        String strIntro = ToneUi.intro(str);
        return strIntro != null ? strIntro : FullM9Ui.galleryIntro(str);
    }

    public static Bitmap cloudPreviousGalleryLabel(int i) {
        return ToneUi.position(i) ? ToneUi.label(i) : FullM9Ui.galleryLabel(i);
    }

    public static int cloudPreviousGalleryModelIndex(int i) {
        return ToneUi.position(i) ? ToneUi.model(i) : FullM9Ui.galleryModelIndex(i);
    }

    public static String[] cloudPreviousGalleryNames() {
        return ToneUi.append(FullM9Ui.galleryNames());
    }

    public static Bitmap cloudPreviousGallerySample(Context context, int i) {
        return ToneUi.position(i) ? ToneUi.sample(context, i) : FullM9Ui.gallerySample(context, i);
    }

    public static int cloudPreviousGallerySelection(Context context, int i) {
        int iSelection = ToneUi.selection(context);
        return iSelection >= 0 ? iSelection : FullM9Ui.gallerySelection(context, i);
    }

    public static String cloudPreviousModelName(int i) {
        String strName = ToneUi.name(i);
        return strName != null ? strName : FullM9Ui.modelName(i);
    }

    public static void cloudPreviousUpdateBadge(View view) {
        if (ToneUi.selected(view.getContext()) >= 0) {
            ToneUi.badge(view);
        } else {
            FullM9Ui.updateBadge(view);
        }
    }

    private static Bitmap decode(byte[] bArr) {
        return LegacyQuality.decodeFinal(bArr);
    }

    private static byte[] exif(byte[] bArr, byte[] bArr2, boolean z, int i, int i2, boolean z2) {
        return LegacyQuality.exif(bArr, bArr2, z, i, i2, z2);
    }

    public static void galleryApply(Activity activity, Object obj, int i) {
        CloudUi.galleryApply(activity, obj, i);
    }

    public static String galleryIntro(String str) {
        return CloudUi.galleryIntro(str);
    }

    public static Bitmap galleryLabel(int i) {
        return CloudUi.galleryLabel(i);
    }

    public static int galleryModelIndex(int i) {
        return CloudUi.galleryModelIndex(i);
    }

    public static String[] galleryNames() {
        return CloudUi.galleryNames();
    }

    public static Bitmap gallerySample(Context context, int i) {
        return CloudUi.gallerySample(context, i);
    }

    public static Bitmap gallerySampleLegacy(Context context, int i) throws IOException {
        Bitmap bitmap;
        if (i < 0 || i >= 2) {
            throw new IOException("Invalid tone selection");
        }
        Bitmap[] bitmapArr = GALLERY_SAMPLES;
        synchronized (bitmapArr) {
            bitmap = bitmapArr[i];
            if (bitmap == null || bitmap.isRecycled()) {
                InputStream inputStreamOpen = context.getAssets().open(i == 0 ? "tone-intro/M9.png" : "tone-intro/M3.png");
                try {
                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inSampleSize = 2;
                    Bitmap bitmapDecodeStream = BitmapFactory.decodeStream(inputStreamOpen, null, options);
                    inputStreamOpen.close();
                    if (bitmapDecodeStream == null) {
                        throw new IOException("Tone introduction image unavailable");
                    }
                    bitmapArr[i] = bitmapDecodeStream;
                    bitmap = bitmapDecodeStream;
                } catch (Throwable th) {
                    inputStreamOpen.close();
                    throw th;
                }
            }
        }
        return bitmap;
    }

    public static int gallerySelection(Context context, int i) {
        return CloudUi.gallerySelection(context, i);
    }

    public static String modelName(int i) {
        return CloudUi.modelName(i);
    }

    /* JADX INFO: Access modifiers changed from: private */
    public static byte[] render(Context context, byte[] bArr, Object obj, int[] iArr) {
        if (iArr[0] == 512) {
            return CloudCapture.fallback(context, bArr, obj, iArr);
        }
        if (ToneCatalog.valid(iArr[0])) {
            return ToneEngine.render(context, bArr, obj, iArr);
        }
        return iArr[0] == 8 ? FullM9Engine.render(context, bArr, obj, iArr) : LegacyQuality.render(context, bArr, obj, iArr);
    }

    public static void updateBadge(View view) {
        CloudUi.updateBadge(view);
    }

    private static Context app() {
        try {
            return (Context) Class.forName("com.xiaomi.camera.basic.Global").getMethod("getApplication", new Class[0]).invoke(null, new Object[0]);
        } catch (Exception e) {
            return null;
        }
    }

    private static int bounded(int i, int i2, int i3) {
        return (i < 0 || i >= i2) ? i3 : i;
    }

    public static int[] choiceLegacy(Context context) {
        return context == null ? new int[]{0, 0} : new int[]{bounded(context.getSharedPreferences(PREF, 0).getInt("style", 2), IDS.length, 2), 0};
    }

    private static Object field(Object obj, String str) {
        Object obj2 = null;
        if (obj != null) {
            for (Class<?> superclass = obj.getClass(); superclass != null; superclass = superclass.getSuperclass()) {
                try {
                    Field declaredField = superclass.getDeclaredField(str);
                    declaredField.setAccessible(true);
                    obj2 = declaredField.get(obj);
                    break;
                } catch (NoSuchFieldException e) {
                } catch (Exception e2) {
                }
            }
        }
        return obj2;
    }

    private static void put(Object obj, String str, Object obj2) {
        if (obj == null) {
            return;
        }
        try {
            obj.getClass().getField(str).set(obj, obj2);
        } catch (Exception e) {
            Log.w(TAG, "capture size: " + str, e);
        }
    }

    private static int mode() {
        try {
            return Class.forName("com.android.camera.module.Z").getField("a").getInt(null);
        } catch (Exception e) {
            return -1;
        }
    }

    private static int shotMode(Object obj) {
        Object objField = field(field(obj, "b"), "g");
        if (objField instanceof Number) {
            return ((Number) objField).intValue();
        }
        return -1;
    }

    public static void snapshot(Object obj) {
        if (shotMode(obj) == 256) {
            SHOTS.put(obj, choice(app()));
        }
        BackgroundCapture.snapshot(obj);
    }

    public static void copySnapshot(Object obj, Object obj2) {
        int[] iArr = SHOTS.get(obj);
        if (iArr != null && obj2 != null) {
            SHOTS.put(obj2, (int[]) iArr.clone());
        }
        BackgroundCapture.copy(obj, obj2);
    }

    /* JADX INFO: Access modifiers changed from: private */
    public static Object singleton(String str) throws Exception {
        return Class.forName(str).getField("INSTANCE").get(null);
    }

    /* JADX INFO: Access modifiers changed from: private */
    public static Object call(Object obj, String str, Class<?>[] clsArr, Object... objArr) throws Exception {
        Method declaredMethod = (obj instanceof Class ? (Class) obj : obj.getClass()).getDeclaredMethod(str, clsArr);
        declaredMethod.setAccessible(true);
        try {
            if (obj instanceof Class) {
                obj = null;
            }
            return declaredMethod.invoke(obj, objArr);
        } catch (InvocationTargetException e) {
            Throwable cause = e.getCause();
            if (cause instanceof Error) {
                throw ((Error) cause);
            }
            if (cause instanceof Exception) {
                throw ((Exception) cause);
            }
            throw e;
        }
    }

    public static byte[] exifLegacy(byte[] bArr, byte[] bArr2, boolean z, int i, int i2, boolean z2) throws Exception {
        return (byte[]) call(Class.forName("com.codex.leicaapp.JpegMetadata"), "copyExif", new Class[]{byte[].class, byte[].class, Boolean.TYPE, Integer.TYPE, Integer.TYPE, Boolean.TYPE}, bArr, bArr2, Boolean.valueOf(z), Integer.valueOf(i), Integer.valueOf(i2), Boolean.valueOf(z2));
    }

    public static Bitmap decodeLegacy(byte[] bArr) {
        Bitmap bitmapTake = DenoiseFlow.take();
        if (bitmapTake != null) {
            return bitmapTake;
        }
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inMutable = true;
        options.inPreferredConfig = Bitmap.Config.ARGB_8888;
        return BitmapFactory.decodeByteArray(bArr, 0, bArr.length, options);
    }

    private static Object callback(final String[] strArr) throws Exception {
        Class<?> cls = Class.forName("lmktln.jvm.functions.Function1");
        return Proxy.newProxyInstance(cls.getClassLoader(), new Class[]{cls}, new InvocationHandler() { // from class: com.codex.lmport.MomentBridge.1
            @Override // java.lang.reflect.InvocationHandler
            public Object invoke(Object obj, Method method, Object[] objArr) throws Throwable {
                if (method.getName().equals("invoke")) {
                    if (strArr != null && objArr != null && objArr.length > 0) {
                        strArr[0] = "原包兼容分支：" + String.valueOf(objArr[0]);
                    }
                    return Class.forName("lmktln.Unit").getField("INSTANCE").get(null);
                }
                if (method.getName().equals("toString")) {
                    return "LMoment callback";
                }
                if (method.getName().equals("hashCode")) {
                    return Integer.valueOf(System.identityHashCode(obj));
                }
                if (method.getName().equals("equals")) {
                    return Boolean.valueOf(obj == objArr[0]);
                }
                return null;
            }
        });
    }

    public static byte[] process(byte[] bArr, Object obj) {
        byte[] bArrFailed;
        Context contextApp = app();
        if (bArr == null || contextApp == null || shotMode(obj) != 256) {
            return null;
        }
        int[] iArrChoice = SHOTS.get(obj);
        if (iArrChoice == null) {
            iArrChoice = choice(contextApp);
        }
        if (iArrChoice[0] == 0) {
            return null;
        }
        try {
            if (Looper.myLooper() == Looper.getMainLooper()) {
                status = "保存入口在主线程，所选模型未执行";
                notice(contextApp, status);
                return bArr;
            }
            bArrFailed = render(contextApp, bArr, obj, iArrChoice);
            return bArrFailed;
        } catch (Exception e) {
            bArrFailed = failed(contextApp, bArr, e);
        } catch (LinkageError e2) {
            bArrFailed = failed(contextApp, bArr, e2);
        } catch (OutOfMemoryError e3) {
            bArrFailed = failed(contextApp, bArr, e3);
        } finally {
            SHOTS.remove(obj);
        }
    }

    private static byte[] failed(Context context, byte[] bArr, Throwable th) {
        status = "模型处理失败：" + th.getClass().getSimpleName();
        Log.e(TAG, status, th);
        notice(context, "本张未完成所选影调，请改选模型后重拍");
        return bArr;
    }

    public static byte[] renderLegacy(Context context, byte[] bArr, Object obj, int[] iArr) throws Exception {
        Bitmap bitmap;
        Bitmap bitmap2;
        Bitmap bitmap3;
        byte[] bArrExif;
        synchronized (RENDER) {
            try {
                try {
                    DenoiseFlow.begin(iArr);
                    String[] strArr = {null};
                    byte[] bArr2 = (byte[]) call(singleton("com.leicamoments.app.ImageUtils"), "normalizeExifOrientation", new Class[]{byte[].class}, bArr);
                    int i = iArr[0];
                    Class<?> cls = Class.forName("com.leicamoments.app.LeicaEngine$Style");
                    byte[] bArr3 = (byte[]) call(singleton("com.leicamoments.app.LeicaEngine"), "process", new Class[]{Context.class, byte[].class, cls, Class.forName("lmktln.jvm.functions.Function1"), Boolean.TYPE}, context, bArr2, Enum.valueOf(cls, IDS[iArr[0]]), callback(strArr), true);
                    if (bArr3 == null || bArr3.length < 4) {
                        throw new IOException("Model produced no JPEG");
                    }
                    if (bArr3 == bArr2) {
                        throw new IOException("Model returned unprocessed source");
                    }
                    BitmapFactory.Options options = new BitmapFactory.Options();
                    options.inJustDecodeBounds = true;
                    BitmapFactory.decodeByteArray(bArr3, 0, bArr3.length, options);
                    if (options.outWidth <= 0 || options.outHeight <= 0) {
                        throw new IOException("Invalid model JPEG");
                    }
                    byte[] bArr4 = (byte[]) call(Class.forName("com.codex.lmoments.LeicaMark"), "mark", new Class[]{byte[].class}, exif(bArr2, bArr3, iArr[0] == 1, options.outWidth, options.outHeight, false));
                    Bitmap bitmapDecode = decode(bArr4);
                    try {
                        if (bitmapDecode == null) {
                            throw new IOException("Decode model JPEG failed");
                        }
                        Bitmap bitmapFinish = DenoiseFlow.finish(bitmapDecode);
                        Bitmap bitmapDecode2 = decode(bArr);
                        if (bitmapDecode2 != null) {
                            try {
                                FullM9Hdr.transfer(bitmapDecode2, bitmapFinish, bArr, iArr[0] == 1);
                            } catch (Throwable th) {
                                th = th;
                                bitmap = null;
                                bitmap2 = bitmapFinish;
                                bitmap3 = bitmapDecode2;
                                if (bitmap != null) {
                                    bitmap.recycle();
                                }
                                if (bitmap2 != null) {
                                    bitmap2.recycle();
                                }
                                if (bitmap3 != null) {
                                    bitmap3.recycle();
                                }
                                throw th;
                            }
                        }
                        Object objField = field(field(obj, "f"), "b");
                        if (objField == null) {
                            objField = field(field(obj, "f"), "c");
                        }
                        if (objField == null) {
                            objField = field(obj, "legendaryPreviewResult");
                        }
                        Bitmap bitmap4 = obj == null ? bitmapFinish : (Bitmap) call(Class.forName("com.codex.leicaapp.OriginalWatermark"), "apply", new Class[]{Bitmap.class, Object.class, byte[].class, Class.forName("android.hardware.camera2.CaptureResult")}, bitmapFinish, obj, bArr4, objField);
                        try {
                            if (bitmap4 == null) {
                                throw new IOException("Watermark produced no bitmap");
                            }
                            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(bArr4.length);
                            Bitmap.CompressFormat compressFormat = Bitmap.CompressFormat.JPEG;
                            FullM9Hdr.finish(bitmapFinish, bitmap4, iArr[0]);
                            if (!bitmap4.compress(compressFormat, 98, byteArrayOutputStream)) {
                                throw new IOException("JPEG compression failed");
                            }
                            bArrExif = exif(bArr4, byteArrayOutputStream.toByteArray(), iArr[0] == 1, bitmap4.getWidth(), bitmap4.getHeight(), true);
                            FullM9Hdr.verify(context, bArrExif, iArr[0]);
                            if (obj != null) {
                                put(field(obj, "b"), "b", Class.forName("android.util.Size").getConstructor(Integer.TYPE, Integer.TYPE).newInstance(Integer.valueOf(bitmap4.getWidth()), Integer.valueOf(bitmap4.getHeight())));
                                uprightSource(field(obj, "a"), bitmap4.getWidth(), bitmap4.getHeight());
                            }
                            status = LABELS[iArr[0]] + " · " + bitmap4.getWidth() + "×" + bitmap4.getHeight() + (strArr[0] == null ? "" : " · " + strArr[0]);
                            Log.i(TAG, status);
                            try {
                                FileOutputStream fileOutputStream = new FileOutputStream(new File(context.getFilesDir(), "lmoment-last-render.txt"));
                                fileOutputStream.write((status + "\n" + ((String) call(singleton("com.leicamoments.app.DiagLog"), "snapshot", new Class[0], new Object[0]))).getBytes("UTF-8"));
                                fileOutputStream.close();
                            } catch (Exception e) {
                                Log.w(TAG, "Write render diagnostics failed", e);
                            }
                            if (bitmap4 != null && bitmap4 != bitmapFinish && !bitmap4.isRecycled()) {
                                bitmap4.recycle();
                            }
                            if (bitmapFinish != null && !bitmapFinish.isRecycled()) {
                                bitmapFinish.recycle();
                            }
                            if (bitmapDecode2 != null && !bitmapDecode2.isRecycled()) {
                                bitmapDecode2.recycle();
                            }
                            DenoiseFlow.end();
                        } catch (Throwable th2) {
                            th = th2;
                            bitmap = bitmap4;
                            bitmap2 = bitmapFinish;
                            bitmap3 = bitmapDecode2;
                            if (bitmap != null && bitmap != bitmap2 && !bitmap.isRecycled()) {
                                bitmap.recycle();
                            }
                            if (bitmap2 != null && !bitmap2.isRecycled()) {
                                bitmap2.recycle();
                            }
                            if (bitmap3 != null && !bitmap3.isRecycled()) {
                                bitmap3.recycle();
                            }
                            throw th;
                        }
                    } catch (Throwable th3) {
                        th = th3;
                        bitmap = null;
                        bitmap2 = bitmapDecode;
                        bitmap3 = null;
                    }
                } catch (Throwable th4) {
                    DenoiseFlow.end();
                    throw th4;
                }
            } catch (Throwable th5) {
                th = th5;
                bitmap = null;
                bitmap2 = null;
                bitmap3 = null;
            }
        }
        return bArrExif;
    }

    /* JADX INFO: Access modifiers changed from: private */
    public static void notice(final Context context, final String str) {
        new Handler(Looper.getMainLooper()).post(new Runnable() { // from class: com.codex.lmport.MomentBridge.2
            @Override // java.lang.Runnable
            public void run() {
                Toast.makeText(context, str, 1).show();
            }
        });
    }

    public static void uprightSource(Object obj, int i, int i2) {
        if (obj == null || i <= 0 || i2 <= 0) {
            return;
        }
        put(obj, "a", Integer.valueOf(i));
        put(obj, "b", Integer.valueOf(i2));
        put(obj, "c", 0);
        put(obj, "d", 0);
    }

    public static String modelNameLegacy(int i) {
        return SHORT_NAMES[bounded(i, SHORT_NAMES.length, 2)];
    }

    public static void updatePicker(Object obj, int i) {
        if (i != 256 || obj == null) {
            return;
        }
        Object objField = field(obj, "b");
        if (objField instanceof View) {
            updateBadge((View) objField);
        }
    }

    public static void updateBadgeLegacy(View view) {
        View viewFindViewById = view.findViewById(2131430434);
        if (viewFindViewById instanceof ImageView) {
            ImageView imageView = (ImageView) viewFindViewById;
            Context context = imageView.getContext();
            int i = choice(context)[0];
            Drawable drawable = imageView.getDrawable();
            if ((drawable instanceof ToneBadge) && ((ToneBadge) drawable).model() == i) {
                return;
            }
            Bitmap bitmapGallerySampleLegacy = null;
            for (int i2 = 0; i2 < GALLERY_ORDER.length; i2++) {
                try {
                    if (GALLERY_ORDER[i2] == i) {
                        bitmapGallerySampleLegacy = gallerySampleLegacy(context, i2);
                        break;
                    }
                } catch (IOException e) {
                    Log.w(TAG, "Button sample unavailable", e);
                } catch (OutOfMemoryError e2) {
                    Log.w(TAG, "Button sample memory", e2);
                }
            }
            imageView.clearColorFilter();
            imageView.setScaleType(ImageView.ScaleType.FIT_CENTER);
            imageView.setImageDrawable(new ToneBadge(context, i, modelName(i), bitmapGallerySampleLegacy));
            imageView.setContentDescription(modelName(i) + " 影调，点击切换");
            View viewFindViewById2 = view.findViewById(2131430433);
            if (viewFindViewById2 != null) {
                viewFindViewById2.setContentDescription(modelName(i) + " 影调，点击切换");
            }
        }
    }

    private static void refreshButton(final Activity activity) {
        View viewFindViewById;
        if (activity == null || (viewFindViewById = activity.findViewById(2131430434)) == null) {
            return;
        }
        viewFindViewById.post(new Runnable() { // from class: com.codex.lmport.MomentBridge.3
            @Override // java.lang.Runnable
            public void run() {
                if (MomentBridge.leicaMode()) {
                    MomentBridge.updateBadge(activity.getWindow().getDecorView());
                }
            }
        });
    }

    public static void attach(Activity activity) {
        if (activity != null) {
            PreviewTone.select(choice(activity)[0]);
            refreshButton(activity);
        }
        BackgroundCapture.attach(activity);
    }

    public static void detach(Activity activity) {
    }

    public static boolean leicaMode() {
        return mode() == 256;
    }

    public static String[] galleryNamesLegacy() {
        return (String[]) GALLERY_NAMES.clone();
    }

    public static int galleryModelIndexLegacy(int i) {
        if (i < 0 || i >= GALLERY_ORDER.length) {
            return 2;
        }
        return GALLERY_ORDER[i];
    }

    public static int gallerySelectionLegacy(Context context, int i) {
        if (context == null || !context.getSharedPreferences(PREF, 0).contains("style")) {
            return i;
        }
        int i2 = choice(context)[0];
        for (int i3 = 0; i3 < GALLERY_ORDER.length; i3++) {
            if (GALLERY_ORDER[i3] == i2) {
                return i3;
            }
        }
        return 0;
    }

    public static Bitmap galleryLabelLegacy(int i) {
        if (i < 0 || i >= GALLERY_NAMES.length) {
            i = 0;
        }
        Bitmap bitmapCreateBitmap = Bitmap.createBitmap(640, 72, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmapCreateBitmap);
        Paint paint = new Paint(1);
        paint.setColor(-1);
        paint.setTypeface(Typeface.DEFAULT_BOLD);
        paint.setTextAlign(Paint.Align.CENTER);
        paint.setTextSize(46.0f);
        canvas.drawText(GALLERY_NAMES[i], 320.0f, 53.0f, paint);
        return bitmapCreateBitmap;
    }

    public static String galleryIntroLegacy(String str) {
        if (str == null) {
            return null;
        }
        String strReplace = str.replace("ı", "i");
        for (int i = 0; i < GALLERY_NAMES.length; i++) {
            if ((GALLERY_NAMES[i].toLowerCase(Locale.US) + "_intro").equals(strReplace)) {
                int i2 = GALLERY_ORDER[i];
                return LABELS[i2] + "\n" + LOOKS[i2] + "\n" + CHAINS[i2] + "\nAI介绍图，仅用于风格说明；实际成片使用所选影调。";
            }
        }
        return null;
    }

    public static void galleryApplyLegacy(Activity activity, Object obj, int i) {
        if (activity == null) {
            return;
        }
        int iGalleryModelIndexLegacy = galleryModelIndexLegacy(i);
        activity.getSharedPreferences(PREF, 0).edit().putInt("style", iGalleryModelIndexLegacy).apply();
        PreviewTone.select(iGalleryModelIndexLegacy);
        String str = iGalleryModelIndexLegacy == 1 ? "M3" : "M9";
        if (obj != null) {
            try {
                call(obj, "v43Select", new Class[]{String.class}, str);
            } catch (Exception e) {
                Log.w(TAG, "Native gallery selection", e);
            }
        }
        refreshButton(activity);
        Log.i(TAG, "Native gallery selected " + IDS[iGalleryModelIndexLegacy] + " / " + LABELS[iGalleryModelIndexLegacy]);
    }

    public static boolean activityResultLegacy(Activity activity, int i, int i2, Intent intent) {
        if (i != 19533) {
            return false;
        }
        if (i2 != -1 || intent == null || intent.getData() == null) {
            return true;
        }
        final Uri data = intent.getData();
        final Context applicationContext = activity.getApplicationContext();
        final int[] iArrChoice = choice(applicationContext);
        if (iArrChoice[0] == 0) {
            notice(applicationContext, "请先选择 L-Moment 影调");
            return true;
        }
        notice(applicationContext, "开始处理导入照片");
        new Thread(new Runnable() { // from class: com.codex.lmport.MomentBridge.4
            /* JADX WARN: Code duplicated, block: B:85:0x0201  */
            @Override // java.lang.Runnable
            public void run() throws Throwable {
                Uri uriInsert;
                try {
                    try {
                        byte[] byteArray = (byte[]) MomentBridge.call(MomentBridge.singleton("com.leicamoments.app.ImageUtils"), "readBytes", new Class[]{Context.class, Uri.class}, applicationContext, data);
                        if (byteArray.length < 2 || (byteArray[0] & UByte.MAX_VALUE) != 255 || (byteArray[1] & UByte.MAX_VALUE) != 216) {
                            String type = applicationContext.getContentResolver().getType(data);
                            Bitmap bitmapDecodeByteArray = (type == null || !type.startsWith("image/") || type.contains("raw") || type.contains("dng")) ? null : BitmapFactory.decodeByteArray(byteArray, 0, byteArray.length);
                            if (bitmapDecodeByteArray == null) {
                                int[] iArr = (int[]) MomentBridge.call(Class.forName("com.leicamoments.app.RawDecoder"), "nativeDecode", new Class[]{byte[].class}, byteArray);
                                if (iArr == null || iArr.length < 3) {
                                    throw new IOException("RAW decode failed");
                                }
                                int i3 = iArr[0];
                                int i4 = iArr[1];
                                if (i3 <= 0 || i4 <= 0 || ((long) i3) * ((long) i4) > iArr.length - 2) {
                                    throw new IOException("RAW size invalid");
                                }
                                Bitmap bitmapCreateBitmap = Bitmap.createBitmap(i3, i4, Bitmap.Config.ARGB_8888);
                                bitmapCreateBitmap.setPixels(iArr, 2, i3, 0, 0, i3, i4);
                                bitmapDecodeByteArray = bitmapCreateBitmap;
                            }
                            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                            if (!bitmapDecodeByteArray.compress(Bitmap.CompressFormat.JPEG, 95, byteArrayOutputStream)) {
                                throw new IOException("Import JPEG encoding failed");
                            }
                            byteArray = byteArrayOutputStream.toByteArray();
                            bitmapDecodeByteArray.recycle();
                        }
                        byte[] bArrRender = MomentBridge.render(applicationContext, byteArray, null, iArrChoice);
                        ContentValues contentValues = new ContentValues();
                        contentValues.put("_display_name", "LMoment_" + System.currentTimeMillis() + ".jpg");
                        contentValues.put("mime_type", "image/jpeg");
                        if (Build.VERSION.SDK_INT >= 29) {
                            contentValues.put("relative_path", "DCIM/Camera");
                            contentValues.put("is_pending", (Integer) 1);
                        }
                        uriInsert = applicationContext.getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, contentValues);
                        try {
                            if (uriInsert == null) {
                                throw new IOException("Cannot create output photo");
                            }
                            OutputStream outputStreamOpenOutputStream = applicationContext.getContentResolver().openOutputStream(uriInsert);
                            if (outputStreamOpenOutputStream == null) {
                                throw new IOException("Cannot write output photo");
                            }
                            try {
                                outputStreamOpenOutputStream.write(bArrRender);
                                outputStreamOpenOutputStream.close();
                                if (Build.VERSION.SDK_INT >= 29) {
                                    ContentValues contentValues2 = new ContentValues();
                                    contentValues2.put("is_pending", (Integer) 0);
                                    applicationContext.getContentResolver().update(uriInsert, contentValues2, null, null);
                                }
                                MomentBridge.notice(applicationContext, "影调照片已保存");
                                if (0 != 0) {
                                    applicationContext.getContentResolver().delete(null, null, null);
                                }
                            } catch (Throwable th) {
                                outputStreamOpenOutputStream.close();
                                throw th;
                            }
                        } catch (Exception e) {
                            e = e;
                            Log.e(MomentBridge.TAG, "Import failed", e);
                            MomentBridge.notice(applicationContext, "导入处理失败：" + e.getClass().getSimpleName());
                            if (uriInsert != null) {
                                applicationContext.getContentResolver().delete(uriInsert, null, null);
                            }
                        } catch (LinkageError e2) {
                            MomentBridge.notice(applicationContext, "此文件的模型或 RAW 解码器无法使用");
                            if (uriInsert != null) {
                                applicationContext.getContentResolver().delete(uriInsert, null, null);
                            }
                        } catch (OutOfMemoryError e3) {
                            MomentBridge.notice(applicationContext, "内存不足，导入处理未完成");
                            if (uriInsert != null) {
                                applicationContext.getContentResolver().delete(uriInsert, null, null);
                            }
                        }
                    } catch (Throwable th2) {
                        th = th2;
                        if (0 != 0) {
                            applicationContext.getContentResolver().delete(null, null, null);
                        }
                        throw th;
                    }
                } catch (Exception e4) {
                    e = e4;
                    uriInsert = null;
                } catch (LinkageError e5) {
                    uriInsert = null;
                } catch (OutOfMemoryError e6) {
                    uriInsert = null;
                } catch (Throwable th3) {
                    th = th3;
                    if (0 != 0) {
                        applicationContext.getContentResolver().delete(null, null, null);
                    }
                    throw th;
                }
            }
        }, "LMoment-import").start();
        return true;
    }

    private static final class Hdr {
        private Hdr() {
        }

        static void transfer(Bitmap bitmap, Bitmap bitmap2, byte[] bArr, boolean z) {
            if (Build.VERSION.SDK_INT < 34) {
                return;
            }
            try {
                if (Boolean.TRUE.equals(Bitmap.class.getMethod("hasGainmap", new Class[0]).invoke(bitmap, new Object[0]))) {
                    Object objInvoke = Bitmap.class.getMethod("getGainmap", new Class[0]).invoke(bitmap, new Object[0]);
                    Class<?> cls = Class.forName("android.graphics.Gainmap");
                    Bitmap bitmap3 = (Bitmap) cls.getMethod("getGainmapContents", new Class[0]).invoke(objInvoke, new Object[0]);
                    Object objNewInstance = Class.forName("android.media.ExifInterface").getConstructor(InputStream.class).newInstance(new ByteArrayInputStream(bArr));
                    int iIntValue = ((Integer) objNewInstance.getClass().getMethod("getAttributeInt", String.class, Integer.TYPE).invoke(objNewInstance, ExifInterface.TAG_ORIENTATION, 1)).intValue();
                    Matrix matrix = new Matrix();
                    switch (iIntValue) {
                        case 2:
                            matrix.setScale(-1.0f, 1.0f);
                            break;
                        case 3:
                            matrix.setRotate(180.0f);
                            break;
                        case 4:
                            matrix.setRotate(180.0f);
                            matrix.postScale(-1.0f, 1.0f);
                            break;
                        case ExifInterface.ORIENTATION_TRANSPOSE /* 5 */:
                            matrix.setRotate(90.0f);
                            matrix.postScale(-1.0f, 1.0f);
                            break;
                        case 6:
                            matrix.setRotate(90.0f);
                            break;
                        case 7:
                            matrix.setRotate(270.0f);
                            matrix.postScale(-1.0f, 1.0f);
                            break;
                        case 8:
                            matrix.setRotate(270.0f);
                            break;
                    }
                    Object objNewInstance2 = cls.getConstructor(Bitmap.class).newInstance(Bitmap.createBitmap(bitmap3, 0, 0, bitmap3.getWidth(), bitmap3.getHeight(), matrix, false).copy(Bitmap.Config.ARGB_8888, true));
                    for (String str : new String[]{"RatioMin", "RatioMax", ExifInterface.TAG_GAMMA, "EpsilonSdr", "EpsilonHdr"}) {
                        float[] fArr = (float[]) cls.getMethod("get" + str, new Class[0]).invoke(objInvoke, new Object[0]);
                        if (z) {
                            float f = (0.2126f * fArr[0]) + (0.7152f * fArr[1]) + (fArr[2] * 0.0722f);
                            fArr = new float[]{f, f, f};
                        }
                        cls.getMethod("set" + str, Float.TYPE, Float.TYPE, Float.TYPE).invoke(objNewInstance2, Float.valueOf(fArr[0]), Float.valueOf(fArr[1]), Float.valueOf(fArr[2]));
                    }
                    for (String str2 : new String[]{"MinDisplayRatioForHdrTransition", "DisplayRatioForFullHdr"}) {
                        cls.getMethod("set" + str2, Float.TYPE).invoke(objNewInstance2, Float.valueOf(((Float) cls.getMethod("get" + str2, new Class[0]).invoke(objInvoke, new Object[0])).floatValue()));
                    }
                    Bitmap.class.getMethod("setGainmap", cls).invoke(bitmap2, objNewInstance2);
                }
            } catch (Exception e) {
                Log.w(MomentBridge.TAG, "Transfer HDR gain map", e);
            }
        }
    }
}
