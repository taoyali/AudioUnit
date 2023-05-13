package com.tyl.opensl;

public class AudioOpenSLJava {
    public static native String printLog(String name);

    static {
        System.loadLibrary("AudioOpenSL");
    }
}
