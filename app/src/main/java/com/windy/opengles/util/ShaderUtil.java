package com.windy.opengles.util;

import android.annotation.SuppressLint;
import android.content.Context;

import com.windy.opengles.R;

public class ShaderUtil {

    @SuppressLint("StaticFieldLeak")
    private static Context context;

    public static void setContext(Context context) {
        ShaderUtil.context = context;
    }

    public static String getShaderStr(int shaderResId) {
        return Utils.readRawTextFile(context, shaderResId);
    }

    public static String getTriangleVertSrr() {
        return getShaderStr(R.raw.triangle_vertex);
    }
}
