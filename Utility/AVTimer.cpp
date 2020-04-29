//
// Created by qiyun on 2020/4/29.
//

#include "AVTimer.h"
#include <thread>

template<typename Function>
void AVTimer::setTimeout(Function function, int delay) {
    this->clear = false;
    std::thread t([=]() {
        if(this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(this->clear) return;
        function();
    });
    t.detach();
}

//template<typename Function>
void AVTimer::setInterval(/*Function function, */int interval, void (*func) ()) {
    this->clear = false;
    std::thread t([=]() {
        while(true) {
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(this->clear) return;
            //function();
            func();
        }
    });
    t.detach();
}

void AVTimer::stop() {
    this->clear = true;
}

