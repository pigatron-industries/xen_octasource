#include "MultipliedSource.h"

void MultipliedSource::init() {
    AbstractSource::init();
    _modeCount = 2;
}

long MultipliedSource::setMode(long movement) {
    AbstractSource::setMode(movement);
    init();
    return getMode();
}

void MultipliedSource::setFrequencyHz(float frequencyHz) {
    float freq = frequencyHz;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(freq);
        if(_mode == 0) {
            freq /= 2;
        } else if (_mode == 1) {
            freq /= 3;
        }
    }
}
