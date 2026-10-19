package com.codex.fullm9;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes17.dex */
final class LeicaParams {
    final int lutCount;
    final int lutOff;
    final byte[] raw;
    final java.util.Map<java.lang.String, java.util.List<com.codex.fullm9.LeicaParams.Bin>> scenes;
    final int shadeOff;
    final java.util.List<java.util.List<com.codex.fullm9.LeicaParams.Bin>> shadingTrees;
    final java.util.List<java.lang.Float> zooms;

    static final class Bin {
        int hi;
        int index;
        int lo;
        java.util.List<com.codex.fullm9.LeicaParams.Bin> sub;

        Bin(int r1, int r2, int r3) {
                r0 = this;
                r0.<init>()
                r0.lo = r1
                r0.hi = r2
                r0.index = r3
                return
        }
    }

    LeicaParams(android.content.Context r2) throws java.io.IOException {
            r1 = this;
            r0 = 0
            r1.<init>(r2, r0)
            return
    }

    LeicaParams(android.content.Context r17, boolean r18) throws java.io.IOException {
            r16 = this;
            r0 = r16
            r0.<init>()
            java.util.HashMap r1 = new java.util.HashMap
            r1.<init>()
            r0.scenes = r1
            java.util.ArrayList r1 = new java.util.ArrayList
            r1.<init>()
            r0.zooms = r1
            java.util.ArrayList r1 = new java.util.ArrayList
            r1.<init>()
            r0.shadingTrees = r1
            if (r18 == 0) goto L1f
            java.lang.String r1 = "leica_filter_param_m9_preview.bin"
            goto L21
        L1f:
            java.lang.String r1 = "leica_filter_param_m9_snapshot.bin"
        L21:
            r2 = r17
            byte[] r1 = com.codex.fullm9.Assets.read(r2, r1)
            r0.raw = r1
            byte[] r1 = r0.raw
            java.nio.ByteBuffer r1 = java.nio.ByteBuffer.wrap(r1)
            java.nio.ByteOrder r2 = java.nio.ByteOrder.LITTLE_ENDIAN
            java.nio.ByteBuffer r1 = r1.order(r2)
            int r2 = u(r1)
            int[] r3 = new int[r2]
            r4 = 0
            r5 = r4
        L3d:
            if (r5 < r2) goto Lff
            int r5 = u(r1)
            int r6 = u(r1)
            r0.lutOff = r6
            int r6 = u(r1)
            r7 = 17
            if (r6 != r7) goto Lf7
            int r6 = u(r1)
            int[] r8 = new int[r6]
            r9 = r4
        L58:
            if (r9 < r6) goto Le9
            r10 = r4
            r11 = r5
            r5 = r10
        L5d:
            if (r10 < r2) goto L8e
        L60:
            if (r4 < r6) goto L6f
            r0.lutCount = r5
            int r1 = r0.lutOff
            int r5 = r5 * r7
            int r5 = r5 * r7
            int r5 = r5 * r7
            int r5 = r5 * 3
            int r1 = r1 + r5
            r0.shadeOff = r1
            return
        L6f:
            r2 = r8[r4]
            r1.position(r11)
            java.util.List<java.lang.Float> r3 = r0.zooms
            float r9 = r1.getFloat()
            java.lang.Float r9 = java.lang.Float.valueOf(r9)
            r3.add(r9)
            java.util.List<java.util.List<com.codex.fullm9.LeicaParams$Bin>> r3 = r0.shadingTrees
            java.util.List r9 = tree(r1)
            r3.add(r9)
            int r11 = r11 + r2
            int r4 = r4 + 1
            goto L60
        L8e:
            r12 = r3[r10]
            r1.position(r11)
            r9 = 64
            byte[] r13 = new byte[r9]
            r1.get(r13)
            r14 = r4
        L9b:
            if (r14 >= r9) goto La5
            r15 = r13[r14]
            if (r15 != 0) goto La2
            goto La5
        La2:
            int r14 = r14 + 1
            goto L9b
        La5:
            java.util.List r9 = tree(r1)
            java.util.Map<java.lang.String, java.util.List<com.codex.fullm9.LeicaParams$Bin>> r15 = r0.scenes
            java.lang.String r7 = new java.lang.String
            java.lang.String r0 = "UTF-8"
            r7.<init>(r13, r4, r14, r0)
            r15.put(r7, r9)
            java.util.Iterator r0 = r9.iterator()
        Lb9:
            boolean r7 = r0.hasNext()
            if (r7 != 0) goto Lc7
            int r11 = r11 + r12
            int r10 = r10 + 1
            r7 = 17
            r0 = r16
            goto L5d
        Lc7:
            java.lang.Object r7 = r0.next()
            com.codex.fullm9.LeicaParams$Bin r7 = (com.codex.fullm9.LeicaParams.Bin) r7
            java.util.List<com.codex.fullm9.LeicaParams$Bin> r7 = r7.sub
            java.util.Iterator r7 = r7.iterator()
        Ld3:
            boolean r9 = r7.hasNext()
            if (r9 != 0) goto Lda
            goto Lb9
        Lda:
            java.lang.Object r9 = r7.next()
            com.codex.fullm9.LeicaParams$Bin r9 = (com.codex.fullm9.LeicaParams.Bin) r9
            int r9 = r9.index
            int r9 = r9 + 1
            int r5 = java.lang.Math.max(r5, r9)
            goto Ld3
        Le9:
            int r0 = u(r1)
            r8[r9] = r0
            int r9 = r9 + 1
            r7 = 17
            r0 = r16
            goto L58
        Lf7:
            java.io.IOException r0 = new java.io.IOException
            java.lang.String r1 = "M9 LUT size"
            r0.<init>(r1)
            throw r0
        Lff:
            int r0 = u(r1)
            r3[r5] = r0
            int r5 = r5 + 1
            r0 = r16
            goto L3d
    }

