//
// Created by qiyun on 2020/4/24.
//

#include "DataBufferQueue.h"

namespace mq {

    void DataBufferQueue::insert(AVPacket *pkt, AVMediaType type) {
        pthread_mutex_lock(&mutex);

        auto *node = static_cast<AVNode *>(malloc(sizeof(AVNode)));
        node->pkt = *pkt;
        node->type = type;
        node->next = nullptr;
        AVNode *lastNode = last_node();
        node->idx = lastNode->idx + 1;
        lastNode->next = node;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    bool DataBufferQueue::put(AVPacket *out_pkt, AVMediaType *out_type) {
        bool success = true;
        pthread_mutex_lock(&mutex);
        if (header_->next) {
            AVNode *nexNode = header_->next;
            *out_pkt = nexNode->pkt;
            *out_type = nexNode->type;
            if (nexNode->type == AVMEDIA_TYPE_AUDIO) {
                a_samples --;
            } else if (nexNode->type == AVMEDIA_TYPE_VIDEO) {
                v_samples --;
            }
            header_->next = nexNode->next;
            delete nexNode;
        } else {
            *out_pkt = {nullptr};
            *out_type = AVMEDIA_TYPE_UNKNOWN;
            success = false;
        }
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        return success;
    }

    AVNode* DataBufferQueue::last_node() {
        if (header_ == nullptr) {
            return nullptr;
        }
        a_samples = v_samples = 0;
        AVNode *node = header_;
        while (node->next != nullptr) {
            node = node->next;
            if (node->type == AVMEDIA_TYPE_AUDIO) {
                a_samples ++;
            } else if (node->type == AVMEDIA_TYPE_VIDEO) {
                v_samples ++;
            }
        }
        return node;
    }
}