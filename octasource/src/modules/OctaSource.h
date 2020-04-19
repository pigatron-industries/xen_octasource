#ifndef OctaSource_h
#define OctaSource_h

#include <inttypes.h>

#include "generators/Oscillator.h"
#include "modes/AbstractSource.h"

#define MODE_COUNT 5


class OctaSource {

public:
    OctaSource();
    void cycleMode();

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

    uint8_t getMode() {
        return _mode;
    }

private:

    AbstractSource* _source[MODE_COUNT];
    uint8_t _mode;

    void initMode();

};

#endif
