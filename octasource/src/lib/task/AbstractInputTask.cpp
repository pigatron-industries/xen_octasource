#include "AbstractInputTask.h"

#include <Arduino.h>

AbstractInputTask::AbstractInputTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
      _calibrationMode = false;
}

void AbstractInputTask::init() {
    Task::init();
}

void AbstractInputTask::execute() {
}
