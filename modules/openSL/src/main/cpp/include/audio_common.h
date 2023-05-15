//
// Created by taoyali on 2023/5/14.
//

#ifndef AUDIOUNIT_AUDIO_COMMON_H
#define AUDIOUNIT_AUDIO_COMMON_H

#include <SLES/OpenSLES.h>

#define AUDIO_SAMPLE_CHANNELS 1

#define BUF_COUNT 16

#define SLASSERT(x)                   \
  do {                                \
    assert(SL_RESULT_SUCCESS == (x)); \
    (void)(x);                        \
  } while (0)

#endif //AUDIOUNIT_AUDIO_COMMON_H
