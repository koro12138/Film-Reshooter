package com.codex.fullm9;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes17.dex */
public final class FullM9Engine {
    private static final java.lang.Object LOCK = null;

    private static final class HdrCopy {
        private HdrCopy() {
                r0 = this;
                r0.<init>()
                return
        }

        static void copy(android.graphics.Bitmap r1, android.graphics.Bitmap r2) {
                if (r1 == r2) goto Lf
                boolean r0 = r1.hasGainmap()
                if (r0 == 0) goto Lf
                android.graphics.Gainmap r1 = r1.getGainmap()
                r2.setGainmap(r1)
            Lf:
                return
        }
    }

    static final class Settings {
        int cct;
        int lux;
        java.lang.String provenance;
        float zoom;

        Settings() {
                r1 = this;
                r1.<init>()
                r0 = 300(0x12c, float:4.2E-43)
                r1.lux = r0
                r0 = 5000(0x1388, float:7.006E-42)
                r1.cct = r0
                r0 = 1065353216(0x3f800000, float:1.0)
                r1.zoom = r0
                java.lang.String r0 = "reference"
                r1.provenance = r0
                return
        }
    }

    static {
            java.lang.Object r0 = renderLock()
            com.codex.fullm9.FullM9Engine.LOCK = r0
            return
    }

    public FullM9Engine() {
            r0 = this;
            r0.<init>()
            return
    }

    static float boost(android.graphics.Bitmap r11) {
            int r3 = r11.getWidth()
            int r8 = r11.getHeight()
            int[] r1 = new int[r3]
            r9 = 0
            r5 = r9
            r10 = r5
        Ld:
            if (r5 < r8) goto L44
            r0 = 4636737291354636288(0x4059000000000000, double:100.0)
            double r4 = (double) r10
            double r4 = r4 * r0
            long r0 = (long) r3
            long r2 = (long) r8
            long r0 = r0 * r2
            double r0 = (double) r0
            double r4 = r4 / r0
            r0 = 4620693217682128896(0x4020000000000000, double:8.0)
            int r11 = (r4 > r0 ? 1 : (r4 == r0 ? 0 : -1))
            r2 = 4607182418800017408(0x3ff0000000000000, double:1.0)
            if (r11 > 0) goto L21
            goto L38
        L21:
            r6 = 4626322717216342016(0x4034000000000000, double:20.0)
            int r11 = (r4 > r6 ? 1 : (r4 == r6 ? 0 : -1))
            if (r11 < 0) goto L2d
            r2 = 4605380978949069210(0x3fe999999999999a, double:0.8)
            goto L38
        L2d:
            double r4 = r4 - r0
            r0 = 4622945017495814144(0x4028000000000000, double:12.0)
            double r4 = r4 / r0
            r0 = 4596373779694328218(0x3fc999999999999a, double:0.2)
            double r4 = r4 * r0
            double r2 = r2 - r4
        L38:
            r0 = 4647503709213818880(0x407f400000000000, double:500.0)
            double r2 = r2 * r0
            int r11 = (int) r2
            float r11 = (float) r11
            r0 = 1120403456(0x42c80000, float:100.0)
            float r11 = r11 / r0
            return r11
        L44:
            r4 = 0
            r7 = 1
            r2 = 0
            r6 = r3
            r0 = r11
            r0.getPixels(r1, r2, r3, r4, r5, r6, r7)
            r11 = r9
        L4d:
            if (r11 < r3) goto L53
            int r5 = r5 + 1
            r11 = r0
            goto Ld
        L53:
            r2 = r1[r11]
            r2 = r2 & 255(0xff, float:3.57E-43)
            r4 = 250(0xfa, float:3.5E-43)
            if (r2 < r4) goto L5d
            int r10 = r10 + 1
        L5d:
            int r11 = r11 + 1
            goto L4d
    }

    static java.lang.Object captureResult(java.lang.Object r3) {
            java.lang.String r0 = "f"
            java.lang.Object r0 = com.codex.fullm9.Reflect.field(r3, r0)
            java.lang.String r1 = "b"
            java.lang.Object r1 = com.codex.fullm9.Reflect.field(r0, r1)
            boolean r2 = r1 instanceof android.hardware.camera2.CaptureResult
            if (r2 != 0) goto L16
            java.lang.String r1 = "c"
            java.lang.Object r1 = com.codex.fullm9.Reflect.field(r0, r1)
        L16:
            boolean r0 = r1 instanceof android.hardware.camera2.CaptureResult
            if (r0 != 0) goto L20
            java.lang.String r0 = "legendaryPreviewResult"
            java.lang.Object r1 = com.codex.fullm9.Reflect.field(r3, r0)
        L20:
            boolean r3 = r1 instanceof android.hardware.camera2.CaptureResult
            if (r3 == 0) goto L25
            goto L26
        L25:
            r1 = 0
        L26:
            return r1
    }

    static void failure(android.content.Context r4, java.lang.Throwable r5) {
            boolean r0 = r5 instanceof com.codex.fullm9.CloudGraph.PreparedStop
            if (r0 == 0) goto L5
            return
        L5:
            com.codex.fullm9.CaptureTrace.failed(r4, r5)
            java.lang.String r0 = "FullM9"
            java.lang.String r1 = "M9 capture failed"
            android.util.Log.e(r0, r1, r5)
            if (r4 == 0) goto L3b
            r0 = 0
            java.io.PrintWriter r1 = new java.io.PrintWriter     // Catch: java.lang.Throwable -> L30
            java.io.File r2 = new java.io.File     // Catch: java.lang.Throwable -> L30
            java.io.File r4 = r4.getFilesDir()     // Catch: java.lang.Throwable -> L30
            java.lang.String r3 = "fullm9-last-error.txt"
            r2.<init>(r4, r3)     // Catch: java.lang.Throwable -> L30
            java.lang.String r4 = "UTF-8"
            r1.<init>(r2, r4)     // Catch: java.lang.Throwable -> L30
            r5.printStackTrace(r1)     // Catch: java.lang.Throwable -> L2b
            r1.close()     // Catch: java.lang.Throwable -> L30
            goto L3b
        L2b:
            r0 = move-exception
            r1.close()     // Catch: java.lang.Throwable -> L30
            throw r0     // Catch: java.lang.Throwable -> L30
        L30:
            r4 = move-exception
            if (r0 == 0) goto L39
            if (r0 == r4) goto L38
            r0.addSuppressed(r4)     // Catch: java.lang.Exception -> L3a
        L38:
            r4 = r0
        L39:
            throw r4     // Catch: java.lang.Exception -> L3a
        L3a:
            r4 = move-exception
        L3b:
            return
    }

    static byte[] metadata(byte[] r9, byte[] r10, int r11, int r12) throws java.lang.Exception {
            java.lang.String r0 = "com.codex.leicaapp.JpegMetadata"
            java.lang.Class r0 = java.lang.Class.forName(r0)
            java.lang.Class r3 = java.lang.Boolean.TYPE
            java.lang.Class r4 = java.lang.Integer.TYPE
            java.lang.Class r5 = java.lang.Integer.TYPE
            java.lang.Class r6 = java.lang.Boolean.TYPE
            java.lang.Class<byte[]> r1 = byte[].class
            java.lang.Class<byte[]> r2 = byte[].class
            java.lang.Class[] r1 = new java.lang.Class[]{r1, r2, r3, r4, r5, r6}
            r2 = 1
            java.lang.Boolean r5 = java.lang.Boolean.valueOf(r2)
            java.lang.Integer r6 = java.lang.Integer.valueOf(r11)
            java.lang.Integer r7 = java.lang.Integer.valueOf(r12)
            r8 = r5
            r3 = r9
            r4 = r10
            java.lang.Object[] r9 = new java.lang.Object[]{r3, r4, r5, r6, r7, r8}
            java.lang.String r10 = "copyExif"
            java.lang.Object r9 = com.codex.fullm9.Reflect.call(r0, r10, r1, r9)
            byte[] r9 = (byte[]) r9
            byte[] r9 = com.codex.fullm9.ExifOrientation.upright(r9)
            return r9
    }

    static android.graphics.Bitmap p3(android.graphics.Bitmap r5) {
            int r0 = r5.getWidth()
            int r1 = r5.getHeight()
            android.graphics.Bitmap$Config r2 = android.graphics.Bitmap.Config.ARGB_8888
            android.graphics.ColorSpace$Named r3 = android.graphics.ColorSpace.Named.DISPLAY_P3
            android.graphics.ColorSpace r3 = android.graphics.ColorSpace.get(r3)
            r4 = 0
            android.graphics.Bitmap r0 = android.graphics.Bitmap.createBitmap(r0, r1, r2, r4, r3)
            android.graphics.Canvas r1 = new android.graphics.Canvas
            r1.<init>(r0)
            android.graphics.Paint r2 = new android.graphics.Paint
            r3 = 3
            r2.<init>(r3)
            r3 = 0
            r1.drawBitmap(r5, r3, r3, r2)
            return r0
    }

