package com.windy.opengles

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.content.res.AssetManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import android.view.ViewGroup
import android.widget.RelativeLayout
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.windy.opengles.databinding.ActivityMainBinding
import com.windy.opengles.render.GLCustomSurfaceView
import com.windy.opengles.render.GLCustomSurfaceView.Companion.IMAGE_FORMAT_RGBA
import com.windy.opengles.render.GlCustomRender
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_KEY_AVATAR
import com.windy.opengles.render.GlCustomRender.Companion.SAMPLE_TYPE_KEY_BEATING_HEART
import com.windy.opengles.util.ShaderUtil
import java.io.IOException
import java.nio.ByteBuffer

class MainActivity : AppCompatActivity(), SensorEventListener {
    private val REQUEST_PERMISSIONS = arrayOf(
        Manifest.permission.WRITE_EXTERNAL_STORAGE,
        Manifest.permission.RECORD_AUDIO
    )
    private val PERMISSION_REQUEST_CODE = 1


    private lateinit var binding: ActivityMainBinding
    private val render = GlCustomRender()

    private val mSampleSelectedIndex: Int = SAMPLE_TYPE_KEY_BEATING_HEART - SAMPLE_TYPE
    private var mSensorManager: SensorManager? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        ShaderUtil.setContext(this);
        nativeSetContext(this, assets)
        mSensorManager = getSystemService(SENSOR_SERVICE) as SensorManager

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        render.init()
        val glView = GLCustomSurfaceView(this, render)
        val lp = RelativeLayout.LayoutParams(
            ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT
        )
        lp.addRule(RelativeLayout.CENTER_IN_PARENT)
        binding.root.addView(glView, lp)
        glView.renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY

        loadRGBAImage(R.drawable.noise)
    }

    override fun onResume() {
        super.onResume()
        mSensorManager!!.registerListener(
            this,
            mSensorManager!!.getDefaultSensor(Sensor.TYPE_GRAVITY),
            SensorManager.SENSOR_DELAY_FASTEST
        )

        if (!hasPermissionsGranted(REQUEST_PERMISSIONS)) {
            ActivityCompat.requestPermissions(
                this,
                REQUEST_PERMISSIONS,
                PERMISSION_REQUEST_CODE
            )
        }
    }

    override fun onPause() {
        super.onPause()
        mSensorManager!!.unregisterListener(this)
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
        init {
            System.loadLibrary("native-opengles")
        }
    }

    override fun onSensorChanged(event: SensorEvent?) {
        when (event!!.sensor.type) {
            Sensor.TYPE_GRAVITY -> {
                Log.i(
                    "MainActivity",
                    "onSensorChanged() called with TYPE_GRAVITY: [x,y,z] = [" + event.values[0] + ", " + event.values[1] + ", " + event.values[2] + "]"
                )
                if (mSampleSelectedIndex + SAMPLE_TYPE === SAMPLE_TYPE_KEY_AVATAR) {
                    render.setGravityXY(event.values[0], event.values[1])
                }
            }
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {

    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String?>,
        grantResults: IntArray
    ) {
        if (requestCode == PERMISSION_REQUEST_CODE) {
            if (!hasPermissionsGranted(REQUEST_PERMISSIONS)) {
                Toast.makeText(
                    this,
                    "We need the permission: WRITE_EXTERNAL_STORAGE",
                    Toast.LENGTH_SHORT
                ).show()
            }
        } else {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        }
    }

    private fun hasPermissionsGranted(permissions: Array<String>): Boolean {
        for (permission in permissions) {
            if (ActivityCompat.checkSelfPermission(this, permission!!)
                != PackageManager.PERMISSION_GRANTED
            ) {
                return false
            }
        }
        return true
    }
}