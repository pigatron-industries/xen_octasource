#ifndef ChenAttractor_h
#define ChenAttractor_h

#include "../ContinuousSystem.h"
#include <math.h>

class ChenAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0.1;
            pos[Z] = 0.1;
            mult[X] = 0.25;
            mult[Y] = 0.3;
            mult[Z] = 0.8;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = -9.5;
            speedMult = 1.5; //Breaks if it goes too fast
            initParams(
                {5, -10, -0.38}, 
                {5, -10, -0.38}
            );
        }

        const char* getName() { return "CHEN"; }

        void system() {
            delta[X] = PA*pos[X] - pos[Y]*pos[Z];
            delta[Y] = PB*pos[Y] + pos[X]*pos[Z];
            delta[Z] = PC*pos[Z] + pos[X]*pos[Y]/3;
        }

};

#endif
