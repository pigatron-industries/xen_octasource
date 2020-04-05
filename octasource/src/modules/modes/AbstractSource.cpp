#include "AbstractSource.h"


void AbstractSource::execute(unsigned long timeDiff) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _outputs[i] = _oscillators[i].execute(timeDiff);
    }
}

float AbstractSource::getOutput(uint8_t index) {
    return _outputs[index];
}

void AbstractSource::init() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setPosition(0);
    }
}

void AbstractSource::setFrequencyHz(float frequencyHz) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(frequencyHz);
    }
}

void AbstractSource::setAmplitude(float amplitude) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setAmplitude(amplitude);
    }
}

void AbstractSource::setWave(float wave) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setWave(wave);
    }
}

void AbstractSource::trigger() {
    init();
}
