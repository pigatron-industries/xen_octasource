#include "OutputTask.h"

#include <Arduino.h>

OutputTask::OutputTask(CvInputOutput& cvInputOutput, OctaSource& octasource) :
    _cvInputOutput(cvInputOutput),
    _octasource(octasource) {
}

void OutputTask::init() {
    Task::init();
    for(uint8_t i = 0; i < OSCILLATOR_COUNT; i++) {
        _cvInputOutput.setPinModeAnalogOut(OUTPUT_PIN_START+i);
    }
}

void OutputTask::execute() {
    if(lastExecutionDiff > 100000 || lastExecutionDiff < 0) {
        return;
    }

    _octasource.execute(lastExecutionDiff);

    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        float voltage = _octasource.getOutput(i);
        _cvInputOutput.setVoltage(OUTPUT_PIN_START+i, voltage);
    }
}
