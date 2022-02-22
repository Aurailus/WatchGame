package com.example.roguelike

import android.app.Activity
import android.os.Bundle
import com.example.roguelike.databinding.ActivityMainBinding

class MainActivity : Activity() {
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.text.text = nativeGetName()
    }

    external fun nativeGetName(): String

    companion object {
        init {
            System.loadLibrary("Roguelike")
        }
    }
}