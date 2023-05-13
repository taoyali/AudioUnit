//
// Created by taoyali on 2023/5/18.
//

#ifndef AUDIOUNIT_JNI_INTERFACE_H
#define AUDIOUNIT_JNI_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLKotlin_00024Companion_printLog(JNIEnv *env, jobject thiz, jstring name);

JNIEXPORT jstring JNICALL
Java_com_tyl_opensl_AudioOpenSLJava_printLog(JNIEnv* env, jclass thiz, jstring name);

#ifdef __cplusplus
};
#endif

#endif //AUDIOUNIT_JNI_INTERFACE_H