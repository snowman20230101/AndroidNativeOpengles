package com.windy.opengles.render

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GlCustomRender constructor() : GLSurfaceView.Renderer {

    private var nativeRender: NativeRender = NativeRender()

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        nativeRender.native_onSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        nativeRender.native_onSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        nativeRender.native_onDrawFrame()
    }

    fun init() {
        nativeRender.native_init()
    }

    fun unInit() {
        nativeRender.native_unInit()
    }

    fun setImageData(format: Int, width: Int, height: Int, bytes: ByteArray?) {
        nativeRender.native_setImageData(format, width, height, bytes)
    }

    fun setImageDataWithIndex(index: Int, format: Int, width: Int, height: Int, bytes: ByteArray?) {
        nativeRender.native_setImageDataWithIndex(index, format, width, height, bytes)
    }
}