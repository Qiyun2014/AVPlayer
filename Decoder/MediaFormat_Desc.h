//
// Created by qiyun on 2020/4/27.
//

#ifndef AVPLAYER_MEDIAFORMAT_DESC_H
#define AVPLAYER_MEDIAFORMAT_DESC_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavresample/avresample.h>
}

class MediaFormat_Desc {
private:

public:
    AVCodec *a_codec{}, *v_codec{};
    AVFormatContext *fmt_ctx{};
    AVCodecContext *v_codec_ctx{}, *a_codec_ctx{};
    AVStream *m_stream{};
    AVPacket *m_pkt{};
    int v_stream_index = -1, a_stream_index = -1;
    int has_video_track = 0;
    int has_audio_track = 0;

    bool is_completion_ = false;
    double max_cache_time = 5.0;   // 最大缓存时间，默认是5s

    float get_fps()              { return (has_video_track)? (float) fmt_ctx->streams[v_stream_index]->avg_frame_rate.num / (float) fmt_ctx->streams[v_stream_index]->avg_frame_rate.den: 0; }
    // (mediaParser->out_frame->pkt_duration) * av_q2d(mediaParser->m_parse_class->m_stream_->time_base);
    float get_duration_per_frame(AVMediaType mediaType)  {
        if (mediaType == AVMEDIA_TYPE_VIDEO)
            return (1 / get_fps());
        else
            return (float) a_codec_ctx->time_base.num / (float) a_codec_ctx->time_base.den;
    };
    int32_t get_pixels_width()  { return fmt_ctx->streams[v_stream_index]->codecpar->width; }
    int32_t get_pixels_height() { return fmt_ctx->streams[v_stream_index]->codecpar->height; }
    int64_t git_bitrate()       { return fmt_ctx->streams[v_stream_index]->codecpar->bit_rate; }
    int64_t get_audio_packet_size()  {
        return (has_audio_track) ?
               fmt_ctx->streams[a_stream_index]->codecpar->bits_per_raw_sample *
               fmt_ctx->streams[a_stream_index]->codecpar->sample_rate *
               fmt_ctx->streams[a_stream_index]->codecpar->channels / 8:
               0;
    }

    double GetAudioFrameOfSize()  {
        return (has_audio_track) ?
               (double) fmt_ctx->streams[a_stream_index]->codecpar->frame_size * get_duration_per_frame(AVMEDIA_TYPE_AUDIO) / (double)fmt_ctx->streams[a_stream_index]->codecpar->sample_rate :
               0;
    }
};


#endif //AVPLAYER_MEDIAFORMAT_DESC_H
