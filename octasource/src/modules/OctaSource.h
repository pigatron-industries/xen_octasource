#ifndef OctaSource_h
#define OctaSource_h

#include <inttypes.h>

#include "Oscillator.h"


class OctaSource {

public:
    OctaSource();
    void execute(unsigned long timeDiff);

    void setFrequencyHz(float frequencyHz);

private:
    Oscillator _oscillator1;

    //TODO add more oscillators

};

#endif
