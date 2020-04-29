//
// Created by qiyun on 2020/4/29.
//

#ifndef AVPLAYER_SDLRENDER_H
#define AVPLAYER_SDLRENDER_H

#include <SDL2/SDL.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavresample/avresample.h>
}

class SDLRender {
public:
    SDLRender(int width, int height);
    ~SDLRender();

    // 直接渲染yuv420p格式图像
    void sdl_render_frame(AVFrame *frame);

private:
    SDL_Renderer *renderer_;
    SDL_Texture *texture_;
    SDL_Window *window_;
    SDL_mutex *text_mutex_;
    int width_{}, height_{};
};


#endif //AVPLAYER_SDLRENDER_H
