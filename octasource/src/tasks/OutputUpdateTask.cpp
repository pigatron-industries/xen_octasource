#include "OutputUpdateTask.h"

#include <Arduino.h>


OutputUpdateTask::OutputUpdateTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
}

void OutputUpdateTask::init() {
    Task::init();
}

void OutputUpdateTask::execute() {
    //while(true) {
        _cvInputOutput.setVoltage(0, 0);
        _cvInputOutput.setVoltage(0, 5);
    //  }
}
