#include "Oscillator.h"

#include <Arduino.h>

#define MAX_AMPLITUDE 5

Oscillator::Oscillator() {
      _position = 0;
      _frequencyHz = 1;
      _wave = 0;
      _amplitude = MAX_AMPLITUDE;
}

void Oscillator::setFrequencyHz(float frequencyHz) {
    _frequencyHz = frequencyHz;
}

void Oscillator::setAmplitude(float amplitude) {
    _amplitude = amplitude;
}

void Oscillator::setWave(float wave) {
    _wave = wave;
}

void Oscillator::setPosition(float position) {
    _position = position;
}

float Oscillator::execute(unsigned long timeDiff) {

    // update position
    _position += (timeDiff * _frequencyHz);
    if(_position > MAX_POSITION) {
        _position -= MAX_POSITION;
    } else if (_position < 0) {
        _position += MAX_POSITION;
    }

    float value = 0;
    if(_wave < 1) {
        value = _rampWave.getValue(_position);
    } else if(_wave < 2) {
        value = _triangleWave.getValue(_position);
    } else if (_wave < 3) {
        value = _sineWave.getValue(_position);
    } else {
        value = _squareWave.getValue(_position);
    }

    float voltage = value / MAX_POSITION * _amplitude;
    return voltage;
}
