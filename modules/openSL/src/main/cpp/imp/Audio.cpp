
#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/types.h>

// OpenSL ES Android
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// software business developer
#include "../include/audio_common.h"
#include "../include/audio_buf_manager.h"
#include "../include/audio_effect.h"
#include "../include/Audio.h"

using namespace std;

static AudioEngine engine;

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
