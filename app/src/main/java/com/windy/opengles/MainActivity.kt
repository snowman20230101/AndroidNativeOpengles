package com.windy.opengles

import android.content.Context
import android.content.res.AssetManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Bundle
import android.view.ViewGroup
import android.widget.RelativeLayout
import androidx.appcompat.app.AppCompatActivity
import com.windy.opengles.databinding.ActivityMainBinding
import com.windy.opengles.render.GLCustomSurfaceView
import com.windy.opengles.render.GLCustomSurfaceView.Companion.IMAGE_FORMAT_RGBA
import com.windy.opengles.render.GlCustomRender
import com.windy.opengles.util.ShaderUtil
import java.io.IOException
import java.nio.ByteBuffer

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private val render = GlCustomRender()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        ShaderUtil.setContext(this);
        nativeSetContext(this, assets)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        render.init()
        val glView = GLCustomSurfaceView(this, render)
        val lp = RelativeLayout.LayoutParams(
            ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT
        )
        lp.addRule(RelativeLayout.CENTER_IN_PARENT)
        binding.root.addView(glView, lp)

//        loadRGBAImage(R.drawable.noise)
    }

    override fun onDestroy() {
        super.onDestroy()
        render.unInit()
    }

    private fun loadRGBAImage(resId: Int): Bitmap? {
        val inputStream = this.resources.openRawResource(resId)
        val bitmap: Bitmap?
        try {
            bitmap = BitmapFactory.decodeStream(inputStream)
            if (bitmap != null) {
                val bytes = bitmap.byteCount
                val buf = ByteBuffer.allocate(bytes)
                bitmap.copyPixelsToBuffer(buf)
                val byteArray = buf.array()
                render.setImageData(IMAGE_FORMAT_RGBA, bitmap.width, bitmap.height, byteArray)
            }
        } finally {
            try {
                inputStream.close()
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        return bitmap
    }

    external fun nativeSetContext(context: Context, assetManager: AssetManager)

    companion object {
        // Used to load the 'opengles' library on application startup.
        init {
            System.loadLibrary("native-opengles")
        }
    }
}