#include <stdio.h>
#include <string>
#include <iostream>
#include <jni.h>

#include "../include/jni_interface.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLKotlin_00024Companion_printLog(JNIEnv *env, jobject thiz,
                                                              jstring name) {
    // TODO: implement printLog()
    std::cout << name << std::endl;
    return env->NewStringUTF("hello Kotlin Android");
}

JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_printLog(JNIEnv* env,
                                             jclass thiz,
                                             jstring name) {
    std::cout << "hello java native" << std::endl;
    return env->NewStringUTF("hello Java Android");
}