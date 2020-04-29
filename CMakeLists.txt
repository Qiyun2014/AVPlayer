cmake_minimum_required(VERSION 3.15)
project(AVPlayer)

set(CMAKE_CXX_STANDARD 14)


# 判断编译器类型,如果是gcc编译器,则在编译选项中加入c++14支持
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++14")
endif(CMAKE_COMPILER_IS_GNUCXX)


# 引用第三库配置路径映射
set(SRC_DIR ./)
set(FFMPEG_DIR /usr/local/Cellar/ffmpeg/4.2.1_1)
set(SDL_DIR /usr/local/Cellar/sdl2/2.0.10/)
#set(libx265_DIR ./libs/libx265)


# 引入到工程
include_directories(
        ${FFMPEG_DIR}/include/
        ${SDL_DIR}/include/
        #${libx265_DIR}/include
)
link_directories(
        ${FFMPEG_DIR}/lib/
        ${SDL_DIR}/lib/
        #${libx265_DIR}/lib
)


# 执行文件
add_executable(
        AVPlayer

        main.cpp
        Decoder/MediaParser.cpp
        Decoder/MediaParser.h

        Decoder/MediaManager.h

        MessageQueue/DataBufferQueue.cpp
        MessageQueue/DataBufferQueue.h

        Decoder/MediaDecoder.cpp
        Decoder/MediaDecoder.h

        Decoder/MediaFormat_Desc.h
        Decoder/Render/SDLRender.cpp Decoder/Render/SDLRender.h)


# 依赖库
target_link_libraries(
        AVPlayer

        avcodec
        avdevice
        avfilter
        avformat
        avutil
        swresample
        swscale

        SDL2.dylib
        #x265
)

# mac
if (APPLE)
    target_link_libraries(AVPlayer "-framework OpenGL")
    target_link_libraries(AVPlayer "-framework GLUT")
endif()