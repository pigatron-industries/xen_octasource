#include "OctaSource.h"

#include <Arduino.h>
#include <math.h>

#define AMP_SCALE 5

OctaSource::OctaSource() {
    setMode(modePhased);
}

void OctaSource::cycleMode() {
    switch(_mode) {
        case modePhased:
            setMode(modeMultiplied);
            break;
        case modeMultiplied:
            setMode(modeUncorrelated);
            break;
        default:
            setMode(modePhased);
    }
}

void OctaSource::setMode(OctasourceMode_t mode) {
    _mode = mode;
    switch(_mode) {
        case modePhased:
            initPhasedMode();
            break;
        case modeUncorrelated:
            initUncorrelatedMode();
            break;
        default:
            initPhaseAll();
    }
}

void OctaSource::setFrequencyHz(float frequencyHz) {
    switch(_mode) {
        case modeMultiplied:
            setFrequencyMultipliedMode(frequencyHz);
            break;
        case modeUncorrelated:
            setFrequencyUncorrelatedMode(frequencyHz);
            break;
        default:
            setFrequencyAll(frequencyHz);
    }
}

void OctaSource::setAmplitude(float amplitude) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setAmplitude(amplitude);
    }
}

void OctaSource::setWave(float wave) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setWave(wave);
    }
}

void OctaSource::trigger() {
    setMode(_mode); // re-initialise current mode
}

void OctaSource::execute(unsigned long timeDiff) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _outputs[i] = _oscillators[i].execute(timeDiff);
    }
}

float OctaSource::getOutput(uint8_t index) {
    return _outputs[index];
}

void OctaSource::setFrequencyAll(float frequencyHz) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(frequencyHz);
    }
}

void OctaSource::setFrequencyMultipliedMode(float frequencyHz) {
    float freq = frequencyHz;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(freq);
        freq /= 2;
    }
}

void OctaSource::setFrequencyUncorrelatedMode(float frequencyHz) {
    float freq = frequencyHz;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setFrequencyHz(freq);
        freq /= M_PI; //An irrational number
    }
}

void OctaSource::initPhaseAll() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setPosition(0);
    }
}

void OctaSource::initPhasedMode() {
    _oscillators[0].setPosition(0);
    _oscillators[1].setPosition((MAX_POSITION/8)*1);
    _oscillators[2].setPosition((MAX_POSITION/8)*2);
    _oscillators[3].setPosition((MAX_POSITION/8)*3);
    _oscillators[4].setPosition((MAX_POSITION/8)*4);
    _oscillators[5].setPosition((MAX_POSITION/8)*5);
    _oscillators[6].setPosition((MAX_POSITION/8)*6);
    _oscillators[7].setPosition((MAX_POSITION/8)*7);
}

void OctaSource::initUncorrelatedMode() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setPosition(random(MAX_POSITION));
    }
}
