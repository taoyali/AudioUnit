//
// Created by taoyali on 2023/5/14.
//

#ifndef AUDIOUNIT_AUDIO_COMMON_H
#define AUDIOUNIT_AUDIO_COMMON_H

#include <stdio.h>
#include <SLES/OpenSLES.h>

#define AUDIO_SAMPLE_CHANNELS 1

#define BUF_COUNT 16

#define SLASSERT(x)                   \
  do {                                \
    assert(SL_RESULT_SUCCESS == (x)); \
    (void)(x);                        \
  } while (0)


struct SampleFormat {
    uint32_t sampleRate_;
    uint32_t framesPerBuf_;
    uint16_t channels_;
    // 8bit, 16bit, 24bit ...
    uint16_t pcmFormat_;
    // Android extensions
    uint32_t representation;
};

typedef bool (*ENGINE_CALLBACK)(void* pCTX, uint32_t msg, void* pData);


#endif //AUDIOUNIT_AUDIO_COMMON_H
