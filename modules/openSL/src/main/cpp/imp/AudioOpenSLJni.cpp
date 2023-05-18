#include <stdio.h>
#include <string>
#include <iostream>

// OpenSL ES Android
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// Android JNI
#include <jni.h>

// software business developer
#include "../include/audio_common.h"
#include "../include/audio_buf_manager.h"
#include "../include/audio_effect.h"

#include "../include/Audio.h"
#include "../include/jni_interface.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLKotlin_00024Companion_printLog(JNIEnv *env, jobject thiz,
                                                              jstring name) {
    // TODO: implement printLog()
    std::cout << name << std::endl;
    return env->NewStringUTF("hello Kotlin Android");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_printLog(JNIEnv* env,
                                             jclass thiz,
                                             jstring name) {
    std::cout << "hello java native" << std::endl;
    return env->NewStringUTF("hello Java Android");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_initOpenSLEngine(JNIEnv *env, jclass clazz, jint sampleRate,
                                                     jint framesPerBuf, jlong delayInMs,
                                                     jfloat decay) {
    createOpenSLEngine(sampleRate, framesPerBuf, delayInMs, decay);
}

/**
 * 配置Audio
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_configAudio(JNIEnv *env, jclass clazz, jint delay,
                                                jfloat decay) {
    configAudio(delay, decay);
}


