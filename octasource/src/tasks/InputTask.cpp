#include "InputTask.h"
#include "../hwconfig.h"
#include "../lib/util.h"
#include "../lib/io/SerialUtil.h"

#include <Arduino.h>
#include <math.h>

#define RATE_EXP_START_FREQ 0.1
#define RATE_EXP_MULT 4

#define TRANSMIT_TIME 10000


InputTask::InputTask(CvInputOutput& cvInputOutput, OctaSource& octasource) :
  AbstractInputTask(cvInputOutput),
  _octasource(octasource),
  _modeSwitch(MODE_SWITCH_PIN, 100) {
    _calibrationMode = false;
    _slaveMode = false;
    AbstractInputTask::setPotCalibration(MODE_SWITCH_PIN, CALIBRATED_POT_SIZE, OUTPUT_CV_PIN_START);
    _potCalibration[0] = PotCalibration(RATE_POT_PIN, -5, 5);
    _potCalibration[1] = PotCalibration(LENGTH_POT_PIN, 0, 5);
    _potCalibration[2] = PotCalibration(WAVE_POT_PIN, 0, 4);
}

void InputTask::init() {
    Serial2.begin(SERIAL_BAUD);
    _cvInputOutput.setPinModeAnalogIn(RATE_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(RATE_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(WAVE_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(WAVE_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(LENGTH_POT_PIN);
    _cvInputOutput.setPinModeAnalogIn(LENGTH_CV_PIN);
    _cvInputOutput.setPinModeAnalogIn(TRIGGER_IN_PIN);
    AbstractInputTask::init();
}

void InputTask::execute() {
    if(_modeSwitch.update()) {
        if(_modeSwitch.rose() && _modeSwitch.previousDuration() >= 3000) {
            switchSlaveMode();
        }
        if(_modeSwitch.rose() && _modeSwitch.previousDuration() < 3000) {
            switchMode();
        }
    }
    if(_modeSwitch.read() == LOW && _modeSwitch.duration() >= 3000) {
        return; //TODO indicate mode switch somehow
    }

    if(_trigger.update(getValue(TRIGGER_IN_PIN))) {
        if(_trigger.risingEdge()) {
            _octasource.trigger();
        }
    }

    if(!_slaveMode) {
        float rateVoltage = getCalibratedValue(RATE_POT_PIN) + getValue(RATE_CV_PIN);
        float rateFrequency = rateVoltageToFrequency(rateVoltage);
        _octasource.setFrequencyHz(rateFrequency);
        sendData(rateFrequency);
    } else {
        float rateFrequency = receiveData();
        if(rateFrequency != 0) {
            _octasource.setFrequencyHz(rateFrequency);
        }
    }

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

void InputTask::switchMode() {
    _octasource.cycleMode();
    Serial.print("Mode Switch: ");
    Serial.println(_octasource.getMode());

    // Indicate new mode
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _cvInputOutput.setVoltage(OUTPUT_CV_PIN_START+i, 0);
    }
    uint8_t modeNum = _octasource.getMode();
    long startTime = millis();
    long time = millis();
    while(time - startTime < 500) {
        _cvInputOutput.setVoltage(OUTPUT_CV_PIN_START+modeNum, 3);
        delay(1);
        _cvInputOutput.setVoltage(OUTPUT_CV_PIN_START+modeNum, -3);
        delay(1);
        time = millis();
    }
}

void InputTask::switchSlaveMode() {
    _slaveMode = !_slaveMode;
    Serial.print("Mode Switch Slave: ");
    Serial.println(_slaveMode);
}

void InputTask::sendData(float frequency) {
    if(_transmitTimer.isStopped()) {
        Serial2.print('f');
        writeFloat(Serial2, frequency);
        _transmitTimer.start(TRANSMIT_TIME);
    }
}

float InputTask::receiveData() {
    if(Serial2.available()) {
        byte b = getByte();
        Serial.println(b);
        if(b == 'f') {
            return readFloat(Serial2);
        }
    }

    return 0;
}
