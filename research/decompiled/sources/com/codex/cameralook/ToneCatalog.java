package com.codex.cameralook;

/* JADX INFO: loaded from: D:\摄影\CameraLookDesktop\research\classes19.dex */
public final class ToneCatalog {
    public static final int COUNT = 23;
    public static final int FIRST = 16;

    public static boolean valid(int i) {
        return i >= 16 && i < 39;
    }

    public static String[] names() {
        return new String[]{"富士 CC II", "珠光", "Pocket", "富士 NN", "富士 NC", "理光正片", "理光负片", "全能 400", "哈苏蓝", "柯达 5207", "富士 CC", "800T 冷调", "富士 C200", "G7X II", "柯达 5219", "Classic U", "G12", "柯达正片 64", "Portra 160", "哈苏蓝 II", "松下 S9 暖调", "理光 GR III", "适马 BF"};
    }

    public static String name(int i) {
        if (valid(i)) {
            return names()[i - 16];
        }
        throw new IllegalArgumentException("Tone ID");
    }

    public static String intro(String str) {
        if ("富士 CC II_intro".equalsIgnoreCase(str)) {
            return "富士 CC II\n青绿层次与温暖建筑，适合街景和阴天风景。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("珠光_intro".equalsIgnoreCase(str)) {
            return "珠光\n明亮柔和的浅色层次，适合静物和柔光场景。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("Pocket_intro".equalsIgnoreCase(str)) {
            return "Pocket\n清透轻快的日常色彩，适合街拍与旅行。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("富士 NN_intro".equalsIgnoreCase(str)) {
            return "富士 NN\n柔和胶片层次与细腻颗粒，适合日常风景。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("富士 NC_intro".equalsIgnoreCase(str)) {
            return "富士 NC\n更明显的胶片颗粒与色彩氛围，适合街景。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("理光正片_intro".equalsIgnoreCase(str)) {
            return "理光正片\n鲜明色彩与清晰反差，适合晴天建筑和风景。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("理光负片_intro".equalsIgnoreCase(str)) {
            return "理光负片\n柔和的负片色彩，适合阴天街巷。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("全能 400_intro".equalsIgnoreCase(str)) {
            return "全能 400\n均衡胶片层次与颗粒，适合旅行、人文。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("哈苏蓝_intro".equalsIgnoreCase(str)) {
            return "哈苏蓝\n蓝色层次与柔和质感，适合海岸和远山。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("柯达 5207_intro".equalsIgnoreCase(str)) {
            return "柯达 5207\n温暖电影胶片色彩，适合夕阳与旧街。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("富士 CC_intro".equalsIgnoreCase(str)) {
            return "富士 CC\n含蓄的青绿与暖色，适合城市和阴天。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("800T 冷调_intro".equalsIgnoreCase(str)) {
            return "800T 冷调\n冷调电影夜景色彩，适合霓虹和夜街。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("富士 C200_intro".equalsIgnoreCase(str)) {
            return "富士 C200\n明亮胶片色彩与颗粒，适合绿植和日光。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("G7X II_intro".equalsIgnoreCase(str)) {
            return "G7X II\n轻快清透的日常色彩，适合旅行与广场。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("柯达 5219_intro".equalsIgnoreCase(str)) {
            return "柯达 5219\n电影负片层次与柔和高光，适合傍晚。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("Classic U_intro".equalsIgnoreCase(str)) {
            return "Classic U\n复古暖色与颗粒质感，适合老街。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("G12_intro".equalsIgnoreCase(str)) {
            return "G12\n轻盈的复古数码色彩，适合日常静物。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("柯达正片 64_intro".equalsIgnoreCase(str)) {
            return "柯达正片 64\n鲜明的暖色与蓝天，适合晴天风景。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("Portra 160_intro".equalsIgnoreCase(str)) {
            return "Portra 160\n柔和暖色与细腻层次，适合自然光场景。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("哈苏蓝 II_intro".equalsIgnoreCase(str)) {
            return "哈苏蓝 II\n蓝色与暖色层次的第二种表达，适合海港。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("松下 S9 暖调_intro".equalsIgnoreCase(str)) {
            return "松下 S9 暖调\n温暖的复古气氛，适合咖啡馆和傍晚。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("理光 GR III_intro".equalsIgnoreCase(str)) {
            return "理光 GR III\n克制的日常街拍色彩与轻颗粒。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        if ("适马 BF_intro".equalsIgnoreCase(str)) {
            return "适马 BF\n清爽现代的色彩，适合建筑和绿植。\n本地影调适配 · 原尺寸成片\n介绍图为AI风格示意，不是实拍对照。";
        }
        return null;
    }

