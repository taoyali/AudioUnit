//
// Created by taoyali on 2023/5/14.
//

#ifndef AUDIOUNIT_AUDIO_BUF_MANAGER_H
#define AUDIOUNIT_AUDIO_BUF_MANAGER_H

#include <SLES/OpenSLES.h>
#include <sys/types.h>

#include <atomic>
#include <cassert>
#include <limits>
#include <memory>

#include "audio_debug.h"

#ifndef CACHE_ALIGN
#define CACHE_ALIGN 64
#endif

template<typename T>
class ProducerConsumerQueue {
public:
    explicit ProducerConsumerQueue(int size) : ProducerConsumerQueue(size, new T[size]) {}
    explicit ProducerConsumerQueue(int size, T* buffer) : size_(size), buffer_(buffer) {
        assert(size<std::numeric_limits<int>::max());
    }

    bool push(const T& item) {
        return push([&](T* ptr) -> bool  {
           *ptr = item;
            return true;
        });
    }

    template<typename F>
    bool push(const F& writer) {
        bool result = false;
        int readptr = read_.load(std::memory_order_acquire);
        int writeptr = write_.load(std::memory_order_relaxed);

        int space = size_ - (int)(writeptr - readptr);
        if (space >= 1) {
            result = true;
            if (writer(buffer_.get() + (writeptr % size_))) {
                ++writeptr;
                write_.store(writeptr, std::memory_order_release);
            }
        }
        return result;
    }

private:
    int size_;
    std::unique_ptr<T> buffer_;
    alignas(CACHE_ALIGN) std::atomic<int> read_{0};
    alignas(CACHE_ALIGN) std::atomic<int> write_{0};

};


struct sample_buf {
    uint8_t* buf_;
    uint32_t cap_;
    uint32_t size_;
};

using AudioQueue = ProducerConsumerQueue<sample_buf*>;

__inline__ void releaseSampleBufs(sample_buf* bufs, uint32_t& count) {
    if (!bufs || !count) {
        return;
    }
    for (uint32_t i = 0; i < count; ++i) {
        if (bufs[i].buf_) delete[] bufs[i].buf_;
    }
    delete[] bufs;
}

__inline__ sample_buf* allocateSampleBufs(uint32_t count, uint32_t sizeInByte) {

    LOGW("%s : count = %d, sizeInByte = %d", __FUNCTION__ , count, sizeInByte);

    if (count <= 0 || sizeInByte <= 0) {
        LOGW("%s : count = %d, sizeInByte = %d", __FUNCTION__, count, sizeInByte);
        return nullptr;
    }
    sample_buf* bufs = new sample_buf[count];
    assert(bufs);
    memset(bufs, 0, sizeof(sample_buf) * count);

    uint32_t allocSize = (sizeInByte + 3) & ~3; // padding to 4 bytes aligned
    uint32_t i;
    for (i = 0; i < count; ++i) {
        bufs[i].buf_ = new uint8_t[allocSize];
        if (bufs[i].buf_ == nullptr) {
            LOGW("====Requesting %d buffers, allocated %d in %s", count, i,
                 __FUNCTION__);
            break;
        }
        bufs[i].cap_ = sizeInByte;
        bufs[i].size_ = 0;
    }
    if (i < 2) {
        releaseSampleBufs(bufs, i);
        bufs = nullptr;
    }
    count = i;
    return bufs;
}

#endif //AUDIOUNIT_AUDIO_BUF_MANAGER_H