    static java.util.LinkedHashMap<java.lang.Integer, java.lang.Float> corners(java.util.List<com.codex.fullm9.LeicaParams.Bin> r6, int r7, int r8) {
            com.codex.fullm9.LeicaParams$Bin[] r6 = find(r6, r7)
            r0 = 0
            r1 = r6[r0]
            java.util.List<com.codex.fullm9.LeicaParams$Bin> r1 = r1.sub
            com.codex.fullm9.LeicaParams$Bin[] r1 = find(r1, r8)
            r2 = 1
            r3 = r6[r2]
            java.util.List<com.codex.fullm9.LeicaParams$Bin> r3 = r3.sub
            com.codex.fullm9.LeicaParams$Bin[] r3 = find(r3, r8)
            r4 = r6[r0]
            r6 = r6[r2]
            float r6 = fraction(r7, r4, r6)
            r7 = r1[r0]
            r4 = r1[r2]
            float r7 = fraction(r8, r7, r4)
            r4 = r3[r0]
            r5 = r3[r2]
            float r8 = fraction(r8, r4, r5)
            r4 = r1[r0]
            int r4 = r4.index
            r1 = r1[r2]
            int r1 = r1.index
            r5 = r3[r0]
            int r5 = r5.index
            r3 = r3[r2]
            int r3 = r3.index
            int[] r1 = new int[]{r4, r1, r5, r3}
            r3 = 1065353216(0x3f800000, float:1.0)
            float r4 = r3 - r6
            float r5 = r3 - r7
            float r5 = r5 * r4
            float r4 = r4 * r7
            float r3 = r3 - r8
            float r3 = r3 * r6
            float r6 = r6 * r8
            r7 = 4
            float[] r8 = new float[r7]
            r8[r0] = r5
            r8[r2] = r4
            r2 = 2
            r8[r2] = r3
            r2 = 3
            r8[r2] = r6
            java.util.LinkedHashMap r6 = new java.util.LinkedHashMap
            r6.<init>()
        L5f:
            if (r0 < r7) goto L62
            return r6
        L62:
            r2 = r1[r0]
            java.lang.Integer r2 = java.lang.Integer.valueOf(r2)
            r3 = r1[r0]
            java.lang.Integer r3 = java.lang.Integer.valueOf(r3)
            boolean r3 = r6.containsKey(r3)
            if (r3 == 0) goto L85
            r3 = r1[r0]
            java.lang.Integer r3 = java.lang.Integer.valueOf(r3)
            java.lang.Object r3 = r6.get(r3)
            java.lang.Float r3 = (java.lang.Float) r3
            float r3 = r3.floatValue()
            goto L86
        L85:
            r3 = 0
        L86:
            r4 = r8[r0]
            float r3 = r3 + r4
            java.lang.Float r3 = java.lang.Float.valueOf(r3)
            r6.put(r2, r3)
            int r0 = r0 + 1
            goto L5f
    }

