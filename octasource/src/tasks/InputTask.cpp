#include "InputTask.h"
#include "../hwconfig.h"
#include "../lib/util.h"

#include <Arduino.h>
#include <math.h>

#define RATE_EXP_START_FREQ 0.1
#define RATE_EXP_MULT 4


InputTask::InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource) :
    AbstractInputTask(cvInputOutput),
    _octasource(octasource) {
      _calibrationMode = false;
      AbstractInputTask::setPotCalibration(MODE_SWITCH_PIN, CALIBRATED_POT_SIZE, OUTPUT_CV_PIN_START);
      _potCalibration[0] = PotCalibration(RATE_POT_PIN, -5, 5);
      _potCalibration[1] = PotCalibration(LENGTH_POT_PIN, 0, 5);
      _potCalibration[2] = PotCalibration(WAVE_POT_PIN, 0, 4);

      //TODO reload mode from EEPROM
      _octasource.setMode(modePhased);
}

void InputTask::init() {
    _cvInputOutput.setPinModeAnalogIn(RATE_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(RATE_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(WAVE_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(WAVE_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(LENGTH_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(LENGTH_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(TRIGGER_PIN);
    AbstractInputTask::init();
}

void InputTask::execute() {
    float rateVoltage = getCalibratedValue(RATE_POT_PIN);
    float rateFrequency = rateVoltageToFrequency(rateVoltage);
    _octasource.setFrequencyHz(rateFrequency);

    float amplitude = getCalibratedValue(LENGTH_POT_PIN);
    _octasource.setAmplitude(amplitude);

    float wave = getCalibratedValue(WAVE_POT_PIN);
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
