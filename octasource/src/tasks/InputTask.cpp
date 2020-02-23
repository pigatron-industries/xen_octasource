#include "InputTask.h"

#include <Arduino.h>
#include <math.h>

#define RATE_EXP_START_FREQ 0.1
#define RATE_EXP_MULT 4

InputTask::InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource) :
    _cvInputOutput(cvInputOutput),
    _octasource(octasource),
    _ratePotCalibration(-2.90, 3.67, -5, 5),
    _amplitudePotCalibration(-3.07, 3.72, 0, 5),
    _wavePotCalibration(-3.13, 3.83, 0, 4) {
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
    rateVoltage = _ratePotCalibration.getCalibratedValue(rateVoltage);
    float rateFrequency = rateVoltageToFrequency(rateVoltage);
    _octasource.setFrequencyHz(rateFrequency);

    float amplitude = _cvInputOutput.getVoltage(LENGTH_POT_PIN);
    amplitude = _amplitudePotCalibration.getCalibratedValue(amplitude);
    _octasource.setAmplitude(amplitude);

    float wave = _cvInputOutput.getVoltage(WAVE_POT_PIN);
    wave = _wavePotCalibration.getCalibratedValue(wave);
    _octasource.setWave(wave);
}

float InputTask::rateVoltageToFrequency(float voltage) {
    if(voltage <= 1 && voltage >= -1) {
        return RATE_EXP_START_FREQ * voltage;
    } else if(voltage > 1) {
        return RATE_EXP_START_FREQ * pow(RATE_EXP_MULT, voltage-1);
    } else {
        return -RATE_EXP_START_FREQ * pow(RATE_EXP_MULT, -1-voltage);
    }
}
