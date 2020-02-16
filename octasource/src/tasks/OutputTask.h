#ifndef OutputTask_h
#define OutputTask_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvInputOutput.h"
#include "../waveforms/RampWave.h"
#include "../modules/Oscillator.h"


class OutputTask : public Task {

public:
    OutputTask(CvInputOutput& cvInputOutput);
    void init();
    void execute();

private:
    CvInputOutput& _cvInputOutput;
    Oscillator _oscillator1;


};

#endif