    static com.codex.fullm9.LeicaParams.Bin[] find(java.util.List<com.codex.fullm9.LeicaParams.Bin> r6, int r7) {
            r0 = 0
            r1 = r0
        L2:
            int r2 = r6.size()
            r3 = 2
            r4 = 1
            if (r1 < r2) goto L1c
            int r7 = r6.size()
            int r7 = r7 - r4
            java.lang.Object r6 = r6.get(r7)
            com.codex.fullm9.LeicaParams$Bin r6 = (com.codex.fullm9.LeicaParams.Bin) r6
            com.codex.fullm9.LeicaParams$Bin[] r7 = new com.codex.fullm9.LeicaParams.Bin[r3]
            r7[r0] = r6
            r7[r4] = r6
            return r7
        L1c:
            java.lang.Object r2 = r6.get(r1)
            com.codex.fullm9.LeicaParams$Bin r2 = (com.codex.fullm9.LeicaParams.Bin) r2
            int r5 = r2.hi
            if (r7 > r5) goto L42
            int r5 = r2.lo
            if (r7 >= r5) goto L3b
            if (r1 != 0) goto L2d
            goto L3b
        L2d:
            com.codex.fullm9.LeicaParams$Bin[] r7 = new com.codex.fullm9.LeicaParams.Bin[r3]
            int r1 = r1 - r4
            java.lang.Object r6 = r6.get(r1)
            com.codex.fullm9.LeicaParams$Bin r6 = (com.codex.fullm9.LeicaParams.Bin) r6
            r7[r0] = r6
            r7[r4] = r2
            goto L41
        L3b:
            com.codex.fullm9.LeicaParams$Bin[] r7 = new com.codex.fullm9.LeicaParams.Bin[r3]
            r7[r0] = r2
            r7[r4] = r2
        L41:
            return r7
        L42:
            int r1 = r1 + 1
            goto L2
    }

    static float fraction(int r1, com.codex.fullm9.LeicaParams.Bin r2, com.codex.fullm9.LeicaParams.Bin r3) {
            int r3 = r3.lo
            int r0 = r2.hi
            int r3 = r3 - r0
            if (r3 != 0) goto L9
            r1 = 0
            goto Lf
        L9:
            int r2 = r2.hi
            int r1 = r1 - r2
            float r1 = (float) r1
            float r2 = (float) r3
            float r1 = r1 / r2
        Lf:
            return r1
    }

    static java.util.List<com.codex.fullm9.LeicaParams.Bin> tree(java.nio.ByteBuffer r12) {
            int r0 = u(r12)
            java.util.ArrayList r1 = new java.util.ArrayList
            r1.<init>()
            r2 = 0
            r3 = r2
        Lb:
            if (r3 < r0) goto Le
            return r1
        Le:
            com.codex.fullm9.LeicaParams$Bin r4 = new com.codex.fullm9.LeicaParams$Bin
            int r5 = u(r12)
            int r6 = u(r12)
            r7 = -1
            r4.<init>(r5, r6, r7)
            int r5 = u(r12)
            java.util.ArrayList r6 = new java.util.ArrayList
            r6.<init>()
            r4.sub = r6
            r6 = r2
        L28:
            if (r6 < r5) goto L30
            r1.add(r4)
            int r3 = r3 + 1
            goto Lb
        L30:
            java.util.List<com.codex.fullm9.LeicaParams$Bin> r7 = r4.sub
            com.codex.fullm9.LeicaParams$Bin r8 = new com.codex.fullm9.LeicaParams$Bin
            int r9 = u(r12)
            int r10 = u(r12)
            int r11 = u(r12)
            r8.<init>(r9, r10, r11)
            r7.add(r8)
            int r6 = r6 + 1
            goto L28
    }

    static int u(java.nio.ByteBuffer r1) {
            short r1 = r1.getShort()
            r0 = 65535(0xffff, float:9.1834E-41)
            r1 = r1 & r0
            return r1
    }

