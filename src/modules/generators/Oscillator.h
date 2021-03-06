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
    void reset();

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float amplitude);
    void setWave(float wave);
    void setPosition(float position);
    void setCycle(bool cycle);

    float getVoltage() {
        return _voltage;
    }

    bool getTriggerOut() {
        return _trigger;
    }

    float getFrequencyHz() {
        return _frequencyHz;
    }

    float getPosition() {
        return _position;
    }

private:
    // controls
    float _frequencyHz;
    float _amplitude;
    float _wave;
    float _position;

    bool _cycle;
    bool _triggered;

    // outputs
    float _voltage;
    bool _trigger;

    // waves
    RampWave _rampWave;
    TriangleWave _triangleWave;
    SineWave _sineWave;
    SquareWave _squareWave;


    void updatePosition(unsigned long timeDiff);
};

#endif
