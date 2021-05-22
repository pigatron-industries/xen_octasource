#ifndef AbstractInputTask_h
#define AbstractInputTask_h

#include <inttypes.h>

#include "../task/Task.h"
#include "../../Hardware.h"
#include "PotCalibration.h"
#include "GateInput.h"

class AbstractInputTask : public Task {

public:
    AbstractInputTask();
    void setPotCalibration(uint8_t modeSwitchPin, uint8_t potCalibrationSize, uint8_t displayLedPin);
    void init();

    float getValue(uint8_t pin);
    float getCalibratedValue(uint8_t pin);

protected:
    PotCalibration* _potCalibration;
    uint8_t _potCalibrationSize;

    uint8_t _calibrationMode;
    uint8_t _modeSwitchPin;
    uint8_t _displayLedPin;

private:
    void doCalibrationSequence();

};

#endif