    byte[] lut(java.lang.String r10, int r11, int r12) {
            r9 = this;
            java.util.Map<java.lang.String, java.util.List<com.codex.fullm9.LeicaParams$Bin>> r0 = r9.scenes
            java.lang.Object r10 = r0.get(r10)
            java.util.List r10 = (java.util.List) r10
            if (r10 != 0) goto L14
            java.util.Map<java.lang.String, java.util.List<com.codex.fullm9.LeicaParams$Bin>> r10 = r9.scenes
            java.lang.String r0 = "common"
            java.lang.Object r10 = r10.get(r0)
            java.util.List r10 = (java.util.List) r10
        L14:
            java.util.LinkedHashMap r10 = corners(r10, r11, r12)
            r11 = 14739(0x3993, float:2.0654E-41)
            byte[] r12 = new byte[r11]
            int r0 = r10.size()
            r1 = 0
            r2 = 1
            if (r0 != r2) goto L40
            java.util.Set r10 = r10.keySet()
            java.util.Iterator r10 = r10.iterator()
            java.lang.Object r10 = r10.next()
            java.lang.Integer r10 = (java.lang.Integer) r10
            int r10 = r10.intValue()
            byte[] r0 = r9.raw
            int r2 = r9.lutOff
            int r10 = r10 * r11
            int r2 = r2 + r10
            java.lang.System.arraycopy(r0, r2, r12, r1, r11)
            return r12
        L40:
            float[] r0 = new float[r11]
            java.util.Set r10 = r10.entrySet()
            java.util.Iterator r10 = r10.iterator()
        L4a:
            boolean r2 = r10.hasNext()
            if (r2 != 0) goto L5c
        L50:
            if (r1 < r11) goto L53
            return r12
        L53:
            r10 = r0[r1]
            int r10 = (int) r10
            byte r10 = (byte) r10
            r12[r1] = r10
            int r1 = r1 + 1
            goto L50
        L5c:
            java.lang.Object r2 = r10.next()
            java.util.Map$Entry r2 = (java.util.Map.Entry) r2
            int r3 = r9.lutOff
            java.lang.Object r4 = r2.getKey()
            java.lang.Integer r4 = (java.lang.Integer) r4
            int r4 = r4.intValue()
            int r4 = r4 * r11
            int r3 = r3 + r4
            r4 = r1
        L71:
            if (r4 < r11) goto L74
            goto L4a
        L74:
            r5 = r0[r4]
            java.lang.Object r6 = r2.getValue()
            java.lang.Float r6 = (java.lang.Float) r6
            float r6 = r6.floatValue()
            byte[] r7 = r9.raw
            int r8 = r3 + r4
            r7 = r7[r8]
            r7 = r7 & 255(0xff, float:3.57E-43)
            float r7 = (float) r7
            float r6 = r6 * r7
            float r5 = r5 + r6
            r0[r4] = r5
            int r4 = r4 + 1
            goto L71
    }

    float[] shading(float r9, int r10, int r11) {
            r8 = this;
            r0 = 0
            r1 = r0
            r2 = r1
        L3:
            java.util.List<java.lang.Float> r3 = r8.zooms
            int r3 = r3.size()
            if (r1 < r3) goto L6a
            r3 = 8
            float[] r4 = new float[r3]
            byte[] r9 = r8.raw
            java.nio.ByteBuffer r9 = java.nio.ByteBuffer.wrap(r9)
            java.nio.ByteOrder r1 = java.nio.ByteOrder.LITTLE_ENDIAN
            java.nio.ByteBuffer r5 = r9.order(r1)
            java.util.List<java.util.List<com.codex.fullm9.LeicaParams$Bin>> r9 = r8.shadingTrees
            java.lang.Object r9 = r9.get(r2)
            java.util.List r9 = (java.util.List) r9
            java.util.LinkedHashMap r9 = corners(r9, r10, r11)
            java.util.Set r9 = r9.entrySet()
            java.util.Iterator r6 = r9.iterator()
        L2f:
            boolean r9 = r6.hasNext()
            if (r9 != 0) goto L36
            return r4
        L36:
            java.lang.Object r9 = r6.next()
            r7 = r9
            java.util.Map$Entry r7 = (java.util.Map.Entry) r7
            int r9 = r8.shadeOff
            java.lang.Object r10 = r7.getKey()
            java.lang.Integer r10 = (java.lang.Integer) r10
            int r10 = r10.intValue()
            int r10 = r10 * 32
            int r9 = r9 + r10
            r5.position(r9)
            r9 = r0
        L50:
            if (r9 < r3) goto L53
            goto L2f
        L53:
            r10 = r4[r9]
            java.lang.Object r11 = r7.getValue()
            java.lang.Float r11 = (java.lang.Float) r11
            float r11 = r11.floatValue()
            float r1 = r5.getFloat()
            float r11 = r11 * r1
            float r10 = r10 + r11
            r4[r9] = r10
            int r9 = r9 + 1
            goto L50
        L6a:
            java.util.List<java.lang.Float> r3 = r8.zooms
            java.lang.Object r3 = r3.get(r1)
            java.lang.Float r3 = (java.lang.Float) r3
            float r3 = r3.floatValue()
            int r3 = (r9 > r3 ? 1 : (r9 == r3 ? 0 : -1))
            if (r3 < 0) goto L7b
            r2 = r1
        L7b:
            int r1 = r1 + 1
            goto L3
    }
}
