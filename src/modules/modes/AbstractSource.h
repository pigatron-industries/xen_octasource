#ifndef AbstractSource_h
#define AbstractSource_h

#include <inttypes.h>
#include "../generators/Oscillator.h"

#define OSCILLATOR_COUNT 8


class AbstractSource {

public:
    virtual void execute(unsigned long timeDiff);
    float getOutput(uint8_t index);
    bool getTriggerOut();

    virtual void init();
    virtual long setMode(long movement);
    virtual void setFrequencyHz(float frequencyHz);
    virtual void setAmplitude(float amplitude);
    virtual void setWave(float wave);
    virtual void setPosition(float position);
    virtual void setTriggerValue(float value);
    virtual void trigger();

    float getFrequencyHz();
    float getPosition();
    long getMode() { return _mode; }

protected:
    Oscillator _oscillators[OSCILLATOR_COUNT];
    float _outputs[OSCILLATOR_COUNT];
    long _mode = 0;
    long _modeCount = 1;

};

#endif
