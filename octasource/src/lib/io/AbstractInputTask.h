#ifndef AbstractInputTask_h
#define AbstractInputTask_h

#include <inttypes.h>

#include "../task/Task.h"
#include "../../drivers/CvInputOutput.h"
#include "PotCalibration.h"

class AbstractInputTask : public Task {

public:
    AbstractInputTask(CvInputOutput& cvInputOutput, uint8_t modeSwitchPin, uint8_t potCalibrationsSize);
    void init();
    void execute();

protected:
    CvInputOutput& _cvInputOutput;

    PotCalibration* _potCalibrations;
    uint8_t _potCalibrationsSize;

    bool _calibrationMode;
    uint8_t _modeSwitchPin;


};

#endif
