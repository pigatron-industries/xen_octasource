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
            initParams(
                {3, 2.7, 1.7, 2, 9}, 
                {3, 2.7, 1.7, 2, 9}
            );
        }

        const char* getName() { return "DADRAS"; }

        void system() {
            delta[X] = pos[Y] - PA*pos[X] + PB*pos[Y]*pos[Z];
            delta[Y] = PC*pos[Y] - pos[X]*pos[Z] + pos[Z];
            delta[Z] = PD*pos[X]*pos[Y] - PE*pos[Z];
        }
};

#endif
