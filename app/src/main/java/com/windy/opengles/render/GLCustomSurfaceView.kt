package com.windy.opengles.render

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log

class GLCustomSurfaceView(
    context: Context,
    attrs: AttributeSet?,
    private val render: GlCustomRender
) :
    GLSurfaceView(context, attrs) {

    constructor(context: Context, render: GlCustomRender) : this(context, null, render) {
        setEGLContextClientVersion(3)
        Log.d("GLCustomSurfaceView", "GLCustomSurfaceView()")
        /*If no setEGLConfigChooser method is called,
        then by default the view will choose an RGB_888 surface with a depth buffer depth of at least 16 bits.*/
        /*If no setEGLConfigChooser method is called,
        then by default the view will choose an RGB_888 surface with a depth buffer depth of at least 16 bits.*/
        setEGLConfigChooser(
            8,
            8,
            8,
            8,
            16,
            8
        )
        setRenderer(render)
        // 设置按需渲染 当我们调用 requestRender 请求GLThread 回调一次 onDrawFrame
        // 连续渲染 就是自动的回调onDrawFrame
        renderMode = RENDERMODE_WHEN_DIRTY
    }
}