    static byte[] rawExif(android.content.Context r30, byte[] r31, int r32, int r33) throws java.lang.Exception {
            r0 = r31
            android.graphics.Bitmap$Config r1 = android.graphics.Bitmap.Config.ARGB_8888
            r2 = 1
            android.graphics.Bitmap r1 = android.graphics.Bitmap.createBitmap(r2, r2, r1)
            java.io.ByteArrayOutputStream r3 = new java.io.ByteArrayOutputStream
            r3.<init>()
            android.graphics.Bitmap$CompressFormat r4 = android.graphics.Bitmap.CompressFormat.JPEG     // Catch: java.lang.Throwable -> L132
            r5 = 97
            r1.compress(r4, r5, r3)     // Catch: java.lang.Throwable -> L132
            r1.recycle()
            int r1 = r0.length
            r4 = 0
            if (r1 <= r2) goto L37
            r1 = r0[r4]
            r5 = 255(0xff, float:3.57E-43)
            r1 = r1 & r5
            if (r1 != r5) goto L37
            r1 = r0[r2]
            r1 = r1 & r5
            r2 = 216(0xd8, float:3.03E-43)
            if (r1 != r2) goto L37
            byte[] r1 = r3.toByteArray()
            r2 = r32
            r5 = r33
            byte[] r0 = metadata(r0, r1, r2, r5)
            return r0
        L37:
            r2 = r32
            r5 = r33
            java.lang.String r1 = ".jpg"
            java.io.File r6 = r30.getCacheDir()
            java.lang.String r7 = "fullm9-meta-"
            java.io.File r1 = java.io.File.createTempFile(r7, r1, r6)
            r6 = 0
            java.io.FileOutputStream r7 = new java.io.FileOutputStream     // Catch: java.lang.Throwable -> L123
            r7.<init>(r1)     // Catch: java.lang.Throwable -> L123
            byte[] r3 = r3.toByteArray()     // Catch: java.lang.Throwable -> L11d
            r7.write(r3)     // Catch: java.lang.Throwable -> L11d
            r7.close()     // Catch: java.lang.Throwable -> L123
            android.media.ExifInterface r3 = new android.media.ExifInterface     // Catch: java.io.IOException -> L62 java.lang.Throwable -> L12d
            java.io.ByteArrayInputStream r7 = new java.io.ByteArrayInputStream     // Catch: java.io.IOException -> L62 java.lang.Throwable -> L12d
            r7.<init>(r0)     // Catch: java.io.IOException -> L62 java.lang.Throwable -> L12d
            r3.<init>(r7)     // Catch: java.io.IOException -> L62 java.lang.Throwable -> L12d
            goto L6b
        L62:
            r0 = move-exception
            java.lang.String r3 = "FullM9"
            java.lang.String r7 = "No readable source EXIF"
            android.util.Log.d(r3, r7, r0)     // Catch: java.lang.Throwable -> L12d
            r3 = r6
        L6b:
            android.media.ExifInterface r0 = new android.media.ExifInterface     // Catch: java.lang.Throwable -> L12d
            java.lang.String r7 = r1.getAbsolutePath()     // Catch: java.lang.Throwable -> L12d
            r0.<init>(r7)     // Catch: java.lang.Throwable -> L12d
            java.lang.String r8 = "Make"
            java.lang.String r9 = "Model"
            java.lang.String r10 = "ExposureTime"
            java.lang.String r11 = "FNumber"
            java.lang.String r12 = "PhotographicSensitivity"
            java.lang.String r13 = "ISOSpeedRatings"
            java.lang.String r14 = "FocalLength"
            java.lang.String r15 = "FocalLengthIn35mmFilm"
            java.lang.String r16 = "DateTime"
            java.lang.String r17 = "DateTimeOriginal"
            java.lang.String r18 = "DateTimeDigitized"
            java.lang.String r19 = "ExposureBiasValue"
            java.lang.String r20 = "WhiteBalance"
            java.lang.String r21 = "GPSLatitude"
            java.lang.String r22 = "GPSLatitudeRef"
            java.lang.String r23 = "GPSLongitude"
            java.lang.String r24 = "GPSLongitudeRef"
            java.lang.String r25 = "GPSAltitude"
            java.lang.String r26 = "GPSAltitudeRef"
            java.lang.String r27 = "GPSTimeStamp"
            java.lang.String r28 = "GPSDateStamp"
            java.lang.String r29 = "LensModel"
            java.lang.String[] r7 = new java.lang.String[]{r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29}     // Catch: java.lang.Throwable -> L12d
            r8 = r4
        La5:
            r9 = 22
            if (r8 < r9) goto L10b
            java.lang.String r3 = "Orientation"
            java.lang.String r7 = "1"
            r0.setAttribute(r3, r7)     // Catch: java.lang.Throwable -> L12d
            java.lang.String r3 = "ImageWidth"
            java.lang.String r7 = java.lang.Integer.toString(r2)     // Catch: java.lang.Throwable -> L12d
            r0.setAttribute(r3, r7)     // Catch: java.lang.Throwable -> L12d
            java.lang.String r3 = "ImageLength"
            java.lang.String r7 = java.lang.Integer.toString(r5)     // Catch: java.lang.Throwable -> L12d
            r0.setAttribute(r3, r7)     // Catch: java.lang.Throwable -> L12d
            java.lang.String r3 = "PixelXDimension"
            java.lang.String r2 = java.lang.Integer.toString(r2)     // Catch: java.lang.Throwable -> L12d
            r0.setAttribute(r3, r2)     // Catch: java.lang.Throwable -> L12d
            java.lang.String r2 = "PixelYDimension"
            java.lang.String r3 = java.lang.Integer.toString(r5)     // Catch: java.lang.Throwable -> L12d
            r0.setAttribute(r2, r3)     // Catch: java.lang.Throwable -> L12d
            r0.saveAttributes()     // Catch: java.lang.Throwable -> L12d
            java.io.FileInputStream r2 = new java.io.FileInputStream     // Catch: java.lang.Throwable -> L101
            r2.<init>(r1)     // Catch: java.lang.Throwable -> L101
            java.io.ByteArrayOutputStream r0 = new java.io.ByteArrayOutputStream     // Catch: java.lang.Throwable -> Lfb
            r0.<init>()     // Catch: java.lang.Throwable -> Lfb
            r3 = 8192(0x2000, float:1.14794E-41)
            byte[] r3 = new byte[r3]     // Catch: java.lang.Throwable -> Lfb
        Le5:
            int r5 = r2.read(r3)     // Catch: java.lang.Throwable -> Lfb
            r7 = -1
            if (r5 != r7) goto Lf7
            byte[] r0 = r0.toByteArray()     // Catch: java.lang.Throwable -> Lfb
            r2.close()     // Catch: java.lang.Throwable -> L101
            r1.delete()
            return r0
        Lf7:
            r0.write(r3, r4, r5)     // Catch: java.lang.Throwable -> Lfb
            goto Le5
        Lfb:
            r0 = move-exception
            r6 = r0
            r2.close()     // Catch: java.lang.Throwable -> L101
            throw r6     // Catch: java.lang.Throwable -> L101
        L101:
            r0 = move-exception
            if (r6 == 0) goto L10a
            if (r6 == r0) goto L109
            r6.addSuppressed(r0)     // Catch: java.lang.Throwable -> L12d
        L109:
            r0 = r6
        L10a:
            throw r0     // Catch: java.lang.Throwable -> L12d
        L10b:
            r9 = r7[r8]     // Catch: java.lang.Throwable -> L12d
            if (r3 != 0) goto L111
            r10 = r6
            goto L115
        L111:
            java.lang.String r10 = r3.getAttribute(r9)     // Catch: java.lang.Throwable -> L12d
        L115:
            if (r10 == 0) goto L11a
            r0.setAttribute(r9, r10)     // Catch: java.lang.Throwable -> L12d
        L11a:
            int r8 = r8 + 1
            goto La5
        L11d:
            r0 = move-exception
            r6 = r0
            r7.close()     // Catch: java.lang.Throwable -> L123
            throw r6     // Catch: java.lang.Throwable -> L123
        L123:
            r0 = move-exception
            if (r6 == 0) goto L12c
            if (r6 == r0) goto L12b
            r6.addSuppressed(r0)     // Catch: java.lang.Throwable -> L12d
        L12b:
            r0 = r6
        L12c:
            throw r0     // Catch: java.lang.Throwable -> L12d
        L12d:
            r0 = move-exception
            r1.delete()
            throw r0
        L132:
            r0 = move-exception
            r1.recycle()
            throw r0
    }

    static void recycle(android.graphics.Bitmap r1) {
            if (r1 == 0) goto Lb
            boolean r0 = r1.isRecycled()
            if (r0 != 0) goto Lb
            r1.recycle()
        Lb:
            return
    }

