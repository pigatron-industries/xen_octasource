#ifndef OutputTask_h
#define OutputTask_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvInputOutput.h"
#include "../waveforms/RampWave.h"
#include "../modules/OctaSource.h"

#define OUTPUT_PIN_START 12

class OutputTask : public Task {

public:
    OutputTask(CvInputOutput& cvInputOutput, OctaSource& octasource);
    void init();
    void execute();

private:
    CvInputOutput& _cvInputOutput;
    OctaSource& _octasource;

};

#endif
