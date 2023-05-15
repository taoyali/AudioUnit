//
// Created by taoyali on 2023/5/18.
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <jni.h>

#ifndef AUDIOUNIT_AUDIO_H
#define AUDIOUNIT_AUDIO_H

// OpenSL ES Android
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// software business developer
#include "../include/audio_common.h"
#include "../include/audio_buf_manager.h"
#include "../include/audio_effect.h"

void createOpenSLEngine(int sampleRate, int framesPerBuf, long delayInMs, float decay);

struct AudioEngine {
    SLmilliHertz fastPathSampleRate_;
    uint32_t fastPathFramesPerBuf_;
    uint16_t sampleChannels_;
    uint16_t bitsPerSample_;

    SLObjectItf slEngineObj_;
    SLEngineItf slENgineItf_;
    uint32_t bufCount_;
    sample_buf *bufs_;
    AudioQueue *freeBufQueue_;
    AudioQueue *recBufQueue_;
    int64_t echoDelay_;
    float echoDecay_;
    AudioDelay *delayEffect_;
};

#endif //AUDIOUNIT_AUDIO_H
