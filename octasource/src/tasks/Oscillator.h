#ifndef Oscillator_h
#define Oscillator_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvInputOutput.h"
#include "../waveforms/RampWave.h"


class Oscillator : public Task {

public:
    Oscillator(CvInputOutput& cvInputOutput);
    void init();
    void execute();

    void setFrequencyHz(float frequencyHz);

private:
    CvInputOutput& _cvInputOutput;
    float _frequencyHz;

    RampWave _rampWave;

    float position;

};

#endif
