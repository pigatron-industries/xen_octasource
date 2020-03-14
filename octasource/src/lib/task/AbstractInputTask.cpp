#include "AbstractInputTask.h"

#include <Arduino.h>

AbstractInputTask::AbstractInputTask(CvInputOutput& cvInputOutput, uint8_t modeSwitchPin) :
    _cvInputOutput(cvInputOutput),
    _modeSwitchPin(modeSwitchPin) {
      _calibrationMode = false;
}

void AbstractInputTask::init() {
    Task::init();
    pinMode(_modeSwitchPin, INPUT_PULLUP);
    digitalWrite(_modeSwitchPin, HIGH);
    if(digitalRead(_modeSwitchPin) == LOW) {
        Serial.println("Calibration Mode Started.");
        _calibrationMode = true;
    }
}

void AbstractInputTask::execute() {
}
