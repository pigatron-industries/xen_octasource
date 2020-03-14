#ifndef AbstractInputTask_h
#define AbstractInputTask_h

#include <inttypes.h>

#include "Task.h"
#include "../../drivers/CvInputOutput.h"


class AbstractInputTask : public Task {

public:
    AbstractInputTask(CvInputOutput& cvInputOutput, uint8_t modeSwitchPin);
    void init();
    void execute();

protected:
    CvInputOutput& _cvInputOutput;

    bool _calibrationMode;
    uint8_t _modeSwitchPin;

};

#endif
