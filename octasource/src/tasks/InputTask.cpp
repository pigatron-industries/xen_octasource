#include "InputTask.h"

#include <Arduino.h>

InputTask::InputTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
}

void InputTask::init() {
    Task::init();
    _cvInputOutput.setPinModeAnalogIn(0);
    _cvInputOutput.setPinModeAnalogIn(1);
    _cvInputOutput.setPinModeAnalogIn(2);
    _cvInputOutput.setPinModeAnalogIn(3);
    _cvInputOutput.setPinModeAnalogIn(4);
    _cvInputOutput.setPinModeAnalogIn(5);
    _cvInputOutput.setPinModeAnalogIn(6);
    _cvInputOutput.setPinModeAnalogIn(7);
}

void InputTask::execute() {
}
