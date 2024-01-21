#ifndef NoseHooverAttractor_h
#define NoseHooverAttractor_h

#include "../ContinuousSystem.h"

class NoseHooverAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0;
            pos[Z] = 0;
            mult[X] = 1;
            mult[Y] = 1;
            mult[Z] = 1;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = 0;
            speedMult = 2;
            initParams(
                {1.5}, 
                {1.5}
            );
        }

        const char* getName() { return "NOSEHOOVER"; }

        void system() {
            delta[X] = pos[Y];
            delta[Y] = pos[Z]*pos[Y] - pos[X];
            delta[Z] = PA - pos[Y]*pos[Y];
        }

};

#endif
