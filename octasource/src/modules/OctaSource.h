#ifndef OctaSource_h
#define OctaSource_h

#include <inttypes.h>

#include "Oscillator.h"

#define OSCILLATOR_COUNT 8

class OctaSource {

public:
    OctaSource();
    void execute(unsigned long timeDiff);
    float getOutput(uint8_t index);

    void setFrequencyHz(float frequencyHz);

private:
    Oscillator _oscillators[OSCILLATOR_COUNT];
    float _outputs[OSCILLATOR_COUNT];

};

#endif
