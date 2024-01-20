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
            initParams(
                {0.95, 0.7, 0.6, 3.5, 0.25, 0.1}, 
                {0.95, 0.7, 0.6, 3.5, 0.25, 0.1}
            );
        }

        const char* getName() { return "AIZAWA"; }

        void system() {
            delta[X] = pos[X]*(pos[Z]-PB) - PD*pos[Y];
            delta[Y] = PD*pos[X] + pos[Y]*(pos[Z]-PB);
            delta[Z] = PC + PA*pos[Z] - (pos[Z]*pos[Z]*pos[Z]/3) - (pos[X]*pos[X]+pos[Y]*pos[Y])*(1+PE*pos[Z]) + PF*pos[Z]*pos[X]*pos[X]*pos[X];
        }

};

#endif
