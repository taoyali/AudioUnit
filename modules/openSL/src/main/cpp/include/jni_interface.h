//
// Created by taoyali on 2023/5/18.
//

#ifndef AUDIOUNIT_JNI_INTERFACE_H
#define AUDIOUNIT_JNI_INTERFACE_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLKotlin_00024Companion_printLog(JNIEnv *env, jobject thiz, jstring name);

JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_printLog(JNIEnv* env, jclass thiz, jstring name);

JNIEXPORT void JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_initOpenSLEngine(JNIEnv *env, jclass clazz, jint sampleRate,
                                                     jint framesPerBuf, jlong delayInMs,
                                                     jfloat decay);

JNIEXPORT void JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_configAudio(JNIEnv *env, jclass clazz, jint delay,
                                                jfloat decay);

#ifdef __cplusplus
}
#endif


#endif //AUDIOUNIT_JNI_INTERFACE_H
