#include <iostream>
#include <zconf.h>
#include "Decoder/MediaParser.h"
#include "Decoder/MediaDecoder.h"


int main() {

    std::cout << "Hello, World!" << std::endl;
    //std::string str("/Users/qiyun/Desktop/example_output.h265");
    std::string str("/Users/qiyun/Desktop/IMG_0007.mp4");

    auto *mediaParser = new MediaParser(const_cast<char *>(str.c_str()));
    auto *mediaDecoder = new MediaDecoder();
    mediaParser->observer_register_obj(mediaDecoder);
    mediaDecoder->start_decode(mediaParser);


    std::future<void *> demux_thread = std::async(std::launch::async, MediaParser::parser_thread, mediaParser);
    std::future<void *> decode_thread = std::async(std::launch::async, MediaDecoder::decoder_thread, mediaDecoder);
    decode_thread.get();
    demux_thread.get();

    return 0;
}