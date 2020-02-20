#include "OutputTask.h"

#include <Arduino.h>

#define AMP_SCALE 5

OutputTask::OutputTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
}

void OutputTask::init() {
    Task::init();
    _cvInputOutput->setPinModeAnalogOut(12);
    _cvInputOutput->setPinModeAnalogOut(13);
    _cvInputOutput->setPinModeAnalogOut(14);
    _cvInputOutput->setPinModeAnalogOut(15);
    _cvInputOutput->setPinModeAnalogOut(16);
    _cvInputOutput->setPinModeAnalogOut(17);
    _cvInputOutput->setPinModeAnalogOut(18);
    _cvInputOutput->setPinModeAnalogOut(19);
}

void OutputTask::execute() {
    float voltage = _oscillator1.execute(lastExecutionDiff);
    _cvInputOutput.setVoltage(12, voltage);
}
