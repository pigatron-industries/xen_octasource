#include "Timer.h"

#include <Arduino.h>

Timer::Timer() {
}

void Timer::start(unsigned long waitTime) {
    _running = true;
    _waitTime = waitTime;
    _startTime = micros();
}

bool Timer::isRunning() {
    update();
    return _running;
}

bool Timer::isStopped() {
    update();
    return !_running;
}

void Timer::update() {
    if(_running) {
        unsigned long timeDiff = micros() - _startTime;
        if(timeDiff > _waitTime) {
            _running = false;
        }
    }
}
