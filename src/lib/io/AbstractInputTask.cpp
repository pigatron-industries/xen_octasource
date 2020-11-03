#include "AbstractInputTask.h"
#include "../../hwconfig.h"
#include "../../Config.h"

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

    _potCalibration = Config::instance.getPotCalibrations();

    // Check for calibration mode
    delay(100);
    if(digitalRead(_modeSwitchPin) == LOW) {
        doCalibrationSequence();
    }

}

float AbstractInputTask::getValue(uint8_t pin) {
    return _cvInputOutput.getVoltage(pin);
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

    while (digitalRead(_modeSwitchPin) == LOW) {
        Serial.println("Release mode switch...");
    }

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

    Config::instance.savePotCalibration(_potCalibration, _potCalibrationSize);
    Serial.println("Calibration finished.");
}
