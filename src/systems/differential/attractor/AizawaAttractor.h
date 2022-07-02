#ifndef AizawaAttractor_h
#define AizawaAttractor_h

#include "../ContinuousSystem.h"
#include <math.h>

class AizawaAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0;
            pos[Z] = 0;
            mult[X] = 2.75;
            mult[Y] = 2.75;
            mult[Z] = 3.75;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = -0.75;
            speedMult = 1;
        }

        const char* getName() { return "AIZAWA"; }

        void system() {
            delta[X] = pos[X]*(pos[Z]-b) - d*pos[Y];
            delta[Y] = d*pos[X] + pos[Y]*(pos[Z]-b);
            delta[Z] = c + a*pos[Z] - (pos[Z]*pos[Z]*pos[Z]/3) - (pos[X]*pos[X]+pos[Y]*pos[Y])*(1+e*pos[Z]) + f*pos[Z]*pos[X]*pos[X]*pos[X];
        }

    private:
        float a = 0.95;
        float b = 0.7;
        float c = 0.6;
        float d = 3.5;
        float e = 0.25;
        float f = 0.1;
};

#endif
