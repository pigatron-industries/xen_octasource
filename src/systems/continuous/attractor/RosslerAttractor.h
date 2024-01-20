#ifndef RosslerAttractor_h
#define RosslerAttractor_h

#include "../ContinuousSystem.h"

class RosslerAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0;
            pos[Z] = 0;
            mult[X] = 0.4;
            mult[Y] = 0.5;
            mult[Z] = 0.4;
            offset[X] = -1;
            offset[Y] = 1.5;
            offset[Z] = -11;
            speedMult = 2;
            initParams(
                {0.2, 0.2, 5.7}, 
                {0.2, 0.2, 5.7}
            );
        }

        const char* getName() { return "ROSSLER"; }

        void system() {
            delta[X] = -(pos[Y]+pos[Z]);
            delta[Y] = pos[X] + PA*pos[Y];
            delta[Z] = PB + pos[Z]*(pos[X]-PC);
        }
};

#endif
