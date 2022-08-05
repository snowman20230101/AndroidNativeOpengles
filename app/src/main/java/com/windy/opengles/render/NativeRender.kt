package com.windy.opengles.render

class NativeRender {
    external fun native_init()

    external fun native_unInit()

    external fun native_onSurfaceCreated()

    external fun native_onSurfaceChanged(width: Int, height: Int)

    external fun native_onDrawFrame()

    external fun native_setImageData(format: Int, width: Int, height: Int, bytes: ByteArray?)

    external fun native_setImageDataWithIndex(
        index: Int,
        format: Int,
        width: Int,
        height: Int,
        bytes: ByteArray?
    )

    external fun native_setParamsFloat(paramType: Int, value0: Float, value1: Float)

    external fun native_setParamsInt(paramType: Int, value0: Int, value1: Int)

    external fun native_setAudioData(audioData: ShortArray?)

    external fun native_updateTransformMatrix(
        rotateX: Float,
        rotateY: Float,
        scaleX: Float,
        scaleY: Float
    )
}