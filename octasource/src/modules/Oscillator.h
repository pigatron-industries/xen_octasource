#ifndef Oscillator_h
#define Oscillator_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvInputOutput.h"
#include "../waveforms/RampWave.h"


class Oscillator {

public:
    Oscillator();
    float execute(unsigned long timeDiff);

    void setFrequencyHz(float frequencyHz);

private:
    float _frequencyHz;
    float _position;

    RampWave _rampWave;
};

#endif
