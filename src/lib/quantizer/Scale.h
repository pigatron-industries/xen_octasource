#ifndef Scale_h
#define Scale_h

#include <eurorack.h>

class Scale {
    public:

        Scale() {}
        Scale(int notes) {
            float interval = 1.0 / notes;
            for(int i = 0; i < notes; i++) {
                intervals.add(interval*i);
            }
        }

        int getNotes() { return intervals.size(); }

        float getNoteValue(int octave, int note) {
            return octave + (note > 0 ? intervals[note-1] : 0);
        }

    private:
        Array<float, 24> intervals;
        

};

#endif
