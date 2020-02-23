#include "Oscillator.h"

#include <Arduino.h>

#define MAX_AMPLITUDE 5

Oscillator::Oscillator() {
      _position = 0;
      _frequencyHz = 1;
      _amplitude = MAX_AMPLITUDE;
}

void Oscillator::setFrequencyHz(float frequencyHz) {
    _frequencyHz = frequencyHz;
}

void Oscillator::setAmplitude(float amplitude) {
    _amplitude = amplitude;
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

    //float value = _rampWave.getValue(_position);
    //float value = _triangleWave.getValue(_position);
    float value = _sineWave.getValue(_position);

    float voltage = value / MAX_POSITION * _amplitude;
    return voltage;
}
