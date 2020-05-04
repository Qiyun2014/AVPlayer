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

typedef enum __AVPlayerStatus {
    none,
    prepare,
    stating,
    pausing,
    stop,
    playback
} PlayerStatus;

__const int THREAD_COUNT = 3;

namespace avplayer {

    class MediaManager : public MediaFormat_Desc {
    public:
        ~MediaManager() {
           for (auto & i : _pthread) {
               if (i != nullptr) {
                   pthread_detach(i);
               }
           }
           _mStatus = none;
        };

        virtual void start_decode(avplayer::MediaManager *m_class) { printf("父类声明 .. \n"); };
        virtual bool seekToTime(float) { return false; };
        virtual void play() {};
        virtual void pause() {};
        virtual void stop() {};

        /* 当前状态值记录 */
        PlayerStatus _mStatus = none;

        /* Demux线程，解码线程 */
        pthread_t  _pthread[THREAD_COUNT]{};

        /* 缓存队列 */
        mq::DataBufferQueue *bufferQueue{};

        /* 线程锁 */
        pthread_cond_t cv{};
        pthread_mutex_t mutex{};

        virtual void* start_decode_thread(void*) {
            printf("父类解码 ...");
            _mStatus = prepare;
            return nullptr;
        };
    };
}