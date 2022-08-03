package com.windy.opengles.render

class NativeRender {
    external fun native_init()

    external fun native_unInit()

    external fun native_onSurfaceCreated()

    external fun native_onSurfaceChanged(width: Int, height: Int)

    external fun native_onDrawFrame()
}