package com.tyl.opensl

public class AudioOpenSLKotlin {

    companion object {
        init {
            System.loadLibrary("AudioOpenSL")
        }

        open external fun printLog(name: String) : String
    }
}