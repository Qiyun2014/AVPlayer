#include <iostream>
#include <zconf.h>
#include "Decoder/MediaParser.h"
#include "Decoder/MediaDecoder.h"
#include "Decoder/Render/SDLRender.h"
#include "Utility/AVTimer.h"

static SDLRender *render;

void timer_callback() {
    printf("================================================================================ \n");
}

int main() {

    std::cout << "Hello, World!" << std::endl;
    std::string str("/Users/qiyun/Desktop/example_output.h265");
    // std::string str("/Users/qiyun/Desktop/example.mp4");


    auto *mediaParser   = new MediaParser(const_cast<char *>(str.c_str()));
    auto *mediaDecoder  = new MediaDecoder();
    mediaParser->observer_register_obj(mediaDecoder);
    mediaDecoder->start_decode(mediaParser);


    AVTimer timer = AVTimer();
    timer.setInterval(1000, timer_callback);


    // 解码完成
    auto dec_complete = []() {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    };


    // SDL图像渲染
    render = new SDLRender(mediaParser->get_pixels_width(), mediaParser->get_pixels_height());
    auto dec_frame = [](AVFrame *out_frame, AVMediaType mediaType, double pts) {
        render->sdl_render_frame(out_frame);
    };


    mediaDecoder->decode_complete = dec_complete;
    mediaDecoder->decode_frame = dec_frame;


    // 开始demux和解码线程
    std::future<void *> demux_thread = std::async(std::launch::async, MediaParser::parser_thread, mediaParser);
    std::future<void *> decode_thread = std::async(std::launch::async, MediaDecoder::decoder_thread, mediaDecoder);
    decode_thread.get();
    demux_thread.get();


    return 0;
}