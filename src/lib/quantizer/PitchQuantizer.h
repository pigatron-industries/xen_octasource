#ifndef PitchQuantizer_h
#define PitchQuantizer_h

#include "Scale.h"

class PitchQuantizer {
    public:
        PitchQuantizer(Scale& scale) { this->scale = &scale; }
        void setScale(Scale& scale) { this->scale = &scale; }
        float quantize(float value);
        float getNoteValue(int octave, int note);


    private:
        Scale* scale;
        
};

#endif
