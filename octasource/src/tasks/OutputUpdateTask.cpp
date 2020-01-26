#include "OutputUpdateTask.h"

#include <Arduino.h>


OutputUpdateTask::OutputUpdateTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
      position = 0;
      samples = 0;
}

void OutputUpdateTask::init() {
    Task::init();
}

void OutputUpdateTask::execute() {

    // update position
    position += (lastExecutionDiff * 100); //100Hz
    if(position > 1000000) {
        position -= 1000000;
        samples = 0;
        return;
    }

    //RampWave
    float value = (position - 500000) / 100000;

    samples += 1;
    _cvInputOutput.setVoltage(0, value);
}
