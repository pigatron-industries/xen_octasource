#include "InputTask.h"

#include <Arduino.h>

InputTask::InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource) :
    _cvInputOutput(cvInputOutput),
    _octasource(octasource) {
}

void InputTask::init() {
    Task::init();
    _cvInputOutput.setPinModeAnalogIn(RATE_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(RATE_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(WAVE_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(WAVE_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(LENGTH_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(LENGTH_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(TRIGGER_PIN);
}

void InputTask::execute() {
    float rateVoltage = _cvInputOutput.getVoltage(RATE_POT_PIN);
    //TODO convert rate voltage to frequency
    float frequency = rateVoltage;
    _octasource.setFrequencyHz(frequency);
}
