//
// Created by qiyun on 2020/4/27.
//

#include <zconf.h>
#include "MediaDecoder.h"
#include "../MessageQueue/DataBufferQueue.h"


bool is_decode_sucess (int val, MediaDecoder *mediaParser) {
    switch (val) {
        case AVERROR(EAGAIN):
            printf("************************ must try to send new input ... \n");
            break;
        case AVERROR_EOF:
            printf("************************ end of file ... \n");
            avcodec_flush_buffers(mediaParser->m_parse_class->v_codec_ctx_);
            avcodec_flush_buffers(mediaParser->m_parse_class->a_codec_ctx_);
            mediaParser->m_parse_class->is_completion_ = true;
            return false;
        case AVERROR(EINVAL):
            printf("************************ codec not opened ... \n");
            break;
        case AVERROR_INPUT_CHANGED:
            printf("************************ input changed ... \n");
            break;
        default:
            break;
    }
    return true;
}

void* MediaDecoder::decoder_thread(void *userdata) {
    auto *mediaParser = static_cast<MediaDecoder *>(userdata);
    AVPacket pkt, *packet = &pkt;
    int val = 0;
    AVMediaType mediaType = AVMEDIA_TYPE_UNKNOWN;

    while (!mediaParser->m_parse_class->is_completion_ || mediaParser->m_parse_class->bufferQueue->v_samples > 0) {
        pthread_mutex_lock(&mediaParser->m_parse_class->mutex);
        bool success = mediaParser->m_parse_class->bufferQueue->put(packet, &mediaType);
        if (mediaType == AVMEDIA_TYPE_UNKNOWN || !success) {
            printf("*********************  cache queue not data ..... \n");
            usleep(100 * 1000);
            pthread_mutex_unlock(&mediaParser->m_parse_class->mutex);
            continue;
        }
        // 从缓存队列拿取包数据
        AVCodecContext *codecContext = (mediaType == AVMEDIA_TYPE_VIDEO) ? mediaParser->m_parse_class->v_codec_ctx_ : mediaParser->m_parse_class->a_codec_ctx_;
        val = avcodec_send_packet(codecContext, packet);
        if (!is_decode_sucess(val, mediaParser)) {
            pthread_mutex_unlock(&mediaParser->m_parse_class->mutex);
            break;
        }
        while (avcodec_receive_frame(codecContext, mediaParser->out_frame) == 0) {
            /*  错误的pts重置数值
            if ((mediaParser->pts = mediaParser->out_frame->best_effort_timestamp) == AV_NOPTS_VALUE) {
                mediaParser->pts = 0;
            }
            */
            /* 帧类型，通常只有当存在B帧时，pts和dts就会不同。 */
            AVPictureType pic_type = mediaParser->out_frame->pict_type;
            /* 计算pts */
            if (mediaType == AVMEDIA_TYPE_VIDEO) {
                double frame_duration = mediaParser->m_parse_class->GetDurationPerFrame(AVMEDIA_TYPE_VIDEO);
                mediaParser->pts += frame_duration;
                printf("************************  解码成功, 解码视频帧 -->  %.2f, 帧类型 = %d ... \n", mediaParser->pts, pic_type);
            } else if (mediaType == AVMEDIA_TYPE_AUDIO) {
                printf("************************  解码成功, 解码音频帧 -->  %.2f ... \n", mediaParser->pts);
            }
        }
        av_packet_unref(packet);
        pthread_mutex_unlock(&mediaParser->m_parse_class->mutex);
    }
    printf("************************  解码完成. .. \n");
    delete mediaParser->m_parse_class;
    return nullptr;
}


MediaDecoder::MediaDecoder() {
    out_pkt = av_packet_alloc();
    out_frame = av_frame_alloc();
}

MediaDecoder::~MediaDecoder() {
    av_packet_free(&out_pkt);
    av_frame_free(&out_frame);
}

void MediaDecoder::start_decode(avplayer::MediaManager* m_class) {
    MediaManager::start_decode(m_class);
    m_parse_class = m_class;

    //pthread_create(&m_class->pthread_[1], nullptr, decoder_thread, this);
    //pthread_join(m_class->pthread_[1], nullptr);
}