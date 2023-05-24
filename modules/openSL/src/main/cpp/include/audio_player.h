//
// Created by taoyali on 2023/5/19.
//

#ifndef AUDIOUNIT_AUDIO_PLAYER_H
#define AUDIOUNIT_AUDIO_PLAYER_H

#include <sys/types.h>
#include <mutex>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "audio_common.h"
#include "audio_buf_manager.h"
#include "audio_debug_utils.h"

class AudioPlayerMe {
    // buffer queue player interfaces
    SLObjectItf outputMixObjectItf_;
    SLObjectItf playerObjectItf_;
    SLPlayItf playItf_;
    SLAndroidSimpleBufferQueueItf playBufferQueueItf_;

    SampleFormat sampleInfo_;
    AudioQueue *freeQueue_;       // user
    AudioQueue *playQueue_;       // user
    AudioQueue *devShadowQueue_;  // owner

    ENGINE_CALLBACK callback_;
    void *ctx_;
    sample_buf silentBuf_;
#ifdef ENABLE_LOG
    AndroidLog *logFile_;
#endif
    std::mutex stopMutex_;

public:
    explicit AudioPlayerMe(SampleFormat *sampleFormat, SLEngineItf engine);
    ~AudioPlayerMe();
    void SetBufQueue(AudioQueue *playQ, AudioQueue *freeQ);
    SLresult Start(void);
    void Stop(void);
    void ProcessSLCallback(SLAndroidSimpleBufferQueueItf bq);
    uint32_t dbgGetDevBufCount(void);
    void RegisterCallback(ENGINE_CALLBACK cb, void *ctx);
};


#endif //AUDIOUNIT_AUDIO_PLAYER_H
