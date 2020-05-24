#include "UncorrelatedSource.h"

#include <Arduino.h>
#include <math.h>

void UncorrelatedSource::init() {
    AbstractSource::init();
    _modeCount = 4;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setPosition(random(MAX_POSITION));
        _oscillators[i].setCycle(true);
    }
}

void UncorrelatedSource::setFrequencyHz(float frequencyHz) {
    float freq = frequencyHz;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(freq);
        if(_mode == 0) {
            freq /= 1.41421356; // Square root of 2
        } else if (_mode == 1) {
            freq /= 1.61803398875; // Golden Ratio
        } else if (_mode == 2) {
            freq /= 2.718281828; // Euler's Number
        } else if (_mode == 3) {
            freq /= M_PI; // Pi 3.14159...
        }
    }
}
