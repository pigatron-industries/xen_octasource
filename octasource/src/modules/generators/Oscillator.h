#ifndef Oscillator_h
#define Oscillator_h

#include <inttypes.h>

#include "waveforms/RampWave.h"
#include "waveforms/TriangleWave.h"
#include "waveforms/SineWave.h"
#include "waveforms/SquareWave.h"


class Oscillator {

public:
    Oscillator();
    float execute(unsigned long timeDiff);

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float amplitude);
    void setWave(float wave);
    void setPosition(float position);
    void setCycle(bool cycle);

private:
    float _frequencyHz;
    float _amplitude;
    float _wave;
    float _position;

    bool _cycle;

    RampWave _rampWave;
    TriangleWave _triangleWave;
    SineWave _sineWave;
    SquareWave _squareWave;


    void updatePosition(unsigned long timeDiff);
};

#endif
