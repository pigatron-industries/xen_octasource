#ifndef DadrasAttractor_h
#define DadrasAttractor_h

#include "../ContinuousSystem.h"
#include <math.h>

class DadrasAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0.1;
            pos[Z] = 0.1;
            mult[X] = 0.25;
            mult[Y] = 0.4;
            mult[Z] = 0.35;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = 0;
            speedMult = 1;
        }

        const char* getName() { return "DADRAS"; }

        void system() {
            delta[X] = pos[Y] - a*pos[X] + b*pos[Y]*pos[Z];
            delta[Y] = c*pos[Y] - pos[X]*pos[Z] + pos[Z];
            delta[Z] = d*pos[X]*pos[Y] - e*pos[Z];
        }

    private:
        float a = 3;
        float b = 2.7;
        float c = 1.7;
        float d = 2;
        float e = 9;
};

#endif
