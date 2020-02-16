#include "OutputTask.h"

#include <Arduino.h>

#define AMP_SCALE 5

OutputTask::OutputTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
}

void OutputTask::init() {
    Task::init();
}

void OutputTask::execute() {
    float voltage = _oscillator1.execute(lastExecutionDiff);
    _cvInputOutput.setVoltage(12, voltage);
}
