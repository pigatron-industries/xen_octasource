#include "AbstractInputTask.h"
#include "../../hwconfig.h"

#include <Arduino.h>
#include <EEPROM.h>

AbstractInputTask::AbstractInputTask(CvInputOutput& cvInputOutput) :
  _cvInputOutput(cvInputOutput) {
    _calibrationMode = false;
    _potCalibrationSize = 0;
    _calibrationMode = 0;
}

void AbstractInputTask::setPotCalibration(uint8_t modeSwitchPin, uint8_t potCalibrationSize, uint8_t displayLedPin) {
    _modeSwitchPin = modeSwitchPin;
    _potCalibrationSize = potCalibrationSize;
    _displayLedPin = displayLedPin;
    _potCalibration = new PotCalibration[_potCalibrationSize];
}

void AbstractInputTask::init() {
    Task::init();
    pinMode(_modeSwitchPin, INPUT_PULLUP);
    digitalWrite(_modeSwitchPin, HIGH);

    loadCalibration();

    // Check for calibration mode
    if(digitalRead(_modeSwitchPin) == LOW) {
        doCalibrationSequence();
    }

}


float AbstractInputTask::getCalibratedValue(uint8_t pin) {
    float voltage = _cvInputOutput.getVoltage(pin);

    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        if(_potCalibration[i].getPin() == pin) {
            return _potCalibration[i].getCalibratedValue(voltage);
        }
    }

    return voltage;
}

void AbstractInputTask::doCalibrationSequence() {
    _cvInputOutput.setPinModeAnalogOut(_displayLedPin);
    _cvInputOutput.setVoltage(_displayLedPin, -5.0);
    Serial.println("Calibration mode started.");
    Serial.println("Release mode switch...");

    while (digitalRead(_modeSwitchPin) == LOW) {}

    _cvInputOutput.setVoltage(_displayLedPin, -5.0);
    Serial.println("Turn all pots left, then press mode switch...");
    delay(100);
    while (digitalRead(_modeSwitchPin) == HIGH) {}
    delay(100);
    while (digitalRead(_modeSwitchPin) == LOW) {}

    // Read in min voltages for each pot
    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        float voltage = _cvInputOutput.getVoltage(_potCalibration[i].getPin());
        _potCalibration[i].setRealMin(voltage);
    }

    _cvInputOutput.setVoltage(_displayLedPin, 5.0);
    Serial.println("Turn all pots right, then press mode switch...");
    delay(100);
    while (digitalRead(_modeSwitchPin) == HIGH) {}
    delay(100);
    while (digitalRead(_modeSwitchPin) == LOW) {}

    // Read in max voltages for each pot
    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        float voltage = _cvInputOutput.getVoltage(_potCalibration[i].getPin());
        _potCalibration[i].setRealMax(voltage);
    }

    Serial.println("Calibration finished.");
    saveCalibration();
}

void AbstractInputTask::loadCalibration() {
    int address = 0;
    float realMin, realMax;
    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        EEPROM.get(address, realMin);
        address += sizeof(float);
        EEPROM.get(address, realMax);
        address += sizeof(float);
        _potCalibration[i].setRealMin(realMin);
        _potCalibration[i].setRealMax(realMax);
    }
}

void AbstractInputTask::saveCalibration() {
    int address = 0;
    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        EEPROM.put(address, _potCalibration[i].getRealMin());
        address += sizeof(float);
        EEPROM.put(address, _potCalibration[i].getRealMax());
        address += sizeof(float);
    }
}
