#include "OutputTask.h"

#include <Arduino.h>

OutputTask::OutputTask(CvInputOutput& cvInputOutput, OctaSource& octasource) :
    _cvInputOutput(cvInputOutput),
    _octasource(octasource) {
}

void OutputTask::init() {
    Task::init();
    for(uint8_t i = 0; i < OUTPUT_PINS; i++) {
        _cvInputOutput.setPinModeAnalogOut(OUTPUT_PIN_START+i);
    }
}

void OutputTask::execute() {
    _octasource.execute(lastExecutionDiff);
    float voltage = _octasource.getOutput(0);

    _cvInputOutput.setVoltage(12, voltage);
}
