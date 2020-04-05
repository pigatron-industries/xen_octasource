#ifndef AbstractSource_h
#define AbstractSource_h

#include <inttypes.h>
#include "../generators/Oscillator.h"

#define OSCILLATOR_COUNT 8


class AbstractSource {

public:
    void execute(unsigned long timeDiff);
    float getOutput(uint8_t index);

    virtual void init();
    virtual void setFrequencyHz(float frequencyHz);
    virtual void setAmplitude(float amplitude);
    virtual void setWave(float wave);
    virtual void trigger();

protected:
    Oscillator _oscillators[OSCILLATOR_COUNT];
    float _outputs[OSCILLATOR_COUNT];

};

#endif
