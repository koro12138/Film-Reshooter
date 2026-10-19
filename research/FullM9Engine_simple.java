package com.codex.fullm9;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorSpace;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.hardware.camera2.CaptureResult;
import android.media.ExifInterface;
import android.util.Log;
import com.codex.lmport.MomentBridge;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.Field;
import java.util.Iterator;
import java.util.Locale;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes17.dex */
public final class FullM9Engine {
    private static final Object LOCK = null;

    private static final class HdrCopy {
        private HdrCopy() {
        }

        static void copy(Bitmap r1, Bitmap r2) {
            if (r1 != r2) goto L4;
            return;
        L4:
            if (r1.hasGainmap() == false) goto L8;
            r2.setGainmap(r1.getGainmap());
            return;
        }
    }

    static final class Settings {
        int cct;
        int lux;
        String provenance;
        float zoom;

        Settings() {
            this.lux = 300;
            this.cct = 5000;
            this.zoom = 1.0f;
            this.provenance = "reference";
        }
    }

    public FullM9Engine() {
    }

    static {
        LOCK = renderLock();
    }

    static Object renderLock() {
        Field r0 = MomentBridge.class.getDeclaredField("RENDER");     // Catch: Exception -> L4
        r0.setAccessible(true);     // Catch: Exception -> L4
        return r0.get(null);
    L5:
        return MomentBridge.class;
    }

    static Settings settings(byte[] r13, Object r14) {
        if ((r14 instanceof CaptureSnapshot) == true) goto L5;
        Settings r1 = new Settings();
        ExifInterface r2 = new ExifInterface(new ByteArrayInputStream(r13));     // Catch: Exception -> L18
        double r5 = r2.getAttributeDouble("ExposureTime", 0.0d);     // Catch: Exception -> L18
        double r7 = r2.getAttributeDouble("FNumber", 0.0d);     // Catch: Exception -> L18
        double r9 = r2.getAttributeDouble("PhotographicSensitivity", r2.getAttributeDouble("ISOSpeedRatings", 0.0d));     // Catch: Exception -> L18
        if (r5 > 0.0d) goto L10;
    L14:
        double r3 = r2.getAttributeDouble("FocalLengthIn35mmFilm", 0.0d);     // Catch: Exception -> L18
        if (r3 < 50.0d) goto L20;
        r1.zoom = (float) Math.max(3.2d, Math.min(4.3d, r3 / 23.0d));     // Catch: Exception -> L18
    L20:
        Object r15 = captureResult(r14);
        if ((r15 instanceof CaptureResult) == false) goto L67;
        CaptureResult r16 = (CaptureResult) r15;
        Iterator<CaptureResult.Key<?>> r17 = r16.getKeys().iterator();
    L24:
        if (r17.hasNext() == false) goto L67;
        CaptureResult.Key<?> r4 = r17.next();
        String r6 = r4.getName().toLowerCase(Locale.US);     // Catch: Exception -> L65
        Object r8 = r16.get(r4);     // Catch: Exception -> L65
        if ((r8 instanceof Number) == false) goto L31;
        float r10 = ((Number) r8).floatValue();     // Catch: Exception -> L65
    L37:
        if (Float.isFinite(r10) == false) goto L24;
        if (r6.contains("luxindex") == true) goto L44;
        if (r6.contains("lux_index") == true) goto L44;
    L49:
        if (r6.endsWith("cct") == true) goto L55;
        if (r6.contains("colortemperature") == true) goto L55;
        if (r6.contains("color_temperature") == true) goto L55;
    L60:
        if (r6.equals("android.control.zoomratio") == false) goto L24;
        if (r10 <= 0.0f) goto L24;
        r1.zoom = r10;     // Catch: Exception -> L65
    L55:
        if (r10 < 1500.0f) goto L60;
        if (r10 > 20000.0f) goto L60;
        r1.cct = Math.round(r10);     // Catch: Exception -> L65
        r1.provenance = String.valueOf(r1.provenance) + " capture CCT";     // Catch: Exception -> L65
    L44:
        if (r10 < 0.0f) goto L49;
        if (r10 > 1000.0f) goto L49;
        r1.lux = Math.round(r10);     // Catch: Exception -> L65
        r1.provenance = "capture lux";     // Catch: Exception -> L65
        goto L49
    L31:
        if ((r8 instanceof float[]) == true) goto L33;
    L35:
        r10 = Float.NaN;
        goto L37
    L33:
        if (((float[]) r8).length <= 0) goto L35;
        r10 = ((float[]) r8)[0];     // Catch: Exception -> L65
    L65:
        e = move-exception;
        Log.d("FullM9", "Capture trigger key unavailable", e);
    L67:
        return r1;
    L10:
        if (r7 <= 0.0d) goto L14;
        if (r9 <= 0.0d) goto L14;
        r1.lux = (int) Math.max(0.0d, Math.min(999.0d, 474.9d - (((Math.log((r7 * r7) / r5) / Math.log(2.0d)) - (Math.log(r9 / 100.0d) / Math.log(2.0d))) * 23.45d)));     // Catch: Exception -> L18
        r1.provenance = "EXIF EV estimate";     // Catch: Exception -> L18
    L18:
        e = move-exception;
        Log.d("FullM9", "No EXIF metering", e);
        goto L20
    L5:
        return ((CaptureSnapshot) r14).settings();
    }

