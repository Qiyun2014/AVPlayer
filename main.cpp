#include <iostream>
#include <zconf.h>
#include "Decoder/MediaParser.h"
#include "Decoder/MediaDecoder.h"
#include <SDL2/SDL.h>

SDL_Renderer *renderer_;
SDL_Texture *texture_;
SDL_Window *window_;
SDL_mutex *text_mutex_;
int pixel_width_, pixel_height_;

int main() {

    std::cout << "Hello, World!" << std::endl;
    //std::string str("/Users/qiyun/Desktop/example_output.h265");
    std::string str("/Users/qiyun/Desktop/example.mp4");

    auto *mediaParser = new MediaParser(const_cast<char *>(str.c_str()));
    auto *mediaDecoder = new MediaDecoder();
    mediaParser->observer_register_obj(mediaDecoder);
    mediaDecoder->start_decode(mediaParser);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }

    pixel_width_ = mediaParser->GetPixelsOfWidth();
    pixel_height_ = mediaParser->GetPixelsOfHeight();
    window_ = SDL_CreateWindow("Media Player",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               pixel_width_,
                               pixel_height_,
                               SDL_WINDOW_RESIZABLE);

    if (!window_) {
        fprintf(stderr, "\nSDL: could not set video mode:%s - exiting\n", SDL_GetError());
        exit(1);
    }
    //SDL_ShowWindow(window_);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, pixel_width_, pixel_height_);
    text_mutex_ = SDL_CreateMutex();


    auto dec_start = [](MediaDecoder *mediaDecoder1) {

    };

    // 解码完成
    auto dec_complete = []() {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    };

    auto dec_frame = [](AVFrame *out_frame, AVMediaType mediaType, double pts) {
        SDL_Rect rect;
        if (out_frame && out_frame->data[0]) {
            SDL_UpdateYUVTexture(
                    texture_,
                    nullptr,
                    out_frame->data[0], out_frame->linesize[0],
                    out_frame->data[1], out_frame->linesize[1],
                    out_frame->data[2], out_frame->linesize[2]);

            rect.x = 0;
            rect.y = 0;
            rect.w = pixel_width_;
            rect.h = pixel_height_;

            SDL_LockMutex(text_mutex_);
            SDL_RenderClear(renderer_);
            SDL_RenderCopy(renderer_, texture_, nullptr, &rect);
            SDL_RenderPresent(renderer_);
            SDL_UnlockMutex(text_mutex_);
        }
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