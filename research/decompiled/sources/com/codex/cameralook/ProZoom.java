package com.codex.cameralook;

import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Map;
import java.util.WeakHashMap;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
public final class ProZoom {
    private static final Map<View, Entry> ANCHORS = new WeakHashMap();

    private static final class Entry {
        final boolean bound;
        final int mode;
        final float ratio;

        Entry(int i, float f, boolean z) {
            this.mode = i;
            this.ratio = f;
            this.bound = z;
        }
    }

    static boolean professional(int i) {
        return i == 167 || i == 180;
    }

    static boolean valid(float f) {
        return Float.isFinite(f) && f > 0.0f && f <= 100.0f;
    }

    static int mode(Object obj) {
        Object objField = ToneReflect.field(obj, "b");
        if (objField instanceof Number) {
            return ((Number) objField).intValue();
        }
        return -1;
    }

    static Method method(Object obj, String str, Class<?>... clsArr) throws Exception {
        Class<?> superclass = obj instanceof Class ? (Class) obj : obj.getClass();
        try {
            return superclass.getMethod(str, clsArr);
        } catch (NoSuchMethodException e) {
            while (superclass != null) {
                try {
                    Method declaredMethod = superclass.getDeclaredMethod(str, clsArr);
                    declaredMethod.setAccessible(true);
                    return declaredMethod;
                } catch (NoSuchMethodException e2) {
                    superclass = superclass.getSuperclass();
                }
            }
            throw e;
        }
    }

    static Object call(Object obj, String str, Class<?>[] clsArr, Object... objArr) throws Exception {
        Method method = method(obj, str, clsArr);
        if (obj instanceof Class) {
            obj = null;
        }
        return method.invoke(obj, objArr);
    }

    public static synchronized float anchor(View view, float f) {
        if (view != null) {
            int iMode = mode(view);
            if (professional(iMode)) {
                Entry entry = ANCHORS.get(view);
                if (entry != null && entry.mode == iMode) {
                    f = entry.ratio;
                }
                ViewParent parent = view.getParent();
                boolean z = false;
                if (parent instanceof ViewGroup) {
                    int iIndexOfChild = ((ViewGroup) parent).indexOfChild(view);
                    Object objField = ToneReflect.field(parent, "q");
                    if (iIndexOfChild >= 0 && (objField instanceof Number) && ((Number) objField).intValue() == iMode) {
                        try {
                            float fFloatValue = ((Number) call(parent, "m", new Class[]{Integer.TYPE, Integer.TYPE, Boolean.TYPE, Boolean.TYPE}, Integer.valueOf(iMode), Integer.valueOf(iIndexOfChild), Boolean.valueOf(Boolean.TRUE.equals(ToneReflect.field(parent, "a"))), false)).floatValue();
                            if (valid(fFloatValue)) {
                                z = true;
                                f = fFloatValue;
                            }
                        } catch (Exception e) {
                        }
                    }
                }
                if (valid(f)) {
                    ANCHORS.put(view, new Entry(iMode, f, z));
                }
                return f;
            }
            ANCHORS.remove(view);
        }
        return f;
    }

    public static boolean click(View view, boolean z) {
        int iIndexOfChild;
        if (view == null || !professional(mode(view))) {
            return false;
        }
        ViewParent parent = view.getParent();
        if (!(parent instanceof ViewGroup) || !parent.getClass().getName().equals("com.android.camera.ui.zoom.ZoomRatioToggleView") || (iIndexOfChild = ((ViewGroup) parent).indexOfChild(view)) < 0) {
            return false;
        }
        try {
            int iMode = mode(view);
            Object objField = ToneReflect.field(parent, "q");
            if (!(objField instanceof Number) || ((Number) objField).intValue() != iMode || ToneReflect.field(parent, "L") == null || !valid(anchor(view, ((Number) call(view, "getZoomRatio", new Class[0], new Object[0])).floatValue()))) {
                return false;
            }
            Field field = parent.getClass().getField("P");
            boolean z2 = field.getBoolean(parent);
            try {
                field.setBoolean(parent, false);
                call(parent, "T", new Class[]{Integer.TYPE, Integer.TYPE, Boolean.TYPE, Boolean.TYPE, Boolean.TYPE, Boolean.TYPE}, Integer.valueOf(iIndexOfChild), 18, true, true, false, Boolean.valueOf(z));
                return true;
            } finally {
                field.setBoolean(parent, z2);
            }
        } catch (Exception e) {
            return false;
        } catch (LinkageError e2) {
            return false;
        }
    }
}
