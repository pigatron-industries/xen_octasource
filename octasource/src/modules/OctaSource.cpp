#include "OctaSource.h"

#include <Arduino.h>

#define AMP_SCALE 5

OctaSource::OctaSource() {
}

void OctaSource::setFrequencyHz(float frequencyHz) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(frequencyHz);
    }
}

void OctaSource::execute(unsigned long timeDiff) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _outputs[i] = _oscillators[i].execute(timeDiff);
    }
}

float OctaSource::getOutput(uint8_t index) {
    return _outputs[index];
}
