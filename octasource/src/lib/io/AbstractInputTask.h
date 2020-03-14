#ifndef AbstractInputTask_h
#define AbstractInputTask_h

#include <inttypes.h>

#include "../task/Task.h"
#include "../../drivers/CvInputOutput.h"
#include "PotCalibration.h"

class AbstractInputTask : public Task {

public:
    AbstractInputTask(CvInputOutput& cvInputOutput);
    void setPotCalibration(uint8_t modeSwitchPin, uint8_t* potCalibrationPins, uint8_t potCalibrationSize);
    void init();

    float getCalibratedValue(uint8_t pin);

protected:
    CvInputOutput& _cvInputOutput;

    PotCalibration* _potCalibration;
    uint8_t _potCalibrationSize;

    uint8_t _calibrationMode;
    uint8_t _modeSwitchPin;

private:
    void doCalibrationSequence();

};

#endif
