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
//        renderMode = RENDERMODE_WHEN_DIRTY
        renderMode = RENDERMODE_CONTINUOUSLY
    }

    companion object {
        private const val TOUCH_SCALE_FACTOR = 180.0f / 320

        const val IMAGE_FORMAT_RGBA = 0x01
        const val IMAGE_FORMAT_NV21 = 0x02
        const val IMAGE_FORMAT_NV12 = 0x03
        const val IMAGE_FORMAT_I420 = 0x04
        const val IMAGE_FORMAT_YUYV = 0x05
        const val IMAGE_FORMAT_GARY = 0x06

    }
}