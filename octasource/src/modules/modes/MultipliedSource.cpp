#include "MultipliedSource.h"


void MultipliedSource::setFrequencyHz(float frequencyHz) {
    float freq = frequencyHz;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(freq);
        freq /= 2;
    }
}
