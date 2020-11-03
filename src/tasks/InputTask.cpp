#include "InputTask.h"
#include "../hwconfig.h"
#include "../Config.h"
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
  _modeSwitch(MODE_SWITCH_PIN, 100),
  _modeEncoder(MODE_ENCODER_PIN1, MODE_ENCODER_PIN2) {
    _calibrationMode = false;
    _slaveMode = false;
    AbstractInputTask::setPotCalibration(MODE_SWITCH_PIN, CALIBRATED_POT_SIZE, OUTPUT_CV_PIN_START+1);
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
    if(Config::instance.getSelectedMode() < MODE_COUNT) {
        _octasource.setMode(Config::instance.getSelectedMode());
        _octasource.setSubMode(Config::instance.getSelectedMode());
    }
    _modeSwitch.update();
    delay(100);
    _modeSwitch.update();
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
        return;
    }

    _encoderMovement += _modeEncoder.readAndReset();
    if(_encoderMovement != 0 && _encoderMovement%4 == 0) {
        _octasource.cycleSubMode(_encoderMovement/4);
        _encoderMovement = 0;
        Config::instance.saveSelectedMode(_octasource.getMode(), _octasource.getSubMode());
        printMode();
    }

    float triggerValue = getValue(TRIGGER_IN_PIN);
    _octasource.setTriggerValue(triggerValue);
    if(_trigger.update(triggerValue)) {
        if(_trigger.risingEdge()) {
            _octasource.trigger();
        }
    }

    if(!_slaveMode) {
        float rateVoltage = getCalibratedValue(RATE_POT_PIN) + getValue(RATE_CV_PIN);
        float rateFrequency = rateVoltageToFrequency(rateVoltage);
        _octasource.setFrequencyHz(rateFrequency);
        sendData();
    } else {
        receiveData();
    }

    float amplitude = getCalibratedValue(LENGTH_POT_PIN) + getValue(LENGTH_CV_PIN);
    _octasource.setAmplitude(amplitude);

    float wave = getCalibratedValue(WAVE_POT_PIN) + getValue(WAVE_CV_PIN);
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
    uint8_t mode = _octasource.cycleMode();
    Config::instance.saveSelectedMode(mode, _octasource.getSubMode());
    printMode();

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

void InputTask::printMode() {
    Serial.print("Mode: ");
    Serial.print(_octasource.getMode());
    Serial.print(".");
    Serial.println(_octasource.getSubMode());
}

void InputTask::switchSlaveMode() {
    _slaveMode = !_slaveMode;
    Serial.print("Mode Switch Slave: ");
    Serial.println(_slaveMode);
}

void InputTask::sendData() {
    if(_transmitTimer.isStopped()) {
        Serial2.print('f');
        writeFloat(Serial2, _octasource.getFrequencyHz());
        writeFloat(Serial2, _octasource.getPosition());
        _transmitTimer.start(TRANSMIT_TIME);
    }
}

float InputTask::receiveData() {
    if(Serial2.available()) {
        byte b = getByte();
        Serial.println(b);
        if(b == 'f') {
            _octasource.setFrequencyHz(readFloat(Serial2));
            _octasource.setPosition(readFloat(Serial2));
        }
    }

    return 0;
}
