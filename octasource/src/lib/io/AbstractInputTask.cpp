#include "AbstractInputTask.h"

#include <Arduino.h>

AbstractInputTask::AbstractInputTask(CvInputOutput& cvInputOutput) :
  _cvInputOutput(cvInputOutput) {
    _calibrationMode = false;
    _potCalibrationSize = 0;
}

void AbstractInputTask::setPotCalibration(uint8_t modeSwitchPin, uint8_t* potCalibrationPins, uint8_t potCalibrationSize) {
    _modeSwitchPin = modeSwitchPin;
    _potCalibrationSize = potCalibrationSize;
    _potCalibration = new PotCalibration[_potCalibrationSize];
    for(uint8_t i = 0; i < _potCalibrationSize; i++) {
        _potCalibration[i] = PotCalibration(potCalibrationPins[i], -5, 5, -5, 5);
    }
}

void AbstractInputTask::init() {
    Task::init();

    // load pot calibration


    // Check for calibration mode
    pinMode(_modeSwitchPin, INPUT_PULLUP);
    digitalWrite(_modeSwitchPin, HIGH);
    if(digitalRead(_modeSwitchPin) == LOW) {
        Serial.println("Calibration Mode Started.");
        _calibrationMode = true;
    }

}

void AbstractInputTask::execute() {
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
