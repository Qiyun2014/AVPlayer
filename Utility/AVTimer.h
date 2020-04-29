//
// Created by qiyun on 2020/4/29.
//

#ifndef AVPLAYER_AVTIMER_H
#define AVPLAYER_AVTIMER_H

#include <iostream>
#include <thread>
#include <chrono>

class AVTimer {
    bool clear = false;
    int _delay{}, _interval{};
public:
    // AVTimer(int interval, int delay) : _interval(interval), _delay(delay) {}
    // virtual ~AVTimer() = default;

    // 设置超时
    template <typename Function>
    void setTimeout(Function function, int delay);

    // 设置间隔时长
    //template <typename Function>
    void setInterval(/*Function function, */int interval, void (*func) ());

    // 停止
    void stop();
};

#endif //AVPLAYER_AVTIMER_H
