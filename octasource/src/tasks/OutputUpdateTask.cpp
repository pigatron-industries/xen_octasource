#include "OutputUpdateTask.h"

#include <Arduino.h>

#define AMP_SCALE 5

OutputUpdateTask::OutputUpdateTask(CvInputOutput& cvInputOutput) :
    _cvInputOutput(cvInputOutput) {
      position = 0;
}

void OutputUpdateTask::init() {
    Task::init();
}

void OutputUpdateTask::execute() {

    // update position
    position += (lastExecutionDiff * 100); //100Hz
    if(position > MAX_POSITION) {
        position -= MAX_POSITION;
    }

    
    float value = _rampWave.getValue(position);

    float voltage = value / MAX_POSITION*AMP_SCALE;
    _cvInputOutput.setVoltage(0, voltage);
}
