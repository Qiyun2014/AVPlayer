//
// Created by qiyun on 2020/4/24.
//

#ifndef AVPLAYER_FF_MEDIAFORMAT_H
#define AVPLAYER_FF_MEDIAFORMAT_H

#endif //AVPLAYER_FF_MEDIAFORMAT_H



#include <thread>
#include "MediaFormat_Desc.h"
#include "../MessageQueue/DataBufferQueue.h"
#include <chrono>
#include <future>

namespace avplayer {

    class MediaManager : public MediaFormat_Desc {
    public:
        virtual void start_decode(avplayer::MediaManager *m_class) { printf("父类声明 .. \n"); };
        virtual bool seekToTime(float) { return false; };
        virtual void play() {};
        virtual void pause() {};
        virtual void stop() {};

        bool isPause{};
        bool isPlaying{};

        /* Demux线程，解码线程 */
        pthread_t  pthread_[3]{};

        /* 缓存队列 */
        mq::DataBufferQueue *bufferQueue;

        /* 线程锁 */
        pthread_cond_t cv{};
        pthread_mutex_t mutex{};

        //std::future<void *> demux_thread;
        //std::future<void *> decode_thread;

        virtual void* start_decode_thread(void*) {
            printf("父类解码 ...");
            return nullptr;
        };
    };
}