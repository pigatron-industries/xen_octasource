#include "AbstractInputTask.h"

#include <Arduino.h>

AbstractInputTask::AbstractInputTask(CvInputOutput& cvInputOutput) :
  _cvInputOutput(cvInputOutput) {
    _calibrationMode = false;
    _potCalibrationSize = 0;
    _calibrationMode = 0;
}

void AbstractInputTask::setPotCalibration(uint8_t modeSwitchPin, uint8_t potCalibrationSize) {
    _modeSwitchPin = modeSwitchPin;
    _potCalibrationSize = potCalibrationSize;
    _potCalibration = new PotCalibration[_potCalibrationSize];
}

void AbstractInputTask::init() {
    Task::init();
    pinMode(_modeSwitchPin, INPUT_PULLUP);
    digitalWrite(_modeSwitchPin, HIGH);

    // TODO load pot calibration


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
    Serial.println("Calibration mode started.");
    Serial.println("Release mode switch...");

    while (digitalRead(_modeSwitchPin) == LOW) {}

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

    //TODO save calibration
}
