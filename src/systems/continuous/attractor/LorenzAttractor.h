#ifndef LorenzAttractor_h
#define LorenzAttractor_h

#include "../ContinuousSystem.h"

class LorenzAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0;
            pos[Z] = 0;
            mult[X] = 0.2;
            mult[Y] = 0.2;
            mult[Z] = 0.2;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = -25;
            speedMult = 1;
            initParams(
                {10, 8.0/3.0, 28}, 
                {10, 8.0/3.0, 28}
            );
        }

        const char* getName() { return "LORENZ"; }

        void system() {
            delta[0] = PA*(pos[Y]-pos[X]);
            delta[1] = pos[X]*(PC-pos[Z]) - pos[Y];
            delta[2] = pos[X]*pos[Y] - PB*pos[Z];
        }
};

#endif
