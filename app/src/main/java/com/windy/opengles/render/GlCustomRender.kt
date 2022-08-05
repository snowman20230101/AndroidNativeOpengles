package com.windy.opengles.render

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GlCustomRender constructor() : GLSurfaceView.Renderer {

    private var nativeRender: NativeRender = NativeRender()
    private var sampleType = 0

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

    fun setGravityXY(x: Float, y: Float) {
        nativeRender.native_setParamsFloat(SAMPLE_TYPE_SET_GRAVITY_XY, x, y)
    }

    fun setTouchLoc(x: Float, y: Float) {
        nativeRender.native_setParamsFloat(SAMPLE_TYPE_SET_TOUCH_LOC, x, y)
    }

    fun setParamsInt(paramType: Int, value0: Int, value1: Int) {
        if (paramType == SAMPLE_TYPE) {
            sampleType = value0
        }
        nativeRender.native_setParamsInt(paramType, value0, value1)
    }

    fun updateTransformMatrix(rotateX: Float, rotateY: Float, scaleX: Float, scaleY: Float) {
        nativeRender.native_updateTransformMatrix(rotateX, rotateY, scaleX, scaleY)
    }

    fun getSampleType(): Int {
        return sampleType
    }

    companion object {
        const val SAMPLE_TYPE = 200

        const val SAMPLE_TYPE_TRIANGLE = SAMPLE_TYPE
        const val SAMPLE_TYPE_TEXTURE_MAP = SAMPLE_TYPE + 1
        const val SAMPLE_TYPE_YUV_TEXTURE_MAP = SAMPLE_TYPE + 2
        const val SAMPLE_TYPE_VAO = SAMPLE_TYPE + 3
        const val SAMPLE_TYPE_FBO = SAMPLE_TYPE + 4
        const val SAMPLE_TYPE_EGL = SAMPLE_TYPE + 5
        const val SAMPLE_TYPE_FBO_LEG = SAMPLE_TYPE + 6
        const val SAMPLE_TYPE_COORD_SYSTEM = SAMPLE_TYPE + 7
        const val SAMPLE_TYPE_BASIC_LIGHTING = SAMPLE_TYPE + 8
        const val SAMPLE_TYPE_TRANS_FEEDBACK = SAMPLE_TYPE + 9
        const val SAMPLE_TYPE_MULTI_LIGHTS = SAMPLE_TYPE + 10
        const val SAMPLE_TYPE_DEPTH_TESTING = SAMPLE_TYPE + 11
        const val SAMPLE_TYPE_INSTANCING = SAMPLE_TYPE + 12
        const val SAMPLE_TYPE_STENCIL_TESTING = SAMPLE_TYPE + 13
        const val SAMPLE_TYPE_BLENDING = SAMPLE_TYPE + 14
        const val SAMPLE_TYPE_PARTICLES = SAMPLE_TYPE + 15
        const val SAMPLE_TYPE_SKYBOX = SAMPLE_TYPE + 16
        const val SAMPLE_TYPE_3D_MODEL = SAMPLE_TYPE + 17
        const val SAMPLE_TYPE_PBO = SAMPLE_TYPE + 18
        const val SAMPLE_TYPE_KEY_BEATING_HEART = SAMPLE_TYPE + 19
        const val SAMPLE_TYPE_KEY_CLOUD = SAMPLE_TYPE + 20
        const val SAMPLE_TYPE_KEY_TIME_TUNNEL = SAMPLE_TYPE + 21
        const val SAMPLE_TYPE_KEY_BEZIER_CURVE = SAMPLE_TYPE + 22
        const val SAMPLE_TYPE_KEY_BIG_EYES = SAMPLE_TYPE + 23
        const val SAMPLE_TYPE_KEY_FACE_SLENDER = SAMPLE_TYPE + 24
        const val SAMPLE_TYPE_KEY_BIG_HEAD = SAMPLE_TYPE + 25
        const val SAMPLE_TYPE_KEY_ROTARY_HEAD = SAMPLE_TYPE + 26
        const val SAMPLE_TYPE_KEY_VISUALIZE_AUDIO = SAMPLE_TYPE + 27
        const val SAMPLE_TYPE_KEY_SCRATCH_CARD = SAMPLE_TYPE + 28
        const val SAMPLE_TYPE_KEY_AVATAR = SAMPLE_TYPE + 29
        const val SAMPLE_TYPE_KEY_SHOCK_WAVE = SAMPLE_TYPE + 30
        const val SAMPLE_TYPE_KEY_MRT = SAMPLE_TYPE + 31
        const val SAMPLE_TYPE_KEY_FBO_BLIT = SAMPLE_TYPE + 32
        const val SAMPLE_TYPE_KEY_TBO = SAMPLE_TYPE + 33
        const val SAMPLE_TYPE_KEY_UBO = SAMPLE_TYPE + 34
        const val SAMPLE_TYPE_KEY_RGB2YUYV = SAMPLE_TYPE + 35
        const val SAMPLE_TYPE_KEY_MULTI_THREAD_RENDER = SAMPLE_TYPE + 36
        const val SAMPLE_TYPE_KEY_TEXT_RENDER = SAMPLE_TYPE + 37
        const val SAMPLE_TYPE_KEY_STAY_COLOR = SAMPLE_TYPE + 38
        const val SAMPLE_TYPE_KEY_TRANSITIONS_1 = SAMPLE_TYPE + 39
        const val SAMPLE_TYPE_KEY_TRANSITIONS_2 = SAMPLE_TYPE + 40
        const val SAMPLE_TYPE_KEY_TRANSITIONS_3 = SAMPLE_TYPE + 41
        const val SAMPLE_TYPE_KEY_TRANSITIONS_4 = SAMPLE_TYPE + 42
        const val SAMPLE_TYPE_KEY_RGB2NV21 = SAMPLE_TYPE + 43
        const val SAMPLE_TYPE_KEY_RGB2I420 = SAMPLE_TYPE + 44
        const val SAMPLE_TYPE_KEY_RGB2I444 = SAMPLE_TYPE + 45
        const val SAMPLE_TYPE_KEY_COPY_TEXTURE = SAMPLE_TYPE + 46
        const val SAMPLE_TYPE_KEY_BLIT_FRAME_BUFFER = SAMPLE_TYPE + 47
        const val SAMPLE_TYPE_KEY_BINARY_PROGRAM = SAMPLE_TYPE + 48

        const val SAMPLE_TYPE_KEY_HWBuffer = SAMPLE_TYPE + 50

        const val SAMPLE_TYPE_SET_TOUCH_LOC = SAMPLE_TYPE + 999
        const val SAMPLE_TYPE_SET_GRAVITY_XY = SAMPLE_TYPE + 1000
    }
}