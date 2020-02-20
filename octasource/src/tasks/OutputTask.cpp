#include "OutputTask.h"

#include <Arduino.h>

OutputTask::OutputTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
}

void OutputTask::init() {
    Task::init();
    for(uint8_t i = 0; i < OUTPUT_PINS; i++) {
        _cvInputOutput.setPinModeAnalogOut(OUTPUT_PIN_START+i);
    }
}

void OutputTask::execute() {
    float voltage = _oscillator1.execute(lastExecutionDiff);
    _cvInputOutput.setVoltage(12, voltage);
}
