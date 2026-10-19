package com.codex.cameralook;

import android.graphics.Matrix;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class ToneOrientation {
    ToneOrientation() {
    }

    static float[] coefficients(int i) {
        switch (i) {
            case 2:
                return new float[]{-1.0f, 0.0f, 0.0f, 1.0f};
            case 3:
                return new float[]{-1.0f, 0.0f, 0.0f, -1.0f};
            case 4:
                return new float[]{1.0f, 0.0f, 0.0f, -1.0f};
            case 5:
                return new float[]{0.0f, 1.0f, 1.0f, 0.0f};
            case 6:
                return new float[]{0.0f, -1.0f, 1.0f, 0.0f};
            case 7:
                return new float[]{0.0f, -1.0f, -1.0f, 0.0f};
            case 8:
                return new float[]{0.0f, 1.0f, -1.0f, 0.0f};
            default:
                return new float[]{1.0f, 0.0f, 0.0f, 1.0f};
        }
    }

    static Matrix matrix(int i) {
        float[] fArrCoefficients = coefficients(i);
        Matrix matrix = new Matrix();
        matrix.setValues(new float[]{fArrCoefficients[0], fArrCoefficients[1], 0.0f, fArrCoefficients[2], fArrCoefficients[3], 0.0f, 0.0f, 0.0f, 1.0f});
        return matrix;
    }
}
