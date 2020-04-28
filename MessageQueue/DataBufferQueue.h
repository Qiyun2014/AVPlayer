//
// Created by qiyun on 2020/4/24.
//

#ifndef AVPLAYER_DATABUFFERQUEUE_H
#define AVPLAYER_DATABUFFERQUEUE_H

#include <pthread.h>
#include <libavcodec/avcodec.h>

namespace mq {
    typedef struct __AVNode {
        int idx;
        AVPacket pkt;
        AVMediaType type;
        __AVNode* next;
    } AVNode;

    class DataBufferQueue {
    public:
        DataBufferQueue() {
            if (mutex.__sig == 0 && cond.__sig == 0) {
                pthread_mutex_init(&mutex, nullptr);
                pthread_cond_init(&cond, nullptr);
                header_ = static_cast<AVNode *>(malloc(sizeof(AVNode)));
                header_->idx = 0;
                header_->pkt = {};
                header_->type = AVMEDIA_TYPE_UNKNOWN;
                header_->next = nullptr;
            }
        }
        ~DataBufferQueue() {
            pthread_mutex_destroy(&mutex);
            pthread_cond_destroy(&cond);
            while (header_->next != nullptr) {
                if (header_->pkt.size > 0) {
                    header_->idx = 0;
                    header_->type = AVMEDIA_TYPE_UNKNOWN;
                    av_packet_unref(&header_->pkt);
                    header_ = header_->next;
                }
            }
            delete header_;
        }

    private:
        DataBufferQueue(__const DataBufferQueue &);
        AVNode    *header_{};

        // Mutex lock
        pthread_mutex_t mutex{};
        pthread_cond_t cond{};
    public:
        static DataBufferQueue & GetInstance() {
            static DataBufferQueue dataBufferQueueInstances;
            return dataBufferQueueInstances;
        }
        void insert(AVPacket *pkt, AVMediaType type);
        bool put(AVPacket *out_pkt, AVMediaType *out_type);
        AVNode* last_node();

        uint32_t a_samples = 0, v_samples = 0;
    };

}

#endif //AVPLAYER_DATABUFFERQUEUE_H
