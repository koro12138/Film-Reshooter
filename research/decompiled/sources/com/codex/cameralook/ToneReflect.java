package com.codex.cameralook;

import android.util.Log;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
final class ToneReflect {
    ToneReflect() {
    }

    static Object field(Object obj, String str) {
        if (obj == null) {
            return null;
        }
        for (Class<?> superclass = obj.getClass(); superclass != null; superclass = superclass.getSuperclass()) {
            try {
                Field declaredField = superclass.getDeclaredField(str);
                declaredField.setAccessible(true);
                return declaredField.get(obj);
            } catch (NoSuchFieldException e) {
            } catch (Exception e2) {
                return null;
            }
        }
        return null;
    }

    static Object call(Object obj, String str, Class<?>[] clsArr, Object... objArr) throws Exception {
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

    static Object singleton(String str) throws Exception {
        return Class.forName(str).getField("INSTANCE").get(null);
    }

    static void put(Object obj, String str, Object obj2) {
        if (obj == null) {
            return;
        }
        try {
            obj.getClass().getField(str).set(obj, obj2);
        } catch (Exception e) {
            Log.w("FullM9", "Capture size", e);
        }
    }
}
