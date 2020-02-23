#include "OctaSource.h"

#include <Arduino.h>

#define AMP_SCALE 5

OctaSource::OctaSource() {
    _oscillators[0].setPosition(0);
    _oscillators[1].setPosition((MAX_POSITION/8)*1);
    _oscillators[2].setPosition((MAX_POSITION/8)*2);
    _oscillators[3].setPosition((MAX_POSITION/8)*3);
    _oscillators[4].setPosition((MAX_POSITION/8)*4);
    _oscillators[5].setPosition((MAX_POSITION/8)*5);
    _oscillators[6].setPosition((MAX_POSITION/8)*6);
    _oscillators[7].setPosition((MAX_POSITION/8)*7);
}

void OctaSource::setFrequencyHz(float frequencyHz) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(frequencyHz);
    }
}

void OctaSource::setAmplitude(float amplitude) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setAmplitude(amplitude);
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
