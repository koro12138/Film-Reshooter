package com.codex.cameralook;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class ToneTable {
    final float[] data;
    final float[] max;
    final float[] min;
    final int n;

    ToneTable(InputStream inputStream) throws IOException {
        DataInputStream dataInputStream = new DataInputStream(new BufferedInputStream(inputStream));
        if (dataInputStream.readInt() != 1129076017) {
            throw new IOException("Invalid LUT magic");
        }
        this.n = dataInputStream.readInt();
        if (this.n < 2 || this.n > 65) {
            throw new IOException("Invalid LUT size");
        }
        this.min = new float[3];
        this.max = new float[3];
        for (int i = 0; i < 3; i++) {
            this.min[i] = dataInputStream.readFloat();
        }
        for (int i2 = 0; i2 < 3; i2++) {
            this.max[i2] = dataInputStream.readFloat();
        }
        for (int i3 = 0; i3 < 3; i3++) {
            if (!Float.isFinite(this.min[i3]) || !Float.isFinite(this.max[i3]) || this.min[i3] >= this.max[i3]) {
                throw new IOException("Invalid LUT domain");
            }
        }
        this.data = new float[this.n * this.n * this.n * 3];
        for (int i4 = 0; i4 < this.data.length; i4++) {
            this.data[i4] = dataInputStream.readFloat();
            if (!Float.isFinite(this.data[i4])) {
                throw new IOException("Nonfinite LUT");
            }
        }
        if (dataInputStream.read() != -1) {
            throw new IOException("Unexpected LUT data");
        }
    }

    void map(float f, float f2, float f3, float[] fArr) {
        int i;
        int i2;
        float fClamp = ToneMath.clamp((f - this.min[0]) / (this.max[0] - this.min[0])) * (this.n - 1);
        float fClamp2 = ToneMath.clamp((f2 - this.min[1]) / (this.max[1] - this.min[1])) * (this.n - 1);
        float fClamp3 = ToneMath.clamp((f3 - this.min[2]) / (this.max[2] - this.min[2])) * (this.n - 1);
        int iMin = Math.min(this.n - 2, (int) fClamp);
        int iMin2 = Math.min(this.n - 2, (int) fClamp2);
        int iMin3 = Math.min(this.n - 2, (int) fClamp3);
        float f4 = fClamp - iMin;
        float f5 = fClamp2 - iMin2;
        float f6 = fClamp3 - iMin3;
        int i3 = this.n * 3;
        int i4 = this.n * this.n * 3;
        if (f4 >= f5) {
            if (f5 >= f6) {
                i = i3 + 3;
            } else if (f4 >= f6) {
                i = i4 + 3;
                f6 = f5;
                f5 = f6;
            } else {
                i = i4 + 3;
                f5 = f4;
                f4 = f6;
                f6 = f5;
                i2 = i4;
            }
            i2 = 3;
        } else {
            if (f4 >= f6) {
                i = i3 + 3;
                f5 = f4;
                f4 = f5;
            } else if (f5 >= f6) {
                i = i3 + i4;
                f6 = f4;
                f4 = f5;
                f5 = f6;
            } else {
                i = i4 + i3;
                f6 = f4;
                f4 = f6;
                i2 = i4;
            }
            i2 = i3;
        }
        int i5 = (iMin * 3) + (iMin2 * i3) + (iMin3 * i4);
        int i6 = i3 + 3 + i4;
        for (int i7 = 0; i7 < 3; i7++) {
            float f7 = this.data[i5 + i7];
            float f8 = this.data[i5 + i2 + i7];
            float f9 = this.data[i5 + i + i7];
            fArr[i7] = ToneMath.clamp(f7 + ((f8 - f7) * f4) + ((f9 - f8) * f5) + ((this.data[(i5 + i6) + i7] - f9) * f6));
        }
    }
}