    static Object captureResult(Object r3) {
        Object r0 = Reflect.field(r3, "f");
        Object r1 = Reflect.field(r0, "b");
        if ((r1 instanceof CaptureResult) == true) goto L6;
        r1 = Reflect.field(r0, "c");
    L6:
        if ((r1 instanceof CaptureResult) == true) goto L9;
        r1 = Reflect.field(r3, "legendaryPreviewResult");
    L9:
        if ((r1 instanceof CaptureResult) == true) goto L13;
        return null;
    L13:
        return r1;
    }

    static byte[] metadata(byte[] r9, byte[] r10, int r11, int r12) throws Exception {
        return ExifOrientation.upright((byte[]) Reflect.call(Class.forName("com.codex.leicaapp.JpegMetadata"), "copyExif", new Class[]{byte[].class, byte[].class, Boolean.TYPE, Integer.TYPE, Integer.TYPE, Boolean.TYPE}, new Object[]{r9, r10, true, Integer.valueOf(r11), Integer.valueOf(r12), true}));
    }

    static void recycle(Bitmap r1) {
        if (r1 != null) goto L4;
        return;
    L4:
        if (r1.isRecycled() == true) goto L8;
        r1.recycle();
        return;
    }

    static Bitmap p3(Bitmap r5) {
        Bitmap r0 = Bitmap.createBitmap(r5.getWidth(), r5.getHeight(), Bitmap.Config.ARGB_8888, false, ColorSpace.get(ColorSpace.Named.DISPLAY_P3));
        new Canvas(r0).drawBitmap(r5, 0.0f, 0.0f, new Paint(3));
        return r0;
    }

    static Bitmap rotate(Bitmap r7, float r8) {
        Matrix r5 = new Matrix();
        r5.setRotate(r8);
        return Bitmap.createBitmap(r7, 0, 0, r7.getWidth(), r7.getHeight(), r5, false);
    }

    static float boost(Bitmap r11) {
        int r3 = r11.getWidth();
        int r8 = r11.getHeight();
        int[] r1 = new int[r3];
        int r5 = 0;
        int r10 = 0;
    L3:
        if (r5 >= r8) goto L4;
        Bitmap r0 = r11;
        r0.getPixels(r1, 0, r3, 0, r5, r3, 1);
        int r12 = 0;
    L14:
        if (r12 >= r3) goto L15;
        if ((r1[r12] & 255) < 250) goto L19;
        r10 = r10 + 1;
    L19:
        r12 = r12 + 1;
        goto L14
    L15:
        r5 = r5 + 1;
        r11 = r0;
        goto L3
    L4:
        double r4 = (((double) r10) * 100.0d) / (((long) r3) * ((long) r8));
        double r2 = 1.0d;
        if (r4 <= 8.0d) goto L12;
        if (r4 < 20.0d) goto L10;
        r2 = 0.8d;
        goto L12
    L10:
        r2 = 1.0d - (((r4 - 8.0d) / 12.0d) * 0.2d);
    L12:
        return ((int) (r2 * 500.0d)) / 100.0f;
    }

