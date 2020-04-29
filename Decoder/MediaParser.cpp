//
// Created by qiyun on 2020/4/24.
//

#include <tuple>
#include <time.h>
#include <zconf.h>
#include "MediaParser.h"
#include "../MessageQueue/DataBufferQueue.h"

int MediaParser::open_file_input(char* path) {
    int ret;

    AVDictionary *optionsDict = nullptr;
    av_dict_set(&optionsDict, "rtsp_transport", "tcp", 0);
    av_dict_set(&optionsDict, "stimeout", "5000000", 0);
    av_dict_set(&optionsDict, "rw_timeout", "5000", 0);

    if ((ret = avformat_open_input(&fmt_ctx, path, nullptr, &optionsDict)) < 0) {
        fprintf(stderr, "avformat_open_input error ... \n");
        return ret;
    }

    if ((ret = avformat_find_stream_info(fmt_ctx, nullptr)) < 0) {
        fprintf(stderr, "avformat_find_stream_info error ... \n");
        return ret;
    }

    fmt_ctx->probesize = 8192;
    fmt_ctx->max_analyze_duration = 5 * AV_TIME_BASE;
    printf("protocol = %s, format = %s, codec_whitelist = %s \n", fmt_ctx->protocol_whitelist, fmt_ctx->format_whitelist, fmt_ctx->codec_whitelist);
    av_dump_format(fmt_ctx, 0, path, 0);

    if ((ret = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, v_stream_index, &v_codec, 0)) < 0) {
        fprintf(stderr, "av_find_best_stream video error ... \n");
    } else {
        has_video_track = 1;
    }

    if ((ret = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, a_stream_index, &a_codec, 0)) < 0) {
        fprintf(stderr, "av_find_best_stream audio error ... \n");
    } else {
        has_audio_track = 1;
    }

    for (int i = 0; i < fmt_ctx->nb_streams; i ++) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            v_stream_index = i;
            m_stream_ = fmt_ctx->streams[v_stream_index];
        } else if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            a_stream_index = i;
        }
    }
    return (has_audio_track | has_video_track);
}


// 打开指定媒体解码器
AVCodecContext *CodecContextOnFormatContext(AVFormatContext *fmt_ctx, int stream_index, bool video_type, int *out_ret) {
    if (stream_index < 0)
        return nullptr;
    AVCodec *codec = avcodec_find_decoder(fmt_ctx->streams[stream_index]->codecpar->codec_id);
    AVCodecParameters *codec_params = fmt_ctx->streams[stream_index]->codecpar;
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_ctx, codec_params);
    if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
        printf("%s decode open failed ... \n", (video_type) ? "Video" : "Audio");
        *out_ret = -1;
    }
    return codec_ctx;
}


bool thread_control(MediaParser *mediaParser, int a_nums, int v_nums, pthread_mutex_t *mutex, pthread_cond_t *cond,
                    double limit_time) {
    /* 存在视频轨道，计算所有视频帧需要播放的时间，否则将以音频帧数计算播放时间 */
    double_t duration = mediaParser->has_video_track ? (1.0 / mediaParser->GetFPS()) * v_nums : (mediaParser->GetAudioFrameOfSize()) * a_nums;
    printf("视频帧数 = %d, 音频帧数 = %d,  帧可播放时长 = %.2f \n", v_nums, a_nums, duration);
    if (duration > limit_time) {
        printf("线程等待 ...... \n");
        return true;
    } else {
        printf("线程等待取消 ...... \n");
        return false;
    }
}

void* MediaParser::parser_thread(void* threadHanlder) {
    auto *mediaParser = static_cast<MediaParser *>(threadHanlder);
    if (mediaParser == nullptr)
        return nullptr;

    AVPacket *packet = mediaParser->m_pkt_;
    int val = 0;
    if (mediaParser->has_video_track || mediaParser->has_audio_track) {
        /* 通知注册类，开始解码 */
        mediaParser->observer_notify();
        /* 从媒体文件中逐包读取媒体数据 */
        while (!mediaParser->is_completion_) {
            /* 添加锁，防止多线程数据访问出错 */
            pthread_mutex_lock(&mediaParser->mutex);
            /* 控制缓存队列存储数据量 */
            bool is_waitting = thread_control(mediaParser, mediaParser->bufferQueue->a_samples, mediaParser->bufferQueue->v_samples, &mediaParser->mutex, &mediaParser->cv, mediaParser->max_cache_time);
            if (!is_waitting) {
                if (av_read_frame(mediaParser->fmt_ctx, packet) < 0) {
                    break;
                }
                /* 读取媒体数据包，放入缓存队列进行存储 */
                if (packet->stream_index == mediaParser->v_stream_index) {
                    // For video track
                    mediaParser->bufferQueue->insert(packet, AVMEDIA_TYPE_VIDEO);
                } else if (packet->stream_index == mediaParser->a_stream_index) {
                    // For audio track
                    mediaParser->bufferQueue->insert(packet, AVMEDIA_TYPE_AUDIO);
                }
                //av_packet_unref(packet);
                pthread_mutex_unlock(&mediaParser->mutex);
            } else {
                usleep(50 * 1000);
                printf("-----------------------------------------------------------  线程等待 \n");
            }
        }
        mediaParser->is_completion_ = true;
        printf("文件中媒体数据读取完成 .....  \n");
    }
    return nullptr;
}


MediaParser::MediaParser(char *path /*, std::tuple<> tuple*/) {

    int val;
    avformat_network_init();
    val = this->open_file_input(path);
    if (val < 0) {
        printf("加载失败，文件路径有问题 = %s \n", path);
        is_completion_ = true;
        return ;
    }

    // open the codec
    v_codec_ctx_ = CodecContextOnFormatContext(fmt_ctx, v_stream_index, true, &val);
    a_codec_ctx_ = CodecContextOnFormatContext(fmt_ctx, a_stream_index, false, &val);

    /* initialize a condition variable */
    pthread_cond_init(&cv, &cattr);
    pthread_mutex_init(&mutex, &mattr);

    m_pkt_ = (AVPacket *) av_malloc(sizeof(AVPacket));;
    bufferQueue = new mq::DataBufferQueue();
}


MediaParser::~MediaParser() {
    delete bufferQueue;

    av_packet_free(&m_pkt_);
    if (v_codec_ctx_ != nullptr) avcodec_free_context(&v_codec_ctx_);
    if (a_codec_ctx_ != nullptr) avcodec_free_context(&a_codec_ctx_);

    pthread_cond_destroy(&cv);
    pthread_mutex_destroy(&mutex);
}