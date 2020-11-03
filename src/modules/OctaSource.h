#ifndef OctaSource_h
#define OctaSource_h

#include <inttypes.h>

#include "generators/Oscillator.h"
#include "modes/AbstractSource.h"

#define MODE_COUNT 6


class OctaSource {

public:
    OctaSource();
    uint8_t cycleMode();
    void setMode(uint8_t mode);
    uint8_t cycleSubMode(long movement);
    void setSubMode(uint8_t submode);

    void execute(unsigned long timeDiff);

    float getOutput(uint8_t index);
    bool getTriggerOut();

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float amplitude);
    void setWave(float wave);
    void setPosition(float position);
    void setTriggerValue(float value);
    void trigger();

    float getFrequencyHz();
    float getPosition();

    uint8_t getMode() { return _mode; }
    long getSubMode();

private:

    AbstractSource* _source[MODE_COUNT];
    uint8_t _mode;

    void initMode();

};

#endif