    static ToneMath.Params params(int i) {
        switch (i) {
            case 0:
                ToneMath.Params params = new ToneMath.Params();
                params.strength = 1.5f;
                params.grain = 20.0f;
                params.shadows = 30.0f;
                params.midtones = 30.0f;
                params.highlights = 15.0f;
                params.grainSize = 10.0f;
                params.roughness = 15.0f;
                params.colorVariation = 0.0f;
                params.vignette = -20.0f;
                params.midpoint = 25.0f;
                params.clarity = 0.0f;
                params.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params;
            case 1:
                ToneMath.Params params2 = new ToneMath.Params();
                params2.strength = 1.55f;
                params2.grain = 0.0f;
                params2.shadows = 0.0f;
                params2.midtones = 0.0f;
                params2.highlights = 0.0f;
                params2.grainSize = 30.0f;
                params2.roughness = 30.0f;
                params2.colorVariation = 0.0f;
                params2.vignette = 0.0f;
                params2.midpoint = 50.0f;
                params2.clarity = 0.0f;
                params2.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params2.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params2;
            case 2:
                ToneMath.Params params3 = new ToneMath.Params();
                params3.strength = 1.5f;
                params3.grain = 0.0f;
                params3.shadows = 0.0f;
                params3.midtones = 0.0f;
                params3.highlights = 0.0f;
                params3.grainSize = 30.0f;
                params3.roughness = 30.0f;
                params3.colorVariation = 0.0f;
                params3.vignette = 0.0f;
                params3.midpoint = 50.0f;
                params3.clarity = 0.0f;
                params3.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params3.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params3;
            case 3:
                ToneMath.Params params4 = new ToneMath.Params();
                params4.strength = 1.45f;
                params4.grain = 30.0f;
                params4.shadows = 30.0f;
                params4.midtones = 50.0f;
                params4.highlights = 15.0f;
                params4.grainSize = 10.0f;
                params4.roughness = 15.0f;
                params4.colorVariation = 10.0f;
                params4.vignette = -45.0f;
                params4.midpoint = 30.0f;
                params4.clarity = 0.0f;
                params4.luma = new float[]{0.0f, 0.0f, 78.0f, 85.0f, 135.0f, 137.0f, 255.0f, 255.0f};
                params4.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params4;
            case 4:
                ToneMath.Params params5 = new ToneMath.Params();
                params5.strength = 1.35f;
                params5.grain = 60.0f;
                params5.shadows = 30.0f;
                params5.midtones = 50.0f;
                params5.highlights = 15.0f;
                params5.grainSize = 10.0f;
                params5.roughness = 15.0f;
                params5.colorVariation = 10.0f;
                params5.vignette = -45.0f;
                params5.midpoint = 30.0f;
                params5.clarity = 0.0f;
                params5.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params5.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params5;
            case 5:
                ToneMath.Params params6 = new ToneMath.Params();
                params6.strength = 1.4f;
                params6.grain = 0.0f;
                params6.shadows = 0.0f;
                params6.midtones = 0.0f;
                params6.highlights = 0.0f;
                params6.grainSize = 0.0f;
                params6.roughness = 0.0f;
                params6.colorVariation = 0.0f;
                params6.vignette = 0.0f;
                params6.midpoint = 50.0f;
                params6.clarity = 0.0f;
                params6.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params6.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params6;
            case 6:
                ToneMath.Params params7 = new ToneMath.Params();
                params7.strength = 1.35f;
                params7.grain = 0.0f;
                params7.shadows = 0.0f;
                params7.midtones = 0.0f;
                params7.highlights = 0.0f;
                params7.grainSize = 0.0f;
                params7.roughness = 0.0f;
                params7.colorVariation = 0.0f;
                params7.vignette = 0.0f;
                params7.midpoint = 50.0f;
                params7.clarity = 0.0f;
                params7.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params7.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params7;
            case 7:
                ToneMath.Params params8 = new ToneMath.Params();
                params8.strength = 1.4f;
                params8.grain = 30.0f;
                params8.shadows = 30.0f;
                params8.midtones = 50.0f;
                params8.highlights = 15.0f;
                params8.grainSize = 10.0f;
                params8.roughness = 15.0f;
                params8.colorVariation = 10.0f;
                params8.vignette = -10.0f;
                params8.midpoint = 50.0f;
                params8.clarity = 0.0f;
                params8.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params8.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params8;
            case 8:
                ToneMath.Params params9 = new ToneMath.Params();
                params9.strength = 1.75f;
                params9.grain = 10.0f;
                params9.shadows = 50.0f;
                params9.midtones = 30.0f;
                params9.highlights = 15.0f;
                params9.grainSize = 30.0f;
                params9.roughness = 30.0f;
                params9.colorVariation = 0.0f;
                params9.vignette = -63.0f;
                params9.midpoint = 10.0f;
                params9.clarity = -10.0f;
                params9.luma = new float[]{5.0f, 0.0f, 89.0f, 88.0f, 255.0f, 241.0f};
                params9.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params9;
            case 9:
                ToneMath.Params params10 = new ToneMath.Params();
                params10.strength = 1.5f;
                params10.grain = 50.0f;
                params10.shadows = 45.0f;
                params10.midtones = 30.0f;
                params10.highlights = 15.0f;
                params10.grainSize = 10.0f;
                params10.roughness = 15.0f;
                params10.colorVariation = 10.0f;
                params10.vignette = -10.0f;
                params10.midpoint = 50.0f;
                params10.clarity = 0.0f;
                params10.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params10.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params10;
            case 10:
                ToneMath.Params params11 = new ToneMath.Params();
                params11.strength = 1.7f;
                params11.grain = 20.0f;
                params11.shadows = 50.0f;
                params11.midtones = 30.0f;
                params11.highlights = 15.0f;
                params11.grainSize = 30.0f;
                params11.roughness = 30.0f;
                params11.colorVariation = 0.0f;
                params11.vignette = -35.0f;
                params11.midpoint = 20.0f;
                params11.clarity = 0.0f;
                params11.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params11.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params11;
            case 11:
                ToneMath.Params params12 = new ToneMath.Params();
                params12.strength = 1.5f;
                params12.grain = 25.0f;
                params12.shadows = 50.0f;
                params12.midtones = 30.0f;
                params12.highlights = 15.0f;
                params12.grainSize = 30.0f;
                params12.roughness = 30.0f;
                params12.colorVariation = 0.0f;
                params12.vignette = -50.0f;
                params12.midpoint = 30.0f;
                params12.clarity = 0.0f;
                params12.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params12.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params12;
            case 12:
                ToneMath.Params params13 = new ToneMath.Params();
                params13.strength = 1.4f;
                params13.grain = 50.0f;
                params13.shadows = 40.0f;
                params13.midtones = 30.0f;
                params13.highlights = 15.0f;
                params13.grainSize = 35.0f;
                params13.roughness = 30.0f;
                params13.colorVariation = 0.0f;
                params13.vignette = 0.0f;
                params13.midpoint = 50.0f;
                params13.clarity = 0.0f;
                params13.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params13.rgb = new float[]{0.0f, 0.0f, 105.0f, 109.0f, 197.0f, 206.0f, 255.0f, 255.0f};
                return params13;
            case 13:
                ToneMath.Params params14 = new ToneMath.Params();
                params14.strength = 1.5f;
                params14.grain = 0.0f;
                params14.shadows = 0.0f;
                params14.midtones = 0.0f;
                params14.highlights = 0.0f;
                params14.grainSize = 0.0f;
                params14.roughness = 0.0f;
                params14.colorVariation = 0.0f;
                params14.vignette = 0.0f;
                params14.midpoint = 50.0f;
                params14.clarity = 0.0f;
                params14.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params14.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params14;
            case 14:
                ToneMath.Params params15 = new ToneMath.Params();
                params15.strength = 1.4f;
                params15.grain = 60.0f;
                params15.shadows = 55.0f;
                params15.midtones = 20.0f;
                params15.highlights = 15.0f;
                params15.grainSize = 10.0f;
                params15.roughness = 30.0f;
                params15.colorVariation = 0.0f;
                params15.vignette = -45.0f;
                params15.midpoint = 0.0f;
                params15.clarity = 0.0f;
                params15.luma = new float[]{0.0f, 0.0f, 149.0f, 148.0f, 193.0f, 189.0f, 255.0f, 255.0f};
                params15.rgb = new float[]{0.0f, 0.0f, 41.0f, 36.0f, 118.0f, 115.0f, 255.0f, 255.0f};
                return params15;
            case 15:
                ToneMath.Params params16 = new ToneMath.Params();
                params16.strength = 1.45f;
                params16.grain = 40.0f;
                params16.shadows = 40.0f;
                params16.midtones = 30.0f;
                params16.highlights = 15.0f;
                params16.grainSize = 20.0f;
                params16.roughness = 20.0f;
                params16.colorVariation = 20.0f;
                params16.vignette = -30.0f;
                params16.midpoint = 0.0f;
                params16.clarity = 0.0f;
                params16.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params16.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params16;
            case FIRST /* 16 */:
                ToneMath.Params params17 = new ToneMath.Params();
                params17.strength = 1.45f;
                params17.grain = 0.0f;
                params17.shadows = 0.0f;
                params17.midtones = 0.0f;
                params17.highlights = 0.0f;
                params17.grainSize = 30.0f;
                params17.roughness = 30.0f;
                params17.colorVariation = 0.0f;
                params17.vignette = 0.0f;
                params17.midpoint = 50.0f;
                params17.clarity = 0.0f;
                params17.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params17.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params17;
            case 17:
                ToneMath.Params params18 = new ToneMath.Params();
                params18.strength = 1.5f;
                params18.grain = 50.0f;
                params18.shadows = 50.0f;
                params18.midtones = 30.0f;
                params18.highlights = 15.0f;
                params18.grainSize = 30.0f;
                params18.roughness = 30.0f;
                params18.colorVariation = 0.0f;
                params18.vignette = -40.0f;
                params18.midpoint = 30.0f;
                params18.clarity = 0.0f;
                params18.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params18.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params18;
            case 18:
                ToneMath.Params params19 = new ToneMath.Params();
                params19.strength = 1.5f;
                params19.grain = 25.0f;
                params19.shadows = 50.0f;
                params19.midtones = 35.0f;
                params19.highlights = 15.0f;
                params19.grainSize = 30.0f;
                params19.roughness = 30.0f;
                params19.colorVariation = 0.0f;
                params19.vignette = -35.0f;
                params19.midpoint = 35.0f;
                params19.clarity = 0.0f;
                params19.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params19.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params19;
            case 19:
                ToneMath.Params params20 = new ToneMath.Params();
                params20.strength = 1.4f;
                params20.grain = 15.0f;
                params20.shadows = 30.0f;
                params20.midtones = 35.0f;
                params20.highlights = 15.0f;
                params20.grainSize = 10.0f;
                params20.roughness = 15.0f;
                params20.colorVariation = 10.0f;
                params20.vignette = -11.0f;
                params20.midpoint = 28.0f;
                params20.clarity = -6.0f;
                params20.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params20.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params20;
            case 20:
                ToneMath.Params params21 = new ToneMath.Params();
                params21.strength = 1.45f;
                params21.grain = 25.0f;
                params21.shadows = 50.0f;
                params21.midtones = 30.0f;
                params21.highlights = 15.0f;
                params21.grainSize = 30.0f;
                params21.roughness = 30.0f;
                params21.colorVariation = 0.0f;
                params21.vignette = -50.0f;
                params21.midpoint = 30.0f;
                params21.clarity = 0.0f;
                params21.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params21.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params21;
            case 21:
                ToneMath.Params params22 = new ToneMath.Params();
                params22.strength = 1.4f;
                params22.grain = 10.0f;
                params22.shadows = 50.0f;
                params22.midtones = 30.0f;
                params22.highlights = 15.0f;
                params22.grainSize = 30.0f;
                params22.roughness = 30.0f;
                params22.colorVariation = 0.0f;
                params22.vignette = 0.0f;
                params22.midpoint = 50.0f;
                params22.clarity = -5.0f;
                params22.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params22.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params22;
            case 22:
                ToneMath.Params params23 = new ToneMath.Params();
                params23.strength = 1.45f;
                params23.grain = 6.0f;
                params23.shadows = 6.0f;
                params23.midtones = 6.0f;
                params23.highlights = 6.0f;
                params23.grainSize = 6.0f;
                params23.roughness = 6.0f;
                params23.colorVariation = 0.0f;
                params23.vignette = -30.0f;
                params23.midpoint = 15.0f;
                params23.clarity = -10.0f;
                params23.luma = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                params23.rgb = new float[]{0.0f, 0.0f, 255.0f, 255.0f};
                return params23;
            default:
                throw new IllegalArgumentException("Tone index");
        }
    }
}
