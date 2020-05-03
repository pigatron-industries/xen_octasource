#include "Oscillator.h"

#include <Arduino.h>

#define MAX_AMPLITUDE 5

Oscillator::Oscillator() {
      _position = 0;
      _frequencyHz = 1;
      _wave = 0;
      _amplitude = MAX_AMPLITUDE;
      _cycle = true;
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

void Oscillator::setCycle(bool cycle) {
    _cycle = cycle;
}

float Oscillator::execute(unsigned long timeDiff) {
    // reset trigger
    _trigger = false;
    if(_triggered) {
        _trigger = true;
        _triggered = false;
    }

    updatePosition(timeDiff);

    if(!_cycle && (_position < 0 || _position > MAX_POSITION)) {
        return 0;
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

void Oscillator::reset() {
      setPosition(0);
      _triggered = true;
}

void Oscillator::updatePosition(unsigned long timeDiff) {
    float newPos = _position + (timeDiff * _frequencyHz);
    if(_cycle) {
        if(newPos > MAX_POSITION) {
            newPos -= MAX_POSITION;
            _trigger = true;
        } else if (newPos < 0) {
            newPos += MAX_POSITION;
            _trigger = true;
        }
    } else {
        // trigger on 0 crossing
        if(_position <= 0 && newPos > 0) {
            _trigger = true;
        }
    }

    _position = newPos;
}