    static byte[] rawExif(Context r30, byte[] r31, int r32, int r33) throws Exception {
        Bitmap r1 = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888);
        ByteArrayOutputStream r3 = new ByteArrayOutputStream();
        r1.compress(Bitmap.CompressFormat.JPEG, 97, r3);     // Catch: Throwable -> L64
        r1.recycle();
        if (r31.length > 1) goto L7;
    L12:
        File r2 = File.createTempFile("fullm9-meta-", ".jpg", r30.getCacheDir());
        Throwable r6 = null;
        FileOutputStream r7 = new FileOutputStream(r2);     // Catch: Throwable -> L55
        r7.write(r3.toByteArray());     // Catch: Throwable -> L51
        r7.close();     // Catch: Throwable -> L55
        ExifInterface r4 = new ExifInterface(new ByteArrayInputStream(r31));     // Catch: IOException -> L18 Throwable -> L61
    L20:
        ExifInterface r0 = new ExifInterface(r2.getAbsolutePath());     // Catch: Throwable -> L61
        String[] r8 = {"Make", "Model", "ExposureTime", "FNumber", "PhotographicSensitivity", "ISOSpeedRatings", "FocalLength", "FocalLengthIn35mmFilm", "DateTime", "DateTimeOriginal", "DateTimeDigitized", "ExposureBiasValue", "WhiteBalance", "GPSLatitude", "GPSLatitudeRef", "GPSLongitude", "GPSLongitudeRef", "GPSAltitude", "GPSAltitudeRef", "GPSTimeStamp", "GPSDateStamp", "LensModel"};     // Catch: Throwable -> L61
        int r9 = 0;
    L22:
        if (r9 >= 22) goto L23;
        String r10 = r8[r9];     // Catch: Throwable -> L61
        if (r4 != null) goto L47;
        String r11 = null;
    L48:
        if (r11 == null) goto L50;
        r0.setAttribute(r10, r11);     // Catch: Throwable -> L61
    L50:
        r9 = r9 + 1;
        goto L22
    L47:
        r11 = r4.getAttribute(r10);     // Catch: Throwable -> L61
        goto L48
    L23:
        r0.setAttribute("Orientation", "1");     // Catch: Throwable -> L61
        r0.setAttribute("ImageWidth", Integer.toString(r32));     // Catch: Throwable -> L61
        r0.setAttribute("ImageLength", Integer.toString(r33));     // Catch: Throwable -> L61
        r0.setAttribute("PixelXDimension", Integer.toString(r32));     // Catch: Throwable -> L61
        r0.setAttribute("PixelYDimension", Integer.toString(r33));     // Catch: Throwable -> L61
        r0.saveAttributes();     // Catch: Throwable -> L61
        FileInputStream r5 = new FileInputStream(r2);     // Catch: Throwable -> L38
        ByteArrayOutputStream r12 = new ByteArrayOutputStream();     // Catch: Throwable -> L34
        byte[] r13 = new byte[8192];     // Catch: Throwable -> L34
    L26:
        int r14 = r5.read(r13);     // Catch: Throwable -> L34
        if (r14 == (-1)) goto L28;
        r12.write(r13, 0, r14);     // Catch: Throwable -> L34
        goto L26
    L28:
        byte[] r15 = r12.toByteArray();     // Catch: Throwable -> L34
        r5.close();     // Catch: Throwable -> L38
        r2.delete();
        return r15;
    L34:
        th = move-exception;
        r5.close();     // Catch: Throwable -> L38
        throw th;     // Catch: Throwable -> L38
    L38:
        th = move-exception;
        if (0 == 0) goto L82;
        if (null == th) goto L43;
        r6.addSuppressed(th);     // Catch: Throwable -> L61
    L43:
        throw null;     // Catch: Throwable -> L61
    L82:
        throw th;     // Catch: Throwable -> L61
    L18:
        e = move-exception;
        Log.d("FullM9", "No readable source EXIF", e);     // Catch: Throwable -> L61
        r4 = null;
        goto L20
    L51:
        th = move-exception;
        r7.close();     // Catch: Throwable -> L55
        throw th;     // Catch: Throwable -> L55
    L55:
        th = move-exception;
        if (0 == 0) goto L83;
        if (null == th) goto L60;
        r6.addSuppressed(th);     // Catch: Throwable -> L61
    L60:
        throw null;     // Catch: Throwable -> L61
    L83:
        throw th;     // Catch: Throwable -> L61
    L61:
        th = move-exception;
        r2.delete();
        throw th;
    L7:
        if ((r31[0] & 255) != 255) goto L12;
        if ((r31[1] & 255) != 216) goto L12;
        return metadata(r31, r3.toByteArray(), r32, r33);
    L64:
        th = move-exception;
        r1.recycle();
        throw th;
    }

    /*  JADX ERROR: Type inference failed
        jadx.core.utils.exceptions.JadxOverflowException: Type inference error: updates count limit reached with updateSeq = 19161. Try increasing type updates limit count.
        	at jadx.core.utils.ErrorsCounter.addError(ErrorsCounter.java:59)
        	at jadx.core.utils.ErrorsCounter.error(ErrorsCounter.java:31)
        	at jadx.core.dex.attributes.nodes.NotificationAttrNode.addError(NotificationAttrNode.java:19)
        	at jadx.core.dex.visitors.typeinference.TypeInferenceVisitor.visit(TypeInferenceVisitor.java:79)
        */
    public static byte[] render(android.content.Context r42, byte[] r43, java.lang.Object r44, int[] r45) throws java.lang.Exception {
        /*  JADX ERROR: Simple mode code generation failed
            jadx.core.utils.exceptions.CodegenException: Error generate insn: 0x0002: MOVE (r2v0 ?? I:byte[] A[IMMUTABLE_TYPE]) = (r43v0 byte[]) A[DECLARE_VAR] in method: com.codex.fullm9.FullM9Engine.render(android.content.Context, byte[], java.lang.Object, int[]):byte[], file: D:\￦ﾑﾄ￥ﾽﾱ\CameraLookDesktop\research\classes17.dex
            	at jadx.core.codegen.InsnGen.makeInsn(InsnGen.java:310)
            	at jadx.core.codegen.InsnGen.makeInsn(InsnGen.java:273)
            	at jadx.core.codegen.MethodGen.generateSimpleCode(MethodGen.java:348)
            	at jadx.core.codegen.MethodGen.addSimpleMethodCode(MethodGen.java:316)
            	at jadx.core.codegen.MethodGen.addInstructions(MethodGen.java:279)
            	at jadx.core.codegen.ClassGen.addMethodCode(ClassGen.java:420)
            	at jadx.core.codegen.ClassGen.addMethod(ClassGen.java:345)
            	at jadx.core.codegen.ClassGen.lambda$addInnerClsAndMethods$3(ClassGen.java:299)
            	at java.base/java.util.stream.ForEachOps$ForEachOp$OfRef.accept(ForEachOps.java:183)
            	at java.base/java.util.ArrayList.forEach(ArrayList.java:1511)
            	at java.base/java.util.stream.SortedOps$RefSortingSink.end(SortedOps.java:395)
            	at java.base/java.util.stream.Sink$ChainedReference.end(Sink.java:258)
            Caused by: java.lang.NullPointerException: Cannot invoke "jadx.core.dex.instructions.args.ArgType.getPrimitiveType()" because "type" is null
            	at jadx.core.codegen.ClassGen.useType(ClassGen.java:564)
            	at jadx.core.codegen.InsnGen.useType(InsnGen.java:269)
            	at jadx.core.codegen.InsnGen.declareVar(InsnGen.java:166)
            	at jadx.core.codegen.InsnGen.declareVar(InsnGen.java:159)
            	at jadx.core.codegen.InsnGen.assignVar(InsnGen.java:152)
            	at jadx.core.codegen.InsnGen.makeInsn(InsnGen.java:299)
            	... 11 more
            */
        /*
            Method dump skipped, instruction units count: 1916
            To view this dump add '--comments-level debug' option
        */
        throw new UnsupportedOperationException("Method not decompiled: com.codex.fullm9.FullM9Engine.render(android.content.Context, byte[], java.lang.Object, int[]):byte[]");
    }

    static void failure(Context r4, Throwable r5) {
        if ((r5 instanceof CloudGraph.PreparedStop) == false) goto L5;
        return;
    L5:
        CaptureTrace.failed(r4, r5);
        Log.e("FullM9", "M9 capture failed", r5);
        if (r4 == null) goto L28;
        Throwable r0 = null;
        PrintWriter r1 = new PrintWriter(new File(r4.getFilesDir(), "fullm9-last-error.txt"), "UTF-8");     // Catch: Throwable -> L14
        r5.printStackTrace(r1);     // Catch: Throwable -> L11
        r1.close();     // Catch: Throwable -> L14
        return;
    L11:
        th = move-exception;
        r1.close();     // Catch: Throwable -> L14
        throw th;     // Catch: Throwable -> L14
    L14:
        th = move-exception;
        if (0 == 0) goto L27;
        if (null == th) goto L19;
        r0.addSuppressed(th);     // Catch: Exception -> L20
    L21:
        return;
    L19:
        throw null;     // Catch: Exception -> L20
        goto L21
    L27:
        throw th;     // Catch: Exception -> L20
    }
}
