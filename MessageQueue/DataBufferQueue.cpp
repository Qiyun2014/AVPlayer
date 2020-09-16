//
// Created by qiyun on 2020/4/24.
//

#include "DataBufferQueue.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavresample/avresample.h>
}

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
        if (_header->next) {
            AVNode *nexNode = _header->next;
            *out_pkt = nexNode->pkt;
            *out_type = nexNode->type;
            if (nexNode->type == AVMEDIA_TYPE_AUDIO) {
                a_samples --;
            } else if (nexNode->type == AVMEDIA_TYPE_VIDEO) {
                v_samples --;
            }
            _header->next = nexNode->next;
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
        if (_header == nullptr) {
            return nullptr;
        }
        a_samples = v_samples = 0;
        AVNode *node = _header;
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

    void DataBufferQueue::clear() {
        if (_header == nullptr) return;
        while (_header->next != nullptr) {
            if (_header->pkt.size > 0) {
                _header->idx = 0;
                _header->type = AVMEDIA_TYPE_UNKNOWN;
//                av_packet_unref(&(_header->pkt));
                _header = _header->next;
            }
        }
    }
}