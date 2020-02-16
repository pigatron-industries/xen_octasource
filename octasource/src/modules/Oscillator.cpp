#include "Oscillator.h"

#include <Arduino.h>

#define AMP_SCALE 5

Oscillator::Oscillator() {
      _position = 0;
      _frequencyHz = 100;
}

void Oscillator::setFrequencyHz(float frequencyHz) {
    _frequencyHz = frequencyHz;
}

float Oscillator::execute(unsigned long timeDiff) {

    // update position
    _position += (timeDiff * _frequencyHz);
    if(_position > MAX_POSITION) {
        _position -= MAX_POSITION;
    }


    float value = _rampWave.getValue(_position);

    float voltage = value / MAX_POSITION*AMP_SCALE;
    return voltage;
}
