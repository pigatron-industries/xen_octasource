#ifndef HalvorsenAttractor_h
#define HalvorsenAttractor_h

#include "ContinuousSystem.h"

class HalvorsenAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0.1;
            pos[Z] = 0.1;
            mult[X] = 0.4;
            mult[Y] = 0.5;
            mult[Z] = 0.5;
            offset[X] = 2.75;
            offset[Y] = 3;
            offset[Z] = 2.75;
            speedMult = 1;
        }

        void system() {
            delta[X] = -a*pos[X] - 4*pos[Y] - 4*pos[Z] - pos[Y]*pos[Y];
            delta[Y] = -a*pos[Y] - 4*pos[Z] - 4*pos[X] - pos[Z]*pos[Z];
            delta[Z] = -a*pos[Z] - 4*pos[X] - 4*pos[Y] - pos[X]*pos[X];
        }

    private:
        float a = 1.4;
};

#endif
