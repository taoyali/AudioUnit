package com.tyl.opensl;

public class AudioOpenSLJava {
    public static native String printLog(String name);

    public static native void initOpenSLEngine(int sampleRate, int framesPerBuf, long delayInMs, float decay);

    static {
        System.loadLibrary("AudioOpenSL");
    }
}
