#include "AbstractSource.h"


void AbstractSource::execute(unsigned long timeDiff) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _outputs[i] = _oscillators[i].execute(timeDiff);
    }
}

float AbstractSource::getOutput(uint8_t index) {
    return _outputs[index];
}

bool AbstractSource::getTriggerOut() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        bool trigger = _oscillators[i].getTriggerOut();
        if(trigger) {
            return true;
        }
    }
    return false;
}

void AbstractSource::init() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setPosition(0);
        _oscillators[i].setCycle(true);
    }
}

long AbstractSource::setMode(long movement) {
    if(movement >= 0) {
        _mode = (_mode+movement) % _modeCount;
    } else {
        _mode = ((_mode+movement) - (movement*_modeCount)) % _modeCount;
    }
    return _mode;
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

void AbstractSource::setPosition(float position) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setPosition(position);
    }
}

void AbstractSource::setTriggerValue(float position) {
}

void AbstractSource::trigger() {
    init();
}

float AbstractSource::getFrequencyHz() {
    return _oscillators[0].getFrequencyHz();
}

float AbstractSource::getPosition() {
    return _oscillators[0].getPosition();
}
