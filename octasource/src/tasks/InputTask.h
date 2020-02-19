#ifndef InputTask_h
#define InputTask_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvInputOutput.h"


class InputTask : public Task {

public:
    InputTask(CvInputOutput& cvInputOutput);
    void init();
    void execute();

private:
    CvInputOutput& _cvInputOutput;


};

#endif