    public static byte[] render(android.content.Context r42, byte[] r43, java.lang.Object r44, int[] r45) throws java.lang.Exception {
            r1 = r42
            r2 = r43
            r3 = r44
            long r4 = java.lang.System.nanoTime()
            java.lang.Object r6 = com.codex.fullm9.FullM9Engine.LOCK
            monitor-enter(r6)
            long r7 = java.lang.System.nanoTime()     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.CaptureState r9 = new com.codex.fullm9.CaptureState     // Catch: java.lang.Throwable -> L779
            r9.<init>(r3)     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.FullM9Hdr.clear()     // Catch: java.lang.Throwable -> L779
            r0 = 2
            int[] r10 = new int[r0]     // Catch: java.lang.Throwable -> L779
            r11 = 8
            r12 = 0
            r10[r12] = r11     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.OutputQuality.begin(r10)     // Catch: java.lang.Throwable -> L779
            int[] r10 = new int[r0]     // Catch: java.lang.Throwable -> L779
            r10[r12] = r11     // Catch: java.lang.Throwable -> L779
            com.codex.lmport.DenoiseFlow.begin(r10)     // Catch: java.lang.Throwable -> L779
            r10 = 1
            if (r3 == 0) goto L34
            boolean r13 = r3 instanceof com.codex.fullm9.CaptureSnapshot     // Catch: java.lang.Throwable -> L779
            if (r13 != 0) goto L34
            r13 = r10
            goto L35
        L34:
            r13 = r12
        L35:
            com.codex.fullm9.CaptureTrace.start(r1, r13, r4)     // Catch: java.lang.Throwable -> L779
            int r15 = r2.length     // Catch: java.lang.Throwable -> L6f3 java.lang.Error -> L706 java.lang.Exception -> L71c
            r16 = 0
            r4 = 4
            if (r15 <= r4) goto L75
            r4 = r2[r12]     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r5 = 73
            if (r4 != r5) goto L48
            r4 = r2[r10]     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            if (r4 == r5) goto L52
        L48:
            r4 = r2[r12]     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r5 = 77
            if (r4 != r5) goto L75
            r4 = r2[r10]     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            if (r4 != r5) goto L75
        L52:
            r4 = r10
            goto L76
        L54:
            r0 = move-exception
            r1 = r16
            r10 = r1
        L58:
            r7 = 0
            r13 = 0
            r14 = 0
            goto L6fc
        L5d:
            r0 = move-exception
            r10 = r16
            r17 = r10
            r2 = 0
            r4 = 0
            r7 = 0
            r13 = 0
            r14 = 0
            goto L710
        L69:
            r0 = move-exception
            r10 = r16
            r17 = r10
            r2 = 0
            r4 = 0
            r7 = 0
            r13 = 0
            r14 = 0
            goto L726
        L75:
            r4 = r12
        L76:
            if (r4 == 0) goto L1b2
            com.codex.fullm9.DngMeta r4 = new com.codex.fullm9.DngMeta     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r4.<init>(r2)     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            com.codex.fullm9.FullM9Engine$Settings r5 = new com.codex.fullm9.FullM9Engine$Settings     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r5.<init>()     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r15 = r12
            double r11 = r4.lux     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            long r11 = java.lang.Math.round(r11)     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            int r11 = (int) r11     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r5.lux = r11     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            double r11 = r4.cct     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            long r11 = java.lang.Math.round(r11)     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            int r11 = (int) r11     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r5.cct = r11     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            double r11 = r4.zoom     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            float r11 = (float) r11     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r5.zoom = r11     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            java.lang.StringBuilder r11 = new java.lang.StringBuilder     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            java.lang.String r12 = "linear DNG "
            r11.<init>(r12)     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            java.lang.String r12 = r4.camera     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            java.lang.StringBuilder r11 = r11.append(r12)     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            java.lang.String r11 = r11.toString()     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            r5.provenance = r11     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            float[] r11 = r4.wb     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            long r18 = com.codex.fullm9.NativeM9.rawOpen(r2, r11)     // Catch: java.lang.Throwable -> L54 java.lang.Error -> L5d java.lang.Exception -> L69
            int[] r11 = com.codex.fullm9.NativeM9.rawSize(r18)     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            float[] r12 = com.codex.fullm9.NativeM9.rawStats(r18)     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            int r13 = r5.lux     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            r25 = r15
            double r14 = (double) r13     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            java.lang.String r13 = r4.camera     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            com.codex.fullm9.AE r33 = com.codex.fullm9.AE.meter(r1, r12, r14, r13)     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            com.codex.fullm9.Tuning r12 = new com.codex.fullm9.Tuning     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            r12.<init>(r1)     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            r13 = r11[r25]     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            r14 = r11[r10]     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            android.graphics.Bitmap$Config r15 = android.graphics.Bitmap.Config.ARGB_8888     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            android.graphics.Bitmap r22 = android.graphics.Bitmap.createBitmap(r13, r14, r15)     // Catch: java.lang.Throwable -> L189 java.lang.Error -> L190 java.lang.Exception -> L1a1
            r13 = r11[r25]     // Catch: java.lang.Throwable -> L16c java.lang.Error -> L173 java.lang.Exception -> L17e
            int r13 = r13 + r10
            int r13 = r13 / r0
            int r13 = r13 + r10
            r13 = r13 & (-2)
            r14 = r11[r10]     // Catch: java.lang.Throwable -> L16c java.lang.Error -> L173 java.lang.Exception -> L17e
            int r14 = r14 + r10
            int r14 = r14 / r0
            int r14 = r14 + r10
            r0 = r14 & (-2)
            android.graphics.Bitmap$Config r14 = android.graphics.Bitmap.Config.ARGB_8888     // Catch: java.lang.Throwable -> L16c java.lang.Error -> L173 java.lang.Exception -> L17e
            android.graphics.Bitmap r23 = android.graphics.Bitmap.createBitmap(r13, r0, r14)     // Catch: java.lang.Throwable -> L16c java.lang.Error -> L173 java.lang.Exception -> L17e
            java.lang.String r0 = r4.camera     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            double[] r13 = r4.cameraToSrgb     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            int r14 = r5.lux     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            double r14 = (double) r14     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            r35 = r10
            int r10 = r5.cct     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            r36 = r7
            double r7 = (double) r10     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            r34 = 0
            r27 = r0
            r31 = r7
            r26 = r12
            r28 = r13
            r29 = r14
            float[] r20 = r26.config(r27, r28, r29, r31, r33, r34)     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            java.lang.String r0 = r4.camera     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            double[] r4 = r4.cameraToSrgb     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            int r7 = r5.lux     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            double r7 = (double) r7     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            int r10 = r5.cct     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            double r12 = (double) r10     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            r34 = 1
            r27 = r0
            r28 = r4
            r29 = r7
            r31 = r12
            float[] r21 = r26.config(r27, r28, r29, r31, r33, r34)     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            com.codex.fullm9.NativeM9.rawRender(r18, r20, r21, r22, r23)     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            com.codex.fullm9.NativeM9.rawClose(r18)     // Catch: java.lang.Throwable -> L14d java.lang.Error -> L158 java.lang.Exception -> L162
            r0 = r11[r25]     // Catch: java.lang.Throwable -> L132 java.lang.Error -> L137 java.lang.Exception -> L142
            r4 = r11[r35]     // Catch: java.lang.Throwable -> L132 java.lang.Error -> L137 java.lang.Exception -> L142
            byte[] r0 = rawExif(r1, r2, r0, r4)     // Catch: java.lang.Throwable -> L132 java.lang.Error -> L137 java.lang.Exception -> L142
            r7 = r23
            r4 = r0
            goto L219
        L132:
            r0 = move-exception
            r1 = r16
            r10 = r1
            goto L152
        L137:
            r0 = move-exception
            r10 = r16
            r17 = r10
            r15 = r22
            r7 = r23
            goto L245
        L142:
            r0 = move-exception
            r10 = r16
            r17 = r10
            r15 = r22
            r7 = r23
            goto L24e
        L14d:
            r0 = move-exception
            r1 = r16
            r10 = r18
        L152:
            r15 = r22
            r7 = r23
            goto L1dc
        L158:
            r0 = move-exception
            r10 = r18
            r15 = r22
            r7 = r23
            r2 = 0
            r4 = 0
            goto L17b
        L162:
            r0 = move-exception
            r10 = r18
            r15 = r22
            r7 = r23
            r2 = 0
            r4 = 0
            goto L186
        L16c:
            r0 = move-exception
            r1 = r16
            r10 = r18
            goto L1d9
        L173:
            r0 = move-exception
            r10 = r18
            r15 = r22
            r2 = 0
            r4 = 0
            r7 = 0
        L17b:
            r13 = 0
            r14 = 0
            goto L199
        L17e:
            r0 = move-exception
            r10 = r18
            r15 = r22
            r2 = 0
            r4 = 0
            r7 = 0
        L186:
            r13 = 0
            r14 = 0
            goto L1aa
        L189:
            r0 = move-exception
            r1 = r16
            r10 = r18
            goto L58
        L190:
            r0 = move-exception
            r10 = r18
            r2 = 0
            r4 = 0
            r7 = 0
            r13 = 0
            r14 = 0
            r15 = 0
        L199:
            r24 = 0
            r17 = r16
            r16 = 0
            goto L715
        L1a1:
            r0 = move-exception
            r10 = r18
            r2 = 0
            r4 = 0
            r7 = 0
            r13 = 0
            r14 = 0
            r15 = 0
        L1aa:
            r24 = 0
            r17 = r16
            r16 = 0
            goto L72b
        L1b2:
            r36 = r7
            r35 = r10
            r25 = r12
            int r0 = com.codex.fullm9.FullM9Input.orientation(r2)     // Catch: java.lang.Throwable -> L6e4 java.lang.Error -> L6e9 java.lang.Exception -> L6ee
            android.graphics.Bitmap r22 = com.codex.fullm9.FullM9Input.decode(r2, r0)     // Catch: java.lang.Throwable -> L6e4 java.lang.Error -> L6e9 java.lang.Exception -> L6ee
            int r4 = r2.length     // Catch: java.lang.Throwable -> L6be java.lang.Error -> L6ca java.lang.Exception -> L6d7
            r5 = r35
            if (r4 <= r5) goto L1fc
            r4 = r2[r25]     // Catch: java.lang.Throwable -> L1d5 java.lang.Error -> L1e0 java.lang.Exception -> L1ee
            r7 = 255(0xff, float:3.57E-43)
            r4 = r4 & r7
            if (r4 != r7) goto L1fc
            r4 = r2[r5]     // Catch: java.lang.Throwable -> L1d5 java.lang.Error -> L1e0 java.lang.Exception -> L1ee
            r4 = r4 & r7
            r5 = 216(0xd8, float:3.03E-43)
            if (r4 != r5) goto L1fc
            r4 = 1
            goto L1fe
        L1d5:
            r0 = move-exception
            r1 = r16
            r10 = r1
        L1d9:
            r15 = r22
            r7 = 0
        L1dc:
            r13 = 0
            r14 = 0
            goto L6fd
        L1e0:
            r0 = move-exception
            r10 = r16
            r17 = r10
            r15 = r22
            r2 = 0
            r4 = 0
            r7 = 0
        L1ea:
            r13 = 0
            r14 = 0
            goto L711
        L1ee:
            r0 = move-exception
            r10 = r16
            r17 = r10
            r15 = r22
            r2 = 0
            r4 = 0
            r7 = 0
        L1f8:
            r13 = 0
            r14 = 0
            goto L727
        L1fc:
            r4 = r25
        L1fe:
            if (r4 == 0) goto L207
            if (r0 == 0) goto L205
            r5 = 1
            if (r0 != r5) goto L207
        L205:
            r0 = r2
            goto L213
        L207:
            int r0 = r22.getWidth()     // Catch: java.lang.Throwable -> L6be java.lang.Error -> L6ca java.lang.Exception -> L6d7
            int r4 = r22.getHeight()     // Catch: java.lang.Throwable -> L6be java.lang.Error -> L6ca java.lang.Exception -> L6d7
            byte[] r0 = rawExif(r1, r2, r0, r4)     // Catch: java.lang.Throwable -> L6be java.lang.Error -> L6ca java.lang.Exception -> L6d7
        L213:
            com.codex.fullm9.FullM9Engine$Settings r5 = settings(r0, r3)     // Catch: java.lang.Throwable -> L6be java.lang.Error -> L6ca java.lang.Exception -> L6d7
            r7 = 0
            r4 = r0
        L219:
            java.lang.String r0 = "输入降噪"
            com.codex.fullm9.CaptureTrace.stage(r1, r0)     // Catch: java.lang.Throwable -> L69e java.lang.Error -> L6a8 java.lang.Exception -> L6b3
            android.graphics.Bitmap r8 = com.codex.lmport.DenoiseFlow.prepare(r22)     // Catch: java.lang.Throwable -> L69e java.lang.Error -> L6a8 java.lang.Exception -> L6b3
            int r0 = r8.getHeight()     // Catch: java.lang.Throwable -> L685 java.lang.Error -> L68e java.lang.Exception -> L696
            int r10 = r8.getWidth()     // Catch: java.lang.Throwable -> L685 java.lang.Error -> L68e java.lang.Exception -> L696
            if (r0 <= r10) goto L22e
            r0 = 1
            goto L230
        L22e:
            r0 = r25
        L230:
            if (r0 == 0) goto L251
            r10 = 1119092736(0x42b40000, float:90.0)
            android.graphics.Bitmap r10 = rotate(r8, r10)     // Catch: java.lang.Throwable -> L239 java.lang.Error -> L23f java.lang.Exception -> L248
            goto L252
        L239:
            r0 = move-exception
            r15 = r8
            r1 = r16
            r10 = r1
            goto L1dc
        L23f:
            r0 = move-exception
            r15 = r8
            r10 = r16
            r17 = r10
        L245:
            r2 = 0
            r4 = 0
            goto L1ea
        L248:
            r0 = move-exception
            r15 = r8
            r10 = r16
            r17 = r10
        L24e:
            r2 = 0
            r4 = 0
            goto L1f8
        L251:
            r10 = r8
        L252:
            int r11 = r10.getWidth()     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            int r12 = r10.getHeight()     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            float r13 = (float) r11     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            r14 = 1166016512(0x45800000, float:4096.0)
            float r14 = r14 / r13
            float r15 = (float) r12     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            r18 = 1161822208(0x45400000, float:3072.0)
            r19 = r4
            float r4 = r18 / r15
            float r4 = java.lang.Math.min(r14, r4)     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            r14 = 1065353216(0x3f800000, float:1.0)
            float r4 = java.lang.Math.min(r14, r4)     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            int r14 = (r4 > r14 ? 1 : (r4 == r14 ? 0 : -1))
            if (r14 >= 0) goto L2c7
            float r13 = r13 * r4
            int r13 = (int) r13
            r18 = r4
            r4 = 1
            int r13 = java.lang.Math.max(r4, r13)     // Catch: java.lang.Throwable -> L28e java.lang.Error -> L29f java.lang.Exception -> L2b3
            float r15 = r15 * r18
            int r15 = (int) r15     // Catch: java.lang.Throwable -> L28e java.lang.Error -> L29f java.lang.Exception -> L2b3
            int r15 = java.lang.Math.max(r4, r15)     // Catch: java.lang.Throwable -> L28e java.lang.Error -> L29f java.lang.Exception -> L2b3
            android.graphics.Bitmap r13 = android.graphics.Bitmap.createScaledBitmap(r10, r13, r15, r4)     // Catch: java.lang.Throwable -> L28e java.lang.Error -> L29f java.lang.Exception -> L2b3
            if (r10 == r8) goto L28c
            recycle(r10)     // Catch: java.lang.Throwable -> L28e java.lang.Error -> L29f java.lang.Exception -> L2b3
        L28c:
            r10 = r13
            goto L2c7
        L28e:
            r0 = move-exception
            r15 = r8
            r1 = r16
            r13 = 0
        L293:
            r14 = 0
            r18 = 0
            r19 = 0
            r20 = 0
            r16 = r10
            r10 = r1
            goto L73c
        L29f:
            r0 = move-exception
            r15 = r8
            r2 = 0
        L2a2:
            r4 = 0
            r13 = 0
            r14 = 0
            r24 = 0
            r38 = r16
            r40 = r38
            r16 = r10
            r10 = r40
            r17 = r10
            goto L715
        L2b3:
            r0 = move-exception
            r15 = r8
            r2 = 0
        L2b6:
            r4 = 0
            r13 = 0
            r14 = 0
            r24 = 0
            r38 = r16
            r40 = r38
            r16 = r10
            r10 = r40
            r17 = r10
            goto L72b
        L2c7:
            java.lang.String r4 = "M9影调与色彩恢复"
            com.codex.fullm9.CaptureTrace.stage(r1, r4)     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            int r4 = r5.lux     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            int r13 = r5.cct     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            float r15 = r5.zoom     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            android.graphics.Bitmap r4 = com.codex.fullm9.M9Graph.process(r1, r10, r4, r13, r15)     // Catch: java.lang.Throwable -> L65c java.lang.Error -> L669 java.lang.Exception -> L677
            if (r14 >= 0) goto L2f0
            r13 = 1
            android.graphics.Bitmap r11 = android.graphics.Bitmap.createScaledBitmap(r4, r11, r12, r13)     // Catch: java.lang.Throwable -> L2e2 java.lang.Error -> L2e8 java.lang.Exception -> L2ec
            recycle(r4)     // Catch: java.lang.Throwable -> L2e2 java.lang.Error -> L2e8 java.lang.Exception -> L2ec
            r4 = r11
            goto L2f1
        L2e2:
            r0 = move-exception
            r13 = r4
            r15 = r8
            r1 = r16
            goto L293
        L2e8:
            r0 = move-exception
            r2 = r4
            r15 = r8
            goto L2a2
        L2ec:
            r0 = move-exception
            r2 = r4
            r15 = r8
            goto L2b6
        L2f0:
            r13 = 1
        L2f1:
            if (r0 == 0) goto L2fd
            r0 = -1028390912(0xffffffffc2b40000, float:-90.0)
            android.graphics.Bitmap r0 = rotate(r4, r0)     // Catch: java.lang.Throwable -> L2e2 java.lang.Error -> L2e8 java.lang.Exception -> L2ec
            recycle(r4)     // Catch: java.lang.Throwable -> L2e2 java.lang.Error -> L2e8 java.lang.Exception -> L2ec
            r4 = r0
        L2fd:
            if (r10 == r8) goto L302
            recycle(r10)     // Catch: java.lang.Throwable -> L2e2 java.lang.Error -> L2e8 java.lang.Exception -> L2ec
        L302:
            r11 = r16
            r16 = 0
            java.lang.String r0 = "影调与输出降噪"
            com.codex.fullm9.CaptureTrace.stage(r1, r0)     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            com.codex.fullm9.LeicaParams r0 = new com.codex.fullm9.LeicaParams     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            r0.<init>(r1)     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            java.lang.String r10 = "common"
            int r14 = r5.lux     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            int r15 = r5.cct     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            byte[] r10 = r0.lut(r10, r14, r15)     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            float r14 = r5.zoom     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            int r15 = r5.lux     // Catch: java.lang.Throwable -> L63f java.lang.Error -> L64a java.lang.Exception -> L653
            r17 = r11
            int r11 = r5.cct     // Catch: java.lang.Throwable -> L639 java.lang.Error -> L63b java.lang.Exception -> L63d
            float[] r0 = r0.shading(r14, r15, r11)     // Catch: java.lang.Throwable -> L639 java.lang.Error -> L63b java.lang.Exception -> L63d
            com.codex.fullm9.NativeM9.applyFilter(r4, r10, r0)     // Catch: java.lang.Throwable -> L639 java.lang.Error -> L63b java.lang.Exception -> L63d
            android.graphics.Bitmap r4 = com.codex.lmport.DenoiseFlow.finish(r4)     // Catch: java.lang.Throwable -> L639 java.lang.Error -> L63b java.lang.Exception -> L63d
            java.lang.String r0 = "精细纹理恢复"
            com.codex.fullm9.CaptureTrace.stage(r1, r0)     // Catch: java.lang.Throwable -> L61b java.lang.Error -> L62b java.lang.Exception -> L632
            com.codex.fullm9.NativeM9.restoreTexture(r8, r4)     // Catch: java.lang.Throwable -> L336 java.lang.Error -> L345 java.lang.OutOfMemoryError -> L34e java.lang.LinkageError -> L357 java.lang.Exception -> L366
            goto L36e
        L336:
            r0 = move-exception
            r13 = r4
            r15 = r8
        L339:
            r1 = r17
            r10 = r1
            r14 = 0
            r19 = 0
            r20 = 0
        L341:
            r18 = r13
            goto L73c
        L345:
            r0 = move-exception
            r2 = r4
            r15 = r8
        L348:
            r10 = r17
            r13 = 0
            r14 = 0
            goto L713
        L34e:
            r0 = move-exception
            java.lang.String r10 = "FullM9"
            java.lang.String r11 = "Texture recovery memory limit"
        L353:
            android.util.Log.w(r10, r11, r0)     // Catch: java.lang.Throwable -> L336 java.lang.Error -> L345 java.lang.Exception -> L35d
            goto L36e
        L357:
            r0 = move-exception
            java.lang.String r10 = "FullM9"
            java.lang.String r11 = "Texture recovery unavailable"
            goto L353
        L35d:
            r0 = move-exception
            r2 = r4
            r15 = r8
        L360:
            r10 = r17
            r13 = 0
            r14 = 0
            goto L729
        L366:
            r0 = move-exception
            java.lang.String r10 = "FullM9"
            java.lang.String r11 = "Keep M9 output without texture recovery"
            android.util.Log.w(r10, r11, r0)     // Catch: java.lang.Throwable -> L61b java.lang.Error -> L62b java.lang.Exception -> L632
        L36e:
            com.codex.fullm9.CloudGraph.palette(r4)     // Catch: java.lang.Throwable -> L61b java.lang.Error -> L62b java.lang.Exception -> L632
            recycle(r8)     // Catch: java.lang.Throwable -> L61b java.lang.Error -> L62b java.lang.Exception -> L632
            r0 = 34
            r15 = 0
            if (r7 == 0) goto L391
            int r8 = android.os.Build.VERSION.SDK_INT     // Catch: java.lang.Throwable -> L388 java.lang.Error -> L38b java.lang.Exception -> L38e
            if (r8 < r0) goto L391
            float r2 = boost(r7)     // Catch: java.lang.Throwable -> L388 java.lang.Error -> L38b java.lang.Exception -> L38e
            com.codex.fullm9.FullM9Hdr.attachRaw(r4, r7, r2)     // Catch: java.lang.Throwable -> L388 java.lang.Error -> L38b java.lang.Exception -> L38e
            r8 = r25
            r14 = 0
            goto L397
        L388:
            r0 = move-exception
            r13 = r4
            goto L339
        L38b:
            r0 = move-exception
            r2 = r4
            goto L348
        L38e:
            r0 = move-exception
            r2 = r4
            goto L360
        L391:
            r8 = r25
            r14 = 0
            com.codex.fullm9.FullM9Hdr.transfer(r14, r4, r2, r8)     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
        L397:
            java.lang.String r2 = "水印"
            com.codex.fullm9.CaptureTrace.stage(r1, r2)     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
            java.lang.String r2 = "com.codex.lmoments.LeicaMark"
            java.lang.Class r2 = java.lang.Class.forName(r2)     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
            java.lang.String r10 = "mark"
            java.lang.Class<byte[]> r11 = byte[].class
            java.lang.Class[] r11 = new java.lang.Class[]{r11}     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
            java.lang.Object[] r12 = new java.lang.Object[]{r19}     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
            java.lang.Object r2 = com.codex.fullm9.Reflect.call(r2, r10, r11, r12)     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
            byte[] r2 = (byte[]) r2     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
            if (r3 != 0) goto L3b8
            r8 = r4
            goto L3da
        L3b8:
            java.lang.String r10 = "com.codex.leicaapp.OriginalWatermark"
            java.lang.Class r10 = java.lang.Class.forName(r10)     // Catch: java.lang.Throwable -> L611 java.lang.Error -> L615 java.lang.Exception -> L618
            java.lang.String r11 = "apply"
            java.lang.Class<android.graphics.Bitmap> r12 = android.graphics.Bitmap.class
            java.lang.Class<java.lang.Object> r8 = java.lang.Object.class
            java.lang.Class<byte[]> r13 = byte[].class
            java.lang.Class<android.hardware.camera2.CaptureResult> r14 = android.hardware.camera2.CaptureResult.class
            java.lang.Class[] r8 = new java.lang.Class[]{r12, r8, r13, r14}     // Catch: java.lang.Throwable -> L605 java.lang.Error -> L609 java.lang.Exception -> L60d
            java.lang.Object r12 = captureResult(r3)     // Catch: java.lang.Throwable -> L605 java.lang.Error -> L609 java.lang.Exception -> L60d
            java.lang.Object[] r12 = new java.lang.Object[]{r4, r3, r2, r12}     // Catch: java.lang.Throwable -> L605 java.lang.Error -> L609 java.lang.Exception -> L60d
            java.lang.Object r8 = com.codex.fullm9.Reflect.call(r10, r11, r8, r12)     // Catch: java.lang.Throwable -> L605 java.lang.Error -> L609 java.lang.Exception -> L60d
            android.graphics.Bitmap r8 = (android.graphics.Bitmap) r8     // Catch: java.lang.Throwable -> L605 java.lang.Error -> L609 java.lang.Exception -> L60d
        L3da:
            if (r8 == 0) goto L5f1
            r10 = 8
            com.codex.fullm9.FullM9Hdr.finish(r4, r8, r10)     // Catch: java.lang.Throwable -> L5d1 java.lang.Error -> L5db java.lang.Exception -> L5e6
            java.lang.String r10 = "最终HDR与JPEG编码"
            com.codex.fullm9.CaptureTrace.stage(r1, r10)     // Catch: java.lang.Throwable -> L5d1 java.lang.Error -> L5db java.lang.Exception -> L5e6
            android.graphics.Bitmap r10 = p3(r8)     // Catch: java.lang.Throwable -> L5d1 java.lang.Error -> L5db java.lang.Exception -> L5e6
            int r11 = android.os.Build.VERSION.SDK_INT     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            if (r11 < r0) goto L412
            com.codex.fullm9.FullM9Engine.HdrCopy.copy(r8, r10)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            goto L412
        L3f2:
            r0 = move-exception
            r13 = r4
            r19 = r8
            r20 = r10
            r1 = r17
            r10 = r1
            r14 = 0
            goto L341
        L3fe:
            r0 = move-exception
            r2 = r4
            r13 = r8
            r24 = r10
            r10 = r17
            r14 = 0
            goto L715
        L408:
            r0 = move-exception
            r2 = r4
            r13 = r8
            r24 = r10
            r10 = r17
            r14 = 0
            goto L72b
        L412:
            java.io.ByteArrayOutputStream r0 = new java.io.ByteArrayOutputStream     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            r0.<init>()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            android.graphics.Bitmap$CompressFormat r11 = android.graphics.Bitmap.CompressFormat.JPEG     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            r12 = 98
            boolean r11 = r10.compress(r11, r12, r0)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            if (r11 == 0) goto L591
            byte[] r0 = r0.toByteArray()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            int r11 = r10.getWidth()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            int r12 = r10.getHeight()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            byte[] r2 = metadata(r2, r0, r11, r12)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            r11 = 8
            com.codex.fullm9.FullM9Hdr.verify(r1, r2, r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            if (r3 == 0) goto L464
            java.lang.String r0 = "b"
            java.lang.Object r0 = com.codex.fullm9.Reflect.field(r3, r0)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            java.lang.String r11 = "b"
            android.util.Size r12 = new android.util.Size     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            int r13 = r10.getWidth()     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            int r14 = r10.getHeight()     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            r12.<init>(r13, r14)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            com.codex.fullm9.Reflect.put(r0, r11, r12)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            java.lang.String r0 = "a"
            java.lang.Object r0 = com.codex.fullm9.Reflect.field(r3, r0)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            int r11 = r10.getWidth()     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            int r12 = r10.getHeight()     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            com.codex.lmport.MomentBridge.uprightSource(r0, r11, r12)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            com.codex.fullm9.CaptureState.commitJpeg(r3, r2)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
        L464:
            java.lang.StringBuilder r0 = new java.lang.StringBuilder     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = "完美移植m9 size="
            r0.<init>(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            int r11 = r10.getWidth()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = "x"
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            int r11 = r10.getHeight()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = " model="
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            int r11 = r5.lux     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            r12 = 260(0x104, float:3.64E-43)
            if (r11 <= r12) goto L496
            int r11 = r5.cct     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            r12 = 4692(0x1254, float:6.575E-42)
            if (r11 >= r12) goto L496
            java.lang.String r11 = "low"
            goto L498
        L496:
            java.lang.String r11 = "high"
        L498:
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = " "
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = com.codex.fullm9.M9Graph.lastTiming()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = " lux="
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            int r11 = r5.lux     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = " cct="
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            int r11 = r5.cct     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r11 = " triggers="
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r5 = r5.provenance     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.StringBuilder r0 = r0.append(r5)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r5 = " seconds="
            java.lang.StringBuilder r0 = r0.append(r5)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            long r11 = java.lang.System.nanoTime()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            long r11 = r11 - r36
            double r11 = (double) r11     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            r13 = 4741671816366391296(0x41cdcd6500000000, double:1.0E9)
            double r11 = r11 / r13
            java.lang.StringBuilder r0 = r0.append(r11)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r5 = " "
            java.lang.StringBuilder r0 = r0.append(r5)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r5 = com.codex.fullm9.CaptureTrace.timings()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.StringBuilder r0 = r0.append(r5)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r0 = r0.toString()     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.lang.String r5 = "FullM9"
            android.util.Log.i(r5, r0)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.io.FileOutputStream r5 = new java.io.FileOutputStream     // Catch: java.lang.Throwable -> L534
            java.io.File r11 = new java.io.File     // Catch: java.lang.Throwable -> L534
            java.io.File r12 = r1.getFilesDir()     // Catch: java.lang.Throwable -> L534
            java.lang.String r13 = "fullm9-last-render.txt"
            r11.<init>(r12, r13)     // Catch: java.lang.Throwable -> L534
            r5.<init>(r11)     // Catch: java.lang.Throwable -> L534
            java.lang.StringBuilder r11 = new java.lang.StringBuilder     // Catch: java.lang.Throwable -> L52c
            java.lang.String r0 = java.lang.String.valueOf(r0)     // Catch: java.lang.Throwable -> L52c
            r11.<init>(r0)     // Catch: java.lang.Throwable -> L52c
            java.lang.String r0 = "\n"
            java.lang.StringBuilder r0 = r11.append(r0)     // Catch: java.lang.Throwable -> L52c
            java.lang.String r0 = r0.toString()     // Catch: java.lang.Throwable -> L52c
            java.lang.String r11 = "UTF-8"
            byte[] r0 = r0.getBytes(r11)     // Catch: java.lang.Throwable -> L52c
            r5.write(r0)     // Catch: java.lang.Throwable -> L52c
            r5.close()     // Catch: java.lang.Throwable -> L534
            goto L547
        L52c:
            r0 = move-exception
            r13 = r0
            r5.close()     // Catch: java.lang.Throwable -> L532
            throw r13     // Catch: java.lang.Throwable -> L532
        L532:
            r0 = move-exception
            goto L536
        L534:
            r0 = move-exception
            r13 = 0
        L536:
            if (r13 == 0) goto L53e
            if (r13 == r0) goto L53d
            r13.addSuppressed(r0)     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L53f
        L53d:
            r0 = r13
        L53e:
            throw r0     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L53f
        L53f:
            r0 = move-exception
            java.lang.String r5 = "FullM9"
            java.lang.String r11 = "Render diagnostic unavailable"
            android.util.Log.w(r5, r11, r0)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
        L547:
            if (r3 == 0) goto L54f
            boolean r0 = r3 instanceof com.codex.fullm9.CaptureSnapshot     // Catch: java.lang.Throwable -> L3f2 java.lang.Error -> L3fe java.lang.Exception -> L408
            if (r0 != 0) goto L54f
            r12 = 1
            goto L550
        L54f:
            r12 = 0
        L550:
            com.codex.fullm9.CaptureTrace.complete(r1, r12)     // Catch: java.lang.Throwable -> L5a7 java.lang.Error -> L5b3 java.lang.Exception -> L5c2
            java.util.IdentityHashMap r0 = new java.util.IdentityHashMap     // Catch: java.lang.Throwable -> L779
            r0.<init>()     // Catch: java.lang.Throwable -> L779
            java.util.Set r0 = java.util.Collections.newSetFromMap(r0)     // Catch: java.lang.Throwable -> L779
            r18 = r4
            r17 = r4
            r19 = r8
            r20 = r10
            r14 = 0
            android.graphics.Bitmap[] r1 = new android.graphics.Bitmap[]{r14, r15, r16, r17, r18, r19, r20}     // Catch: java.lang.Throwable -> L779
            java.util.Collections.addAll(r0, r1)     // Catch: java.lang.Throwable -> L779
            java.util.Iterator r0 = r0.iterator()     // Catch: java.lang.Throwable -> L779
        L570:
            boolean r1 = r0.hasNext()     // Catch: java.lang.Throwable -> L779
            if (r1 != 0) goto L587
            recycle(r7)     // Catch: java.lang.Throwable -> L779
            com.codex.lmport.DenoiseFlow.end()     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.FullM9Hdr.clear()     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.OutputQuality.end()     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.M9Graph.clearTiming()     // Catch: java.lang.Throwable -> L779
            monitor-exit(r6)     // Catch: java.lang.Throwable -> L779
            return r2
        L587:
            java.lang.Object r1 = r0.next()     // Catch: java.lang.Throwable -> L779
            android.graphics.Bitmap r1 = (android.graphics.Bitmap) r1     // Catch: java.lang.Throwable -> L779
            recycle(r1)     // Catch: java.lang.Throwable -> L779
            goto L570
        L591:
            r2 = r4
            r19 = r8
            r20 = r10
            r14 = 0
            java.io.IOException r0 = new java.io.IOException     // Catch: java.lang.Throwable -> L59f java.lang.Error -> L5a1 java.lang.Exception -> L5a4
            java.lang.String r3 = "Final JPEG encoding failed"
            r0.<init>(r3)     // Catch: java.lang.Throwable -> L59f java.lang.Error -> L5a1 java.lang.Exception -> L5a4
            throw r0     // Catch: java.lang.Throwable -> L59f java.lang.Error -> L5a1 java.lang.Exception -> L5a4
        L59f:
            r0 = move-exception
            goto L5ae
        L5a1:
            r0 = move-exception
            r4 = r2
            goto L5ba
        L5a4:
            r0 = move-exception
            r4 = r2
            goto L5c9
        L5a7:
            r0 = move-exception
            r2 = r4
            r19 = r8
            r20 = r10
            r14 = 0
        L5ae:
            r13 = r2
            r10 = r17
            goto L626
        L5b3:
            r0 = move-exception
            r2 = r4
            r19 = r8
            r20 = r10
            r14 = 0
        L5ba:
            r10 = r17
            r13 = r19
            r24 = r20
            goto L715
        L5c2:
            r0 = move-exception
            r2 = r4
            r19 = r8
            r20 = r10
            r14 = 0
        L5c9:
            r10 = r17
            r13 = r19
            r24 = r20
            goto L72b
        L5d1:
            r0 = move-exception
            r2 = r4
            r19 = r8
            r14 = 0
        L5d6:
            r13 = r2
            r10 = r17
            goto L624
        L5db:
            r0 = move-exception
            r2 = r4
            r19 = r8
            r14 = 0
        L5e0:
            r10 = r17
            r13 = r19
            goto L713
        L5e6:
            r0 = move-exception
            r2 = r4
            r19 = r8
            r14 = 0
        L5eb:
            r10 = r17
            r13 = r19
            goto L729
        L5f1:
            r2 = r4
            r19 = r8
            r14 = 0
            java.io.IOException r0 = new java.io.IOException     // Catch: java.lang.Throwable -> L5fd java.lang.Error -> L5ff java.lang.Exception -> L602
            java.lang.String r3 = "Watermark output unavailable"
            r0.<init>(r3)     // Catch: java.lang.Throwable -> L5fd java.lang.Error -> L5ff java.lang.Exception -> L602
            throw r0     // Catch: java.lang.Throwable -> L5fd java.lang.Error -> L5ff java.lang.Exception -> L602
        L5fd:
            r0 = move-exception
            goto L5d6
        L5ff:
            r0 = move-exception
            r4 = r2
            goto L5e0
        L602:
            r0 = move-exception
            r4 = r2
            goto L5eb
        L605:
            r0 = move-exception
            r2 = r4
            r14 = 0
            goto L613
        L609:
            r0 = move-exception
            r2 = r4
            r14 = 0
            goto L62f
        L60d:
            r0 = move-exception
            r2 = r4
            r14 = 0
            goto L636
        L611:
            r0 = move-exception
            r2 = r4
        L613:
            r13 = r2
            goto L620
        L615:
            r0 = move-exception
            r2 = r4
            goto L62f
        L618:
            r0 = move-exception
            r2 = r4
            goto L636
        L61b:
            r0 = move-exception
            r2 = r4
            r14 = 0
            r13 = r2
            r15 = r8
        L620:
            r10 = r17
            r19 = 0
        L624:
            r20 = 0
        L626:
            r18 = r13
            r1 = r10
            goto L73c
        L62b:
            r0 = move-exception
            r2 = r4
            r14 = 0
            r15 = r8
        L62f:
            r10 = r17
            goto L674
        L632:
            r0 = move-exception
            r2 = r4
            r14 = 0
            r15 = r8
        L636:
            r10 = r17
            goto L682
        L639:
            r0 = move-exception
            goto L642
        L63b:
            r0 = move-exception
            goto L64d
        L63d:
            r0 = move-exception
            goto L656
        L63f:
            r0 = move-exception
            r17 = r11
        L642:
            r14 = 0
            r13 = r4
            r15 = r8
            r1 = r17
            r10 = r1
            goto L6ff
        L64a:
            r0 = move-exception
            r17 = r11
        L64d:
            r14 = 0
            r2 = r4
            r15 = r8
            r10 = r17
            goto L673
        L653:
            r0 = move-exception
            r17 = r11
        L656:
            r14 = 0
            r2 = r4
            r15 = r8
            r10 = r17
            goto L681
        L65c:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r15 = r8
            r16 = r10
            r1 = r17
            r10 = r1
            r13 = 0
            goto L6ff
        L669:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r15 = r8
            r16 = r10
            r10 = r17
            r2 = 0
        L673:
            r4 = 0
        L674:
            r13 = 0
            goto L713
        L677:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r15 = r8
            r16 = r10
            r10 = r17
            r2 = 0
        L681:
            r4 = 0
        L682:
            r13 = 0
            goto L729
        L685:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r15 = r8
            r1 = r17
            r10 = r1
            goto L6c8
        L68e:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r15 = r8
            r10 = r17
            goto L6b0
        L696:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r15 = r8
            r10 = r17
            goto L6bb
        L69e:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r1 = r17
            r10 = r1
            r15 = r22
            goto L6c8
        L6a8:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r10 = r17
            r15 = r22
        L6b0:
            r2 = 0
            r4 = 0
            goto L6d5
        L6b3:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r10 = r17
            r15 = r22
        L6bb:
            r2 = 0
            r4 = 0
            goto L6e2
        L6be:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r1 = r17
            r10 = r1
            r15 = r22
            r7 = 0
        L6c8:
            r13 = 0
            goto L6fd
        L6ca:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r10 = r17
            r15 = r22
            r2 = 0
            r4 = 0
            r7 = 0
        L6d5:
            r13 = 0
            goto L711
        L6d7:
            r0 = move-exception
            r17 = r16
            r14 = 0
            r10 = r17
            r15 = r22
            r2 = 0
            r4 = 0
            r7 = 0
        L6e2:
            r13 = 0
            goto L727
        L6e4:
            r0 = move-exception
            r17 = r16
            r14 = 0
            goto L6f7
        L6e9:
            r0 = move-exception
            r17 = r16
            r14 = 0
            goto L70a
        L6ee:
            r0 = move-exception
            r17 = r16
            r14 = 0
            goto L720
        L6f3:
            r0 = move-exception
            r14 = 0
            r17 = 0
        L6f7:
            r1 = r17
            r10 = r1
            r7 = 0
            r13 = 0
        L6fc:
            r15 = 0
        L6fd:
            r16 = 0
        L6ff:
            r18 = 0
            r19 = 0
            r20 = 0
            goto L73c
        L706:
            r0 = move-exception
            r14 = 0
            r17 = 0
        L70a:
            r10 = r17
            r2 = 0
            r4 = 0
            r7 = 0
            r13 = 0
        L710:
            r15 = 0
        L711:
            r16 = 0
        L713:
            r24 = 0
        L715:
            r9.restore()     // Catch: java.lang.Throwable -> L732
            failure(r1, r0)     // Catch: java.lang.Throwable -> L732
        L71b:
            throw r0     // Catch: java.lang.Throwable -> L732
        L71c:
            r0 = move-exception
            r14 = 0
            r17 = 0
        L720:
            r10 = r17
            r2 = 0
            r4 = 0
            r7 = 0
            r13 = 0
        L726:
            r15 = 0
        L727:
            r16 = 0
        L729:
            r24 = 0
        L72b:
            r9.restore()     // Catch: java.lang.Throwable -> L732
            failure(r1, r0)     // Catch: java.lang.Throwable -> L732
            goto L71b
        L732:
            r0 = move-exception
            r19 = r13
            r20 = r24
            r13 = r2
            r1 = r17
            r18 = r4
        L73c:
            int r1 = (r10 > r1 ? 1 : (r10 == r1 ? 0 : -1))
            if (r1 == 0) goto L743
            com.codex.fullm9.NativeM9.rawClose(r10)     // Catch: java.lang.Throwable -> L779
        L743:
            java.util.IdentityHashMap r1 = new java.util.IdentityHashMap     // Catch: java.lang.Throwable -> L779
            r1.<init>()     // Catch: java.lang.Throwable -> L779
            java.util.Set r1 = java.util.Collections.newSetFromMap(r1)     // Catch: java.lang.Throwable -> L779
            r17 = r13
            android.graphics.Bitmap[] r2 = new android.graphics.Bitmap[]{r14, r15, r16, r17, r18, r19, r20}     // Catch: java.lang.Throwable -> L779
            java.util.Collections.addAll(r1, r2)     // Catch: java.lang.Throwable -> L779
            java.util.Iterator r1 = r1.iterator()     // Catch: java.lang.Throwable -> L779
        L759:
            boolean r2 = r1.hasNext()     // Catch: java.lang.Throwable -> L779
            if (r2 == 0) goto L769
            java.lang.Object r2 = r1.next()     // Catch: java.lang.Throwable -> L779
            android.graphics.Bitmap r2 = (android.graphics.Bitmap) r2     // Catch: java.lang.Throwable -> L779
            recycle(r2)     // Catch: java.lang.Throwable -> L779
            goto L759
        L769:
            recycle(r7)     // Catch: java.lang.Throwable -> L779
            com.codex.lmport.DenoiseFlow.end()     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.FullM9Hdr.clear()     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.OutputQuality.end()     // Catch: java.lang.Throwable -> L779
            com.codex.fullm9.M9Graph.clearTiming()     // Catch: java.lang.Throwable -> L779
            throw r0     // Catch: java.lang.Throwable -> L779
        L779:
            r0 = move-exception
            monitor-exit(r6)     // Catch: java.lang.Throwable -> L779
            throw r0
    }

    static java.lang.Object renderLock() {
            java.lang.Class<com.codex.lmport.MomentBridge> r0 = com.codex.lmport.MomentBridge.class
            java.lang.String r1 = "RENDER"
            java.lang.reflect.Field r0 = r0.getDeclaredField(r1)     // Catch: java.lang.Exception -> L12
            r1 = 1
            r0.setAccessible(r1)     // Catch: java.lang.Exception -> L12
            r1 = 0
            java.lang.Object r0 = r0.get(r1)     // Catch: java.lang.Exception -> L12
            return r0
        L12:
            r0 = move-exception
            java.lang.Class<com.codex.lmport.MomentBridge> r0 = com.codex.lmport.MomentBridge.class
            return r0
    }

    static android.graphics.Bitmap rotate(android.graphics.Bitmap r7, float r8) {
            android.graphics.Matrix r5 = new android.graphics.Matrix
            r5.<init>()
            r5.setRotate(r8)
            int r3 = r7.getWidth()
            int r4 = r7.getHeight()
            r6 = 0
            r1 = 0
            r2 = 0
            r0 = r7
            android.graphics.Bitmap r7 = android.graphics.Bitmap.createBitmap(r0, r1, r2, r3, r4, r5, r6)
            return r7
    }

    static com.codex.fullm9.FullM9Engine.Settings settings(byte[] r13, java.lang.Object r14) {
            java.lang.String r0 = "FullM9"
            boolean r1 = r14 instanceof com.codex.fullm9.CaptureSnapshot
            if (r1 == 0) goto Ld
            com.codex.fullm9.CaptureSnapshot r14 = (com.codex.fullm9.CaptureSnapshot) r14
            com.codex.fullm9.FullM9Engine$Settings r13 = r14.settings()
            return r13
        Ld:
            com.codex.fullm9.FullM9Engine$Settings r1 = new com.codex.fullm9.FullM9Engine$Settings
            r1.<init>()
            android.media.ExifInterface r2 = new android.media.ExifInterface     // Catch: java.lang.Exception -> La1
            java.io.ByteArrayInputStream r3 = new java.io.ByteArrayInputStream     // Catch: java.lang.Exception -> La1
            r3.<init>(r13)     // Catch: java.lang.Exception -> La1
            r2.<init>(r3)     // Catch: java.lang.Exception -> La1
            java.lang.String r13 = "ExposureTime"
            r3 = 0
            double r5 = r2.getAttributeDouble(r13, r3)     // Catch: java.lang.Exception -> La1
            java.lang.String r13 = "FNumber"
            double r7 = r2.getAttributeDouble(r13, r3)     // Catch: java.lang.Exception -> La1
            java.lang.String r13 = "PhotographicSensitivity"
            java.lang.String r9 = "ISOSpeedRatings"
            double r9 = r2.getAttributeDouble(r9, r3)     // Catch: java.lang.Exception -> La1
            double r9 = r2.getAttributeDouble(r13, r9)     // Catch: java.lang.Exception -> La1
            int r13 = (r5 > r3 ? 1 : (r5 == r3 ? 0 : -1))
            if (r13 <= 0) goto L7c
            int r13 = (r7 > r3 ? 1 : (r7 == r3 ? 0 : -1))
            if (r13 <= 0) goto L7c
            int r13 = (r9 > r3 ? 1 : (r9 == r3 ? 0 : -1))
            if (r13 <= 0) goto L7c
            double r7 = r7 * r7
            double r7 = r7 / r5
            double r5 = java.lang.Math.log(r7)     // Catch: java.lang.Exception -> La1
            r7 = 4611686018427387904(0x4000000000000000, double:2.0)
            double r11 = java.lang.Math.log(r7)     // Catch: java.lang.Exception -> La1
            double r5 = r5 / r11
            r11 = 4636737291354636288(0x4059000000000000, double:100.0)
            double r9 = r9 / r11
            double r9 = java.lang.Math.log(r9)     // Catch: java.lang.Exception -> La1
            double r7 = java.lang.Math.log(r7)     // Catch: java.lang.Exception -> La1
            double r9 = r9 / r7
            double r5 = r5 - r9
            r7 = 4627293805885993779(0x4037733333333333, double:23.45)
            double r5 = r5 * r7
            r7 = 4647062145344104038(0x407dae6666666666, double:474.9)
            double r7 = r7 - r5
            r5 = 4651998512748167168(0x408f380000000000, double:999.0)
            double r5 = java.lang.Math.min(r5, r7)     // Catch: java.lang.Exception -> La1
            double r5 = java.lang.Math.max(r3, r5)     // Catch: java.lang.Exception -> La1
            int r13 = (int) r5     // Catch: java.lang.Exception -> La1
            r1.lux = r13     // Catch: java.lang.Exception -> La1
            java.lang.String r13 = "EXIF EV estimate"
            r1.provenance = r13     // Catch: java.lang.Exception -> La1
        L7c:
            java.lang.String r13 = "FocalLengthIn35mmFilm"
            double r2 = r2.getAttributeDouble(r13, r3)     // Catch: java.lang.Exception -> La1
            r4 = 4632233691727265792(0x4049000000000000, double:50.0)
            int r13 = (r2 > r4 ? 1 : (r2 == r4 ? 0 : -1))
            if (r13 < 0) goto La7
            r4 = 4627167142146473984(0x4037000000000000, double:23.0)
            double r2 = r2 / r4
            r4 = 4616527388026811187(0x4011333333333333, double:4.3)
            double r2 = java.lang.Math.min(r4, r2)     // Catch: java.lang.Exception -> La1
            r4 = 4614388178203810202(0x400999999999999a, double:3.2)
            double r2 = java.lang.Math.max(r4, r2)     // Catch: java.lang.Exception -> La1
            float r13 = (float) r2     // Catch: java.lang.Exception -> La1
            r1.zoom = r13     // Catch: java.lang.Exception -> La1
            goto La7
        La1:
            r13 = move-exception
            java.lang.String r2 = "No EXIF metering"
            android.util.Log.d(r0, r2, r13)
        La7:
            java.lang.Object r13 = captureResult(r14)
            boolean r14 = r13 instanceof android.hardware.camera2.CaptureResult
            if (r14 == 0) goto L178
            android.hardware.camera2.CaptureResult r13 = (android.hardware.camera2.CaptureResult) r13
            java.util.List r14 = r13.getKeys()
            java.util.Iterator r14 = r14.iterator()
        Lb9:
            boolean r2 = r14.hasNext()
            if (r2 != 0) goto Lc1
            goto L178
        Lc1:
            java.lang.Object r2 = r14.next()
            android.hardware.camera2.CaptureResult$Key r2 = (android.hardware.camera2.CaptureResult.Key) r2
            java.lang.String r3 = r2.getName()     // Catch: java.lang.Exception -> L170
            java.util.Locale r4 = java.util.Locale.US     // Catch: java.lang.Exception -> L170
            java.lang.String r3 = r3.toLowerCase(r4)     // Catch: java.lang.Exception -> L170
            java.lang.Object r2 = r13.get(r2)     // Catch: java.lang.Exception -> L170
            boolean r4 = r2 instanceof java.lang.Number     // Catch: java.lang.Exception -> L170
            if (r4 == 0) goto Le0
            java.lang.Number r2 = (java.lang.Number) r2     // Catch: java.lang.Exception -> L170
            float r2 = r2.floatValue()     // Catch: java.lang.Exception -> L170
            goto Lf2
        Le0:
            boolean r4 = r2 instanceof float[]     // Catch: java.lang.Exception -> L170
            if (r4 == 0) goto Lf0
            r4 = r2
            float[] r4 = (float[]) r4     // Catch: java.lang.Exception -> L170
            int r4 = r4.length     // Catch: java.lang.Exception -> L170
            if (r4 <= 0) goto Lf0
            float[] r2 = (float[]) r2     // Catch: java.lang.Exception -> L170
            r4 = 0
            r2 = r2[r4]     // Catch: java.lang.Exception -> L170
            goto Lf2
        Lf0:
            r2 = 2143289344(0x7fc00000, float:NaN)
        Lf2:
            boolean r4 = java.lang.Float.isFinite(r2)     // Catch: java.lang.Exception -> L170
            if (r4 != 0) goto Lf9
        Lf8:
            goto Lb9
        Lf9:
            java.lang.String r4 = "luxindex"
            boolean r4 = r3.contains(r4)     // Catch: java.lang.Exception -> L170
            r5 = 0
            if (r4 != 0) goto L10a
            java.lang.String r4 = "lux_index"
            boolean r4 = r3.contains(r4)     // Catch: java.lang.Exception -> L170
            if (r4 == 0) goto L11e
        L10a:
            int r4 = (r2 > r5 ? 1 : (r2 == r5 ? 0 : -1))
            if (r4 < 0) goto L11e
            r4 = 1148846080(0x447a0000, float:1000.0)
            int r4 = (r2 > r4 ? 1 : (r2 == r4 ? 0 : -1))
            if (r4 > 0) goto L11e
            int r4 = java.lang.Math.round(r2)     // Catch: java.lang.Exception -> L170
            r1.lux = r4     // Catch: java.lang.Exception -> L170
            java.lang.String r4 = "capture lux"
            r1.provenance = r4     // Catch: java.lang.Exception -> L170
        L11e:
            java.lang.String r4 = "cct"
            boolean r4 = r3.endsWith(r4)     // Catch: java.lang.Exception -> L170
            if (r4 != 0) goto L136
            java.lang.String r4 = "colortemperature"
            boolean r4 = r3.contains(r4)     // Catch: java.lang.Exception -> L170
            if (r4 != 0) goto L136
            java.lang.String r4 = "color_temperature"
            boolean r4 = r3.contains(r4)     // Catch: java.lang.Exception -> L170
            if (r4 == 0) goto L161
        L136:
            r4 = 1153138688(0x44bb8000, float:1500.0)
            int r4 = (r2 > r4 ? 1 : (r2 == r4 ? 0 : -1))
            if (r4 < 0) goto L161
            r4 = 1184645120(0x469c4000, float:20000.0)
            int r4 = (r2 > r4 ? 1 : (r2 == r4 ? 0 : -1))
            if (r4 > 0) goto L161
            int r4 = java.lang.Math.round(r2)     // Catch: java.lang.Exception -> L170
            r1.cct = r4     // Catch: java.lang.Exception -> L170
            java.lang.String r4 = r1.provenance     // Catch: java.lang.Exception -> L170
            java.lang.StringBuilder r6 = new java.lang.StringBuilder     // Catch: java.lang.Exception -> L170
            java.lang.String r4 = java.lang.String.valueOf(r4)     // Catch: java.lang.Exception -> L170
            r6.<init>(r4)     // Catch: java.lang.Exception -> L170
            java.lang.String r4 = " capture CCT"
            java.lang.StringBuilder r4 = r6.append(r4)     // Catch: java.lang.Exception -> L170
            java.lang.String r4 = r4.toString()     // Catch: java.lang.Exception -> L170
            r1.provenance = r4     // Catch: java.lang.Exception -> L170
        L161:
            java.lang.String r4 = "android.control.zoomratio"
            boolean r3 = r3.equals(r4)     // Catch: java.lang.Exception -> L170
            if (r3 == 0) goto Lf8
            int r3 = (r2 > r5 ? 1 : (r2 == r5 ? 0 : -1))
            if (r3 <= 0) goto Lf8
            r1.zoom = r2     // Catch: java.lang.Exception -> L170
            goto Lf8
        L170:
            r2 = move-exception
            java.lang.String r3 = "Capture trigger key unavailable"
            android.util.Log.d(r0, r3, r2)
            goto Lb9
        L178:
            return r1
    }
}
