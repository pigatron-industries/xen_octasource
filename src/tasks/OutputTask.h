#ifndef OutputTask_h
#define OutputTask_h

#include <inttypes.h>

#include "../lib/task/Task.h"
#include "../lib/io/Timer.h"
#include "../drivers/CvInputOutput.h"
#include "../modules/OctaSource.h"

class OutputTask : public Task {

public:
    OutputTask(CvInputOutput& cvInputOutput, OctaSource& octasource);
    void init();
    void execute();

private:
    CvInputOutput& _cvInputOutput;
    OctaSource& _octasource;

    Timer _triggerTimer;

};

#endif
