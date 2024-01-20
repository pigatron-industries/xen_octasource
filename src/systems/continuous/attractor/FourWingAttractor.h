#ifndef FourWingAttractor_h
#define FourWingAttractor_h

#include "../ContinuousSystem.h"

class FourWingAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0;
            pos[Z] = 0;
            mult[X] = 2;
            mult[Y] = 2;
            mult[Z] = 2;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = 0;
            speedMult = 4;
            initParams(
                {0.2, 0.01, -0.4}, 
                {0.2, 0.01, -0.4}
            );
        }

        const char* getName() { return "FOUR WING"; }

        void system() {
            delta[X] = PA*pos[X] + pos[Y]*pos[Z];
            delta[Y] = PB*pos[X] + PC*pos[Y] - pos[X]*pos[Z];
            delta[Z] = - pos[Z] - pos[X]*pos[Y];
        }

};

#endif
