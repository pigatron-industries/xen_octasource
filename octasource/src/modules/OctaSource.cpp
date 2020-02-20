#include "OctaSource.h"

#include <Arduino.h>

#define AMP_SCALE 5

OctaSource::OctaSource() {
}

void OctaSource::setFrequencyHz(float frequencyHz) {
    _oscillator1.setFrequencyHz(frequencyHz);
}

void OctaSource::execute(unsigned long timeDiff) {
    _oscillator1.execute(timeDiff);
}
