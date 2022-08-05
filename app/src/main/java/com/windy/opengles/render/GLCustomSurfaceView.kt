package com.windy.opengles.render

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import android.view.MotionEvent
import android.view.ScaleGestureDetector
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_3D_MODEL
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_BASIC_LIGHTING
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_COORD_SYSTEM
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_DEPTH_TESTING
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_FBO_LEG
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_INSTANCING
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_KEY_SCRATCH_CARD
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_KEY_SHOCK_WAVE
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_KEY_TEXT_RENDER
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_KEY_UBO
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_KEY_VISUALIZE_AUDIO
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_MULTI_LIGHTS
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_PARTICLES
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_PBO
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_SKYBOX
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_STENCIL_TESTING
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_TRANS_FEEDBACK

class GLCustomSurfaceView(
    context: Context,
    attrs: AttributeSet?,
    private val render: GlCustomRender
) :
    GLSurfaceView(context, attrs), ScaleGestureDetector.OnScaleGestureListener {

    private var mScaleGestureDetector: ScaleGestureDetector? = null

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

        mScaleGestureDetector = ScaleGestureDetector(context, this)
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

    private var mPreScale = 1.0f
    private var mCurScale = 1.0f

    private var mXAngle = 0.0f
    private var mYAngle = 0.0f

    override fun onScale(detector: ScaleGestureDetector?): Boolean {
        when (render.getSampleType()) {
            SAMPLE_TYPE_COORD_SYSTEM,
            SAMPLE_TYPE_BASIC_LIGHTING,
            SAMPLE_TYPE_INSTANCING,
            SAMPLE_TYPE_3D_MODEL,
            SAMPLE_TYPE_KEY_VISUALIZE_AUDIO,
            SAMPLE_TYPE_KEY_TEXT_RENDER -> {
                val preSpan = detector!!.previousSpan
                val curSpan = detector.currentSpan
                mCurScale = if (curSpan < preSpan) {
                    mPreScale - (preSpan - curSpan) / 200
                } else {
                    mPreScale + (curSpan - preSpan) / 200
                }
                mCurScale = Math.max(0.05f, Math.min(mCurScale, 80.0f))
                render.updateTransformMatrix(mXAngle, mYAngle, mCurScale, mCurScale)
                requestRender()
            }
            else -> {}
        }

        return false
    }

    override fun onScaleBegin(detector: ScaleGestureDetector?): Boolean {
        return true
    }

    override fun onScaleEnd(detector: ScaleGestureDetector?) {
        mPreScale = mCurScale
        mLastMultiTouchTime = System.currentTimeMillis()
    }

    private var mLastMultiTouchTime: Long = 0
    private var mPreviousY = 0f
    private var mPreviousX = 0f

    override fun onTouchEvent(e: MotionEvent): Boolean {
        if (e.pointerCount == 1) {
            consumeTouchEvent(e)
            val currentTimeMillis = System.currentTimeMillis()
            if (currentTimeMillis - mLastMultiTouchTime > 200) {
                val y = e.y
                val x = e.x
                when (e.action) {
                    MotionEvent.ACTION_MOVE -> {
                        val dy: Float = y - mPreviousY
                        val dx: Float = x - mPreviousX
                        mYAngle += (dx * TOUCH_SCALE_FACTOR).toInt()
                        mXAngle += (dy * TOUCH_SCALE_FACTOR).toInt()
                    }
                }
                mPreviousY = y
                mPreviousX = x
                when (render.getSampleType()) {
                    SAMPLE_TYPE_FBO_LEG, SAMPLE_TYPE_COORD_SYSTEM,
                    SAMPLE_TYPE_BASIC_LIGHTING,
                    SAMPLE_TYPE_TRANS_FEEDBACK,
                    SAMPLE_TYPE_MULTI_LIGHTS,
                    SAMPLE_TYPE_DEPTH_TESTING,
                    SAMPLE_TYPE_INSTANCING,
                    SAMPLE_TYPE_STENCIL_TESTING,
                    SAMPLE_TYPE_PARTICLES,
                    SAMPLE_TYPE_SKYBOX,
                    SAMPLE_TYPE_3D_MODEL,
                    SAMPLE_TYPE_PBO,
                    SAMPLE_TYPE_KEY_VISUALIZE_AUDIO,
                    SAMPLE_TYPE_KEY_UBO,
                    SAMPLE_TYPE_KEY_TEXT_RENDER -> {
                        render.updateTransformMatrix(mXAngle, mYAngle, mCurScale, mCurScale)
                        requestRender()
                    }
                    else -> {}
                }
            }
        } else {
            mScaleGestureDetector!!.onTouchEvent(e)
        }
        return true
    }

    private fun consumeTouchEvent(e: MotionEvent) {
        dealClickEvent(e)
        var touchX = -1f
        var touchY = -1f
        when (e.action) {
            MotionEvent.ACTION_MOVE -> {
                touchX = e.x
                touchY = e.y
            }
            MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                touchX = -1f
                touchY = -1f
            }
            else -> {}
        }
        when (render.getSampleType()) {
            SAMPLE_TYPE_KEY_SCRATCH_CARD -> {
                render.setTouchLoc(touchX, touchY)
                requestRender()
            }
            else -> {}
        }
        when (e.action) {
            MotionEvent.ACTION_MOVE -> {}
            MotionEvent.ACTION_UP -> {}
            MotionEvent.ACTION_CANCEL -> {}
            else -> {}
        }
    }

    private fun dealClickEvent(e: MotionEvent) {
        var touchX = -1f
        var touchY = -1f
        when (e.action) {
            MotionEvent.ACTION_UP -> {
                touchX = e.x
                touchY = e.y
                run {
                    when (render.getSampleType()) {
                        SAMPLE_TYPE_KEY_SHOCK_WAVE -> render.setTouchLoc(touchX, touchY)
                        else -> {}
                    }
                }
            }
            else -> {}
        }
    }

    private var mRatioWidth = 0
    private var mRatioHeight = 0

    override fun onMeasure(widthMeasureSpec: Int, heightMeasureSpec: Int) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec)
        val width = MeasureSpec.getSize(widthMeasureSpec)
        val height = MeasureSpec.getSize(heightMeasureSpec)
        if (0 == mRatioWidth || 0 == mRatioHeight) {
            setMeasuredDimension(width, height)
        } else {
            if (width < height * mRatioWidth / mRatioHeight) {
                setMeasuredDimension(width, width * mRatioHeight / mRatioWidth)
            } else {
                setMeasuredDimension(height * mRatioWidth / mRatioHeight, height)
            }
        }
    }

    fun setAspectRatio(width: Int, height: Int) {
        Log.d(
            "GLCustomSurfaceView",
            "setAspectRatio() called with: width = [$width], height = [$height]"
        )
        require(!(width < 0 || height < 0)) { "Size cannot be negative." }
        mRatioWidth = width
        mRatioHeight = height
        requestLayout()
    }
}