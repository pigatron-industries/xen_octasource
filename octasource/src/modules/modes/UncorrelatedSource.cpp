#include "UncorrelatedSource.h"

#include <Arduino.h>
#include <math.h>

void UncorrelatedSource::init() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setPosition(random(MAX_POSITION));
    }
}

void UncorrelatedSource::setFrequencyHz(float frequencyHz) {
    float freq = frequencyHz;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(freq);
        freq /= M_PI; //An irrational number
    }
}
