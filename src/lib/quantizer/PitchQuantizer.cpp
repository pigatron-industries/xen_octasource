#include "PitchQuantizer.h"

bool PitchQuantizer::quantize(float value) {
    int octave = scale->findOctave(value);
    Note prevNote = scale->getNote(octave, 0);
    Note nextNote;

    for(int i = 1; i <= scale->getNotes(); i++) {
        nextNote = scale->getNote(octave, i);
        if(scale->isEnabled(nextNote)) {
            if(nextNote.value > value) {
                return setNote(getClosestNote(value, prevNote, nextNote));
            }
            prevNote = nextNote;
        }
    }
    
    nextNote = scale->getNote(octave+1, 0);
    return setNote(getClosestNote(value, prevNote, nextNote));
}

Note& PitchQuantizer::getClosestNote(float value, Note& prevNote, Note& nextNote) {
    if((nextNote.value - value) < (value - prevNote.value)) {
        return nextNote;
    } else {
        return prevNote;
    }
}

bool PitchQuantizer::setNote(Note& note) {
    if(this->note.note != note.note || this->note.octave != note.octave) {
        this->note = note;
        return true;
    }
    return false;
}
