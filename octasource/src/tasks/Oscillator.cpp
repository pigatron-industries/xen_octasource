#include "Oscillator.h"

#include <Arduino.h>

#define AMP_SCALE 5

Oscillator::Oscillator(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
      position = 0;
      _frequencyHz = 100;
}

void Oscillator::init() {
    Task::init();
}

void Oscillator::setFrequencyHz(float frequencyHz) {
    _frequencyHz = frequencyHz;
}

void Oscillator::execute() {

    // update position
    position += (lastExecutionDiff * _frequencyHz);
    if(position > MAX_POSITION) {
        position -= MAX_POSITION;
    }


    float value = _rampWave.getValue(position);

    float voltage = value / MAX_POSITION*AMP_SCALE;
    _cvInputOutput.setVoltage(12, voltage);
}
