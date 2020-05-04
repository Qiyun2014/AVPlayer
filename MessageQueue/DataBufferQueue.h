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
                _header = static_cast<AVNode *>(malloc(sizeof(AVNode)));
                _header->idx = 0;
                _header->pkt = {};
                _header->type = AVMEDIA_TYPE_UNKNOWN;
                _header->next = nullptr;
            }
        }
        ~DataBufferQueue() {
            pthread_mutex_destroy(&mutex);
            pthread_cond_destroy(&cond);
            clear();
            delete _header;
        }

    private:
        DataBufferQueue(__const DataBufferQueue &);
        AVNode    *_header{};
        // Mutex lock
        pthread_mutex_t mutex{};
        pthread_cond_t cond{};
        AVNode* last_node();
    public:
        static DataBufferQueue & GetInstance() {
            static DataBufferQueue dataBufferQueueInstances;
            return dataBufferQueueInstances;
        }
        // 填充新的packet数据到链表
        void insert(AVPacket *pkt, AVMediaType type);
        // 获取头节点后的第一个packet数据包
        bool put(AVPacket *out_pkt, AVMediaType *out_type);
        // 清理缓存数据
        void clear();
        // 当前链表中，音视频数据包的存储数量
        uint32_t a_samples = 0, v_samples = 0;
    };

}

#endif //AVPLAYER_DATABUFFERQUEUE_H
