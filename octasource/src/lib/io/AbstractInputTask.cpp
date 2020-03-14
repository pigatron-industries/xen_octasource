#include "AbstractInputTask.h"

#include <Arduino.h>

AbstractInputTask::AbstractInputTask(CvInputOutput& cvInputOutput, uint8_t modeSwitchPin, uint8_t potCalibrationsSize) :
    _cvInputOutput(cvInputOutput),
    _potCalibrationsSize(potCalibrationsSize),
    _modeSwitchPin(modeSwitchPin) {
      _calibrationMode = false;
      _potCalibrations = new PotCalibration[potCalibrationsSize];
}

void AbstractInputTask::init() {
    Task::init();

    // Load calibration settings


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
