
#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <stdbool.h>

// OpenSL ES Android
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// JNI
#include <jni.h>

// software business developer
#include "../include/audio_common.h"
#include "../include/audio_buf_manager.h"
#include "../include/audio_effect.h"
#include "../include/Audio.h"

using namespace std;

static AudioEngine engine;

bool EngineService(void *ctx, uint32_t msg, void *data);

void createOpenSLEngine(int sampleRate, int framesPerBuf, long delayInMs, float decay) {

    SLresult lresult;
    memset(&engine, 0, sizeof(engine));

    engine.fastPathSampleRate_ = static_cast<SLmilliHertz>(sampleRate) * 1000;
    engine.fastPathFramesPerBuf_ = static_cast<uint32_t>(framesPerBuf);
    engine.sampleChannels_ = AUDIO_SAMPLE_CHANNELS;
    engine.bitsPerSample_ = SL_PCMSAMPLEFORMAT_FIXED_16;

    lresult = slCreateEngine(&engine.slEngineObj_, 0, NULL, 0, NULL, NULL);
    SLASSERT(lresult);

    lresult = (*engine.slEngineObj_)->Realize(engine.slEngineObj_, SL_BOOLEAN_FALSE);
    SLASSERT(lresult);

    lresult = (*engine.slEngineObj_)->GetInterface(engine.slEngineObj_, SL_IID_ENGINE, &engine.slENgineItf_);
    SLASSERT(lresult);

    uint32_t bufSize = engine.fastPathFramesPerBuf_ * engine.sampleChannels_ * engine.bitsPerSample_;
    bufSize = (bufSize + 7) >> 3; // bits --> byte
    engine.bufCount_ = BUF_COUNT;
    engine.bufs_ = allocateSampleBufs(engine.bufCount_, bufSize);

    assert(engine.bufs_);

    engine.freeBufQueue_ = new AudioQueue(engine.bufCount_);
    engine.recBufQueue_ = new AudioQueue (engine.bufCount_);
    assert(engine.freeBufQueue_ && engine.recBufQueue_);
    for (uint32_t i = 0; i < engine.bufCount_; ++i) {
        engine.freeBufQueue_->push(&engine.bufs_[i]);
    }

    engine.echoDelay_ = delayInMs;
    engine.echoDecay_ = decay;
    engine.delayEffect_ = new AudioDelay(
            engine.fastPathSampleRate_,
            engine.sampleChannels_,
            engine.bitsPerSample_,
            engine.echoDelay_,
            engine.echoDecay_);
    assert(engine.delayEffect_);
}

void configAudio(int delayInMs, float decay) {
    engine.echoDelay_ = delayInMs;
    engine.echoDecay_ = decay;

    engine.delayEffect_->setDelayTime(delayInMs);
    engine.delayEffect_->setDecayWeight(decay);
}


uint32_t dbgEngineGetBufCount(void) {
    uint32_t count = engine.player_->dbgGetDevBufCount();
    count += engine.recorder_->dbgGetDevBufCount();
    count += engine.freeBufQueue_->size();
    count += engine.recBufQueue_->size();

    LOGE(
            "Buf Disrtibutions: PlayerDev=%d, RecDev=%d, FreeQ=%d, "
            "RecQ=%d",
            engine.player_->dbgGetDevBufCount(),
            engine.recorder_->dbgGetDevBufCount(), engine.freeBufQueue_->size(),
            engine.recBufQueue_->size());
    if (count != engine.bufCount_) {
        LOGE("====Lost Bufs among the queue(supposed = %d, found = %d)", BUF_COUNT,
             count);
    }
    return count;
}


bool EngineService(void  *ctx, uint32_t msg, void *data) {
    assert(ctx == &engine);
    switch (msg) {
        case ENGINE_SERVICE_MSG_RETRIEVE_DUMP_BUFS: {
            *(static_cast<uint32_t *>(data)) == dbgEngineGetBufCount();
            break;
        }
        case ENGINE_SERVICE_MSG_RECORDED_AUDIO_AVAILABLE: {
            // adding audio delay effect
            sample_buf *buf = static_cast<sample_buf *>(data);
            assert(engine.fastPathFramesPerBuf_ ==
                   buf->size_ / engine.sampleChannels_ / (engine.bitsPerSample_ / 8));
            engine.delayEffect_->process(reinterpret_cast<int16_t *>(buf->buf_),
                                         engine.fastPathFramesPerBuf_);
            break;
        }
        default:
            assert(false);
            return false;
    }
}

bool createSLBufferQueueAudioPlayer() {
    SampleFormat sampleFormat;
    memset(&sampleFormat, 0, sizeof(sampleFormat));
    sampleFormat.pcmFormat_ = (uint16_t)engine.bitsPerSample_;
    sampleFormat.framesPerBuf_ = engine.fastPathFramesPerBuf_;

    sampleFormat.channels_ = (uint16_t)engine.sampleChannels_;
    sampleFormat.sampleRate_ = engine.fastPathSampleRate_;

    engine.player_ = new AudioPlayerMe(&sampleFormat, engine.slENgineItf_);
    assert(engine.player_);
    if (engine.player_ == nullptr) return false;

    engine.player_->SetBufQueue(engine.recBufQueue_, engine.freeBufQueue_);
    engine.player_->RegisterCallback(EngineService, (void *)&engine);

    return true;
}

