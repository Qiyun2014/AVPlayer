//
// Created by qiyun on 2020/4/29.
//

#include "SDLRender.h"


SDLRender::SDLRender(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }
    window_ = SDL_CreateWindow("Media Player",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width,
                               height,
                               SDL_WINDOW_RESIZABLE);
    if (!window_) {
        fprintf(stderr, "\nSDL: could not set video mode:%s - exiting\n", SDL_GetError());
        exit(1);
    }
    //SDL_ShowWindow(window_);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width, height);
    text_mutex_ = SDL_CreateMutex();
    SDL_PollEvent(nullptr);

    width_ = width;
    height_ = height;
}


void SDLRender::sdl_render_frame(AVFrame *frame) {
    SDL_Rect rect;
    if (frame && frame->data[0]) {
        rect.x = 0;
        rect.y = 0;
        rect.w = width_;
        rect.h = height_;

        SDL_UpdateYUVTexture(
                texture_,
                &rect,
                frame->data[0], frame->linesize[0],
                frame->data[1], frame->linesize[1],
                frame->data[2], frame->linesize[2]);

        SDL_LockMutex(text_mutex_);
        SDL_RenderClear(renderer_);
        SDL_RenderCopy(renderer_, texture_, nullptr, &rect);
        SDL_RenderPresent(renderer_);
        SDL_UnlockMutex(text_mutex_);
    }
}

SDLRender::~SDLRender() {
    SDL_DestroyMutex(text_mutex_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyTexture(texture_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

