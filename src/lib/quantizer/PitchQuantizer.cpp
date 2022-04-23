#include "PitchQuantizer.h"

float PitchQuantizer::quantize(float value) {
    int octave = floorf(value);
    float prevValue = octave;
    for(int i = 1; i <= scale->getNotes(); i++) {
        float nextValue = getNoteValue(octave, i);
        if(nextValue > value) {
            return ((nextValue - value) < (value - prevValue)) ? nextValue : prevValue;
        }
        prevValue = nextValue;
    }
    return prevValue;
}

float PitchQuantizer::getNoteValue(int octave, int note) {
    return scale->getNoteValue(octave, note);
}