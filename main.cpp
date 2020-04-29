#include <iostream>
#include <zconf.h>
#include "Decoder/MediaParser.h"
#include "Decoder/MediaDecoder.h"
#include "Decoder/Render/SDLRender.h"

static SDLRender *render;

int main() {

    std::cout << "Hello, World!" << std::endl;
    std::string str("/Users/qiyun/Desktop/example_output.h265");
    // std::string str("/Users/qiyun/Desktop/example.mp4");

    auto *mediaParser = new MediaParser(const_cast<char *>(str.c_str()));
    auto *mediaDecoder = new MediaDecoder();
    mediaParser->observer_register_obj(mediaDecoder);
    mediaDecoder->start_decode(mediaParser);

    render = new SDLRender(mediaParser->GetPixelsOfWidth(), mediaParser->GetPixelsOfHeight());

    auto dec_start = [](MediaDecoder *mediaDecoder1) {

    };

    // 解码完成
    auto dec_complete = []() {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    };

    auto dec_frame = [](AVFrame *out_frame, AVMediaType mediaType, double pts) {
        render->sdl_render_frame(out_frame);
    };

    mediaDecoder->decode_complete = dec_complete;
    mediaDecoder->decode_frame = dec_frame;
    mediaDecoder->decode_start = dec_start;

    std::future<void *> demux_thread = std::async(std::launch::async, MediaParser::parser_thread, mediaParser);
    std::future<void *> decode_thread = std::async(std::launch::async, MediaDecoder::decoder_thread, mediaDecoder);
    decode_thread.get();
    demux_thread.get();

    return 0;
}