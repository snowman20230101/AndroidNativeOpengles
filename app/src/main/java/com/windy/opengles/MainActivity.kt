package com.windy.opengles

import android.os.Bundle
import android.view.ViewGroup
import android.widget.RelativeLayout
import androidx.appcompat.app.AppCompatActivity
import com.windy.opengles.databinding.ActivityMainBinding
import com.windy.opengles.render.GLCustomSurfaceView
import com.windy.opengles.render.GlCustomRender

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private val render = GlCustomRender()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
//        binding.sampleText.text = stringFromJNI()

        render.init()
        val glView = GLCustomSurfaceView(this, render)
        val lp = RelativeLayout.LayoutParams(
            ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT
        )
        lp.addRule(RelativeLayout.CENTER_IN_PARENT)
        binding.root.addView(glView, lp)
    }

    override fun onDestroy() {
        super.onDestroy()
        render.unInit()
    }

    /**
     * A native method that is implemented by the 'opengles' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'opengles' library on application startup.
        init {
            System.loadLibrary("native-opengles")
        }
    }
}