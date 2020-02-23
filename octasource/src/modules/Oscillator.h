#ifndef Oscillator_h
#define Oscillator_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvInputOutput.h"
#include "../waveforms/RampWave.h"
#include "../waveforms/TriangleWave.h"
#include "../waveforms/SineWave.h"


class Oscillator {

public:
    Oscillator();
    float execute(unsigned long timeDiff);

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float amplitude);
    void setPosition(float position);

private:
    float _frequencyHz;
    float _amplitude;
    float _position;

    RampWave _rampWave;
    TriangleWave _triangleWave;
    SineWave _sineWave;
};

#endif
