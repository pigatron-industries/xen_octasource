#ifndef PitchQuantizer_h
#define PitchQuantizer_h

#include "Scale.h"

class PitchQuantizer {
    public:
        PitchQuantizer(Scale& scale) { this->scale = &scale; }
        void setScale(Scale& scale) { this->scale = &scale; }
        bool quantize(float value);

        Note& getNote() { return note; }

    private:
        Scale* scale;
        Note note;
        
        bool setNote(Note& note);
        Note& getClosestNote(float value, Note& prevNote, Note& nextNote);
};

#endif
