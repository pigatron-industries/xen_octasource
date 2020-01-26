#ifndef OutputUpdateTask_h
#define OutputUpdateTask_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvInputOutput.h"


class OutputUpdateTask : public Task {

public:
    OutputUpdateTask(CvInputOutput& cvInputOutput);
    void init();
    void execute();

    void trigger(uint8_t index);
    void sendData();

private:
    CvInputOutput& _cvInputOutput;

};

#endif
