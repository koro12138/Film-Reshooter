package com.codex.cameralook;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ColorSpace;
import android.media.ExifInterface;
import android.os.Build;
import android.util.Log;
import java.io.ByteArrayInputStream;
import java.io.IOException;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class ToneInput {
    ToneInput() {
    }

    static int orientation(byte[] bArr) {
        try {
            return new ExifInterface(new ByteArrayInputStream(bArr)).getAttributeInt("Orientation", 1);
        } catch (IOException e) {
            Log.d("FullM9", "No source orientation", e);
            return 1;
        }
    }

    static Bitmap decode(byte[] bArr, int i) throws IOException {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inMutable = true;
        options.inPreferredConfig = Bitmap.Config.ARGB_8888;
        options.inPreferredColorSpace = ColorSpace.get(ColorSpace.Named.SRGB);
        Bitmap bitmapDecodeByteArray = BitmapFactory.decodeByteArray(bArr, 0, bArr.length, options);
        if (bitmapDecodeByteArray == null) {
            throw new IOException("Cannot decode camera image");
        }
        if (Build.VERSION.SDK_INT >= 34) {
            Api34.clear(bitmapDecodeByteArray);
        }
        if (i < 2 || i > 8) {
            return bitmapDecodeByteArray;
        }
        try {
            Bitmap bitmapCreateBitmap = Bitmap.createBitmap(bitmapDecodeByteArray, 0, 0, bitmapDecodeByteArray.getWidth(), bitmapDecodeByteArray.getHeight(), ToneOrientation.matrix(i), false);
            if (bitmapCreateBitmap != bitmapDecodeByteArray) {
                bitmapDecodeByteArray.recycle();
            }
            return bitmapCreateBitmap;
        } catch (Error e) {
            bitmapDecodeByteArray.recycle();
            throw e;
        } catch (RuntimeException e2) {
            bitmapDecodeByteArray.recycle();
            throw e2;
        }
    }

    private static final class Api34 {
        private Api34() {
        }

        static void clear(Bitmap bitmap) {
            if (bitmap.hasGainmap()) {
                bitmap.setGainmap(null);
            }
        }
    }
}
