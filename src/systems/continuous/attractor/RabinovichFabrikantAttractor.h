#ifndef RabinovichFabrikantAttractor_h
#define RabinovichFabrikantAttractor_h

#include "../ContinuousSystem.h"

class RabinovichFabrikantAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0.1;
            pos[Z] = 0.1;
            mult[X] = 1.75;
            mult[Y] = 1.75;
            mult[Z] = 6;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = -0.5; //-0.75;
            speedMult = 4;
            initParams(
                {0.98, 0.1}, 
                {0.98, 0.1}
            );
        }

        const char* getName() { return "RABINOVICH"; }

        void system() {
            delta[X] = pos[Y]*(pos[Z]-1+pos[X]*pos[X]) + PB*pos[X];
            delta[Y] = pos[X]*(3*pos[Z]+1-pos[X]*pos[X]) + PB*pos[Y];
            delta[Z] = - 2*pos[Z]*(PA + pos[X]*pos[Y]);
        }
};

#endif
