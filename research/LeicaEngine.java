package com.leicamoments.app;

import android.content.Context;
import com.codex.lmoments.LegendaryPostProcessor;
import com.codex.lmoments.MadridLegendary;
import lmktln.Metadata;
import lmktln.NoWhenBranchMatchedException;
import lmktln.Unit;
import lmktln.enums.EnumEntries;
import lmktln.enums.EnumEntriesKt;
import lmktln.jvm.functions.Function1;
import lmktln.jvm.internal.DefaultConstructorMarker;
import lmktln.jvm.internal.Intrinsics;

/* JADX INFO: compiled from: LeicaEngine.kt */
/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes15.dex */
public final class LeicaEngine {
    public static final LeicaEngine INSTANCE = new LeicaEngine();

    /* JADX INFO: compiled from: LeicaEngine.kt */
    @Metadata(k = 3, mv = {1, 9, 0}, xi = 48)
    public /* synthetic */ class WhenMappings {
        public static final /* synthetic */ int[] $EnumSwitchMapping$0;

        static {
            int[] iArr = new int[Style.values().length];
            try {
                iArr[Style.M3.ordinal()] = 1;
            } catch (NoSuchFieldError e) {
            }
            try {
                iArr[Style.M9.ordinal()] = 2;
            } catch (NoSuchFieldError e2) {
            }
            $EnumSwitchMapping$0 = iArr;
        }
    }

    private LeicaEngine() {
    }

    /* JADX INFO: compiled from: LeicaEngine.kt */
    public enum Style {
        M3("M3", "M3", "黑白经典"),
        M9("M9", "M9", "彩色经典");

        private final String desc;
        private final String id;
        private final String label;
        private static final /* synthetic */ EnumEntries $ENTRIES = EnumEntriesKt.enumEntries($VALUES);
        public static final Companion Companion = new Companion(null);

        public static EnumEntries<Style> getEntries() {
            return $ENTRIES;
        }

        Style(String id, String label, String desc) {
            this.id = id;
            this.label = label;
            this.desc = desc;
        }

        public final String getDesc() {
            return this.desc;
        }

        public final String getId() {
            return this.id;
        }

        public final String getLabel() {
            return this.label;
        }

        /* JADX INFO: compiled from: LeicaEngine.kt */
        @Metadata(d1 = {"\u0000\u0018\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0000\n\u0002\u0010\u000e\n\u0000\b\u0086\u0003\u0018\u00002\u00020\u0001B\u0007\b\u0002¢\u0006\u0002\u0010\u0002J\u0010\u0010\u0003\u001a\u00020\u00042\b\u0010\u0005\u001a\u0004\u0018\u00010\u0006¨\u0006\u0007"}, d2 = {"Lcom/leicamoments/app/LeicaEngine$Style$Companion;", "", "()V", "fromId", "Lcom/leicamoments/app/LeicaEngine$Style;", "id", "", "app_debug"}, k = 1, mv = {1, 9, 0}, xi = 48)
        public static final class Companion {
            public /* synthetic */ Companion(DefaultConstructorMarker defaultConstructorMarker) {
                this();
            }

            private Companion() {
            }

            /* JADX WARN: Code duplicated, block: B:10:0x001e  */
            /* JADX WARN: Code duplicated, block: B:14:? A[RETURN, SYNTHETIC] */
            public final Style fromId(String id) {
                for (Style style : Style.values()) {
                    if (Intrinsics.areEqual(style.getId(), id)) {
                        if (style == null) {
                            return Style.M9;
                        }
                        return style;
                    }
                }
                style = null;
                if (style == null) {
                    return Style.M9;
                }
                return style;
            }
        }
    }

    /* JADX WARN: Multi-variable type inference failed */
    public static /* synthetic */ byte[] process$default(LeicaEngine leicaEngine, Context context, byte[] bArr, Style style, Function1 function1, boolean z, int i, Object obj) {
        boolean z2;
        if ((i & 8) != 0) {
            function1 = null;
        }
        Function1 function2 = function1;
        if ((i & 16) == 0) {
            z2 = z;
        } else {
            z2 = true;
        }
        return leicaEngine.process(context, bArr, style, function2, z2);
    }

    public final byte[] process(Context context, byte[] jpeg, Style style, Function1<? super Style, Unit> function1, boolean allowCpuFallback) {
        Intrinsics.checkNotNullParameter(context, "context");
        Intrinsics.checkNotNullParameter(jpeg, "jpeg");
        Intrinsics.checkNotNullParameter(style, "style");
        Context app = context.getApplicationContext();
        byte[] input = ImageUtils.INSTANCE.normalizeExifOrientation(jpeg);
        switch (WhenMappings.$EnumSwitchMapping$0[style.ordinal()]) {
            case 1:
                Intrinsics.checkNotNull(app);
                return processM3(app, input, function1);
            case 2:
                Intrinsics.checkNotNull(app);
                return processM9(app, input, function1, allowCpuFallback);
            default:
                throw new NoWhenBranchMatchedException();
        }
    }

    private final byte[] processM3(Context app, byte[] jpeg, Function1<? super Style, Unit> function1) {
        byte[] it = LegendaryPostProcessor.processM3(app, jpeg);
        if (it != null && it != jpeg) {
            return M3Mono.INSTANCE.ensure(it);
        }
        DiagLog.INSTANCE.w("Engine", "M3 完整链不可用，降级旧链");
        byte[] out = MadridLegendary.process(app, jpeg, "M3");
        if (function1 != null) {
            function1.invoke(Style.M3);
        }
        M3Mono m3Mono = M3Mono.INSTANCE;
        Intrinsics.checkNotNull(out);
        return m3Mono.ensure(out);
    }

    private final byte[] processM9(Context app, byte[] jpeg, Function1<? super Style, Unit> function1, boolean allowCpuFallback) {
        byte[] it;
        byte[] it2 = LegendaryPostProcessor.processM9(app, jpeg);
        if (it2 != null) {
            return it2;
        }
        if (!allowCpuFallback || (it = M9CpuFallback.INSTANCE.run(app, jpeg)) == null) {
            DiagLog.INSTANCE.w("Engine", "M9 降级纯 LUT (allowCpuFallback=" + allowCpuFallback + ")");
            if (function1 != null) {
                function1.invoke(Style.M9);
            }
            byte[] bArrProcess = MadridLegendary.process(app, jpeg, "M9");
            Intrinsics.checkNotNullExpressionValue(bArrProcess, "process(...)");
            return bArrProcess;
        }
        DiagLog.INSTANCE.w("Engine", "M9 完整链不可用，CPU 补丁链接管");
        return it;
    }
}
