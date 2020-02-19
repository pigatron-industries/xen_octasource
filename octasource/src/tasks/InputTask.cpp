#include "InputTask.h"

#include <Arduino.h>

InputTask::InputTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
}

void InputTask::init() {
    Task::init();
}

void InputTask::execute() {
}
