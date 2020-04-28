//
// Created by qiyun on 2020/4/27.
//

#ifndef AVPLAYER_MEDIADECODER_H
#define AVPLAYER_MEDIADECODER_H

#import "MediaManager.h"

class MediaDecoder : public avplayer::MediaManager {
public:
    MediaDecoder();
    ~MediaDecoder();

    /* 解码函数回调 */
    void (*decode_frame) (AVFrame *out_frame, AVMediaType mediaType, double pts){};
    /* 解码开始 */
    void (*decode_start) (MediaDecoder *mediaDecoder){};
    /* 解码完成回调 */
    void (*decode_complete) (){};

    /* 解码开始 */
    void start_decode(avplayer::MediaManager* m_class) override;
    /* 解码线程 */
    static void* decoder_thread(void *userdata);

    AVPacket    *out_pkt;
    AVFrame     *out_frame;
    double      pts = 0;

    avplayer::MediaManager *m_parse_class = nullptr;
};


#endif //AVPLAYER_MEDIADECODER_H
