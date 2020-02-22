#include "InputTask.h"

#include <Arduino.h>
#include <math.h>

#define RATE_EXP_START_FREQ 0.1
#define RATE_EXP_MULT 3

InputTask::InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource) :
    _cvInputOutput(cvInputOutput),
    _octasource(octasource),
    _ratePotCalibration(-2.90, 3.67) {
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
    Serial.println("rateVoltage");
    Serial.println(rateVoltage);
    Serial.println("rateFrequency");
    Serial.println(rateFrequency);
    _octasource.setFrequencyHz(rateFrequency);
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
