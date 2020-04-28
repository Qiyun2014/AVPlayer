//
// Created by qiyun on 2020/4/24.
//

#include <tuple>
#include <list>

#ifndef AVPLAYER_MEDIAPARSER_H
#define AVPLAYER_MEDIAPARSER_H

#endif //AVPLAYER_MEDIAPARSER_H

#import "MediaManager.h"


class MediaParser : public avplayer::MediaManager {
public:
    explicit MediaParser(char *path /*, std::tuple<> tuple*/);
    ~MediaParser();

    // 加载本地或网络路径文件
    int open_file_input(char* path);

    void observer_register_obj(avplayer::MediaManager *obs) {
        m_observers.push_back(obs);
    };
    void observer_remove_obj(avplayer::MediaManager *obs) {
        m_observers.remove(obs);
    }
    void observer_notify() {
        auto it = m_observers.begin();
        while (it != m_observers.end()) {
            (*it)->start_decode(this);
            ++ it;
        }
    }

    // 解析线程
    static void* parser_thread(void* threadHanlder);

    pthread_condattr_t cattr{};
    pthread_mutexattr_t mattr{};
private:
    std::list<avplayer::MediaManager *> m_observers;
};