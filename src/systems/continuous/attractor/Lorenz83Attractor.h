#ifndef Lorenz83Attractor_h
#define Lorenz83Attractor_h

#include "../ContinuousSystem.h"

class Lorenz83Attractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0.1;
            pos[Z] = 0.1;
            mult[X] = 1.8;
            mult[Y] = 1.5;
            mult[Z] = 1.5;
            offset[X] = -0.75;
            offset[Y] = -0.25;
            offset[Z] = -0.25;
            speedMult = 1;
            initParams(
                {0.95, 7.91, 4.83, 4.66}, 
                {0.95, 7.91, 4.83, 4.66}
            );
        }

        const char* getName() { return "LORENZ83"; }

        void system() {
            delta[X] = - PA*pos[X] - pos[Y]*pos[Y] - pos[Z]*pos[Z] + PA*PC;
            delta[Y] = - pos[Y] + pos[X]*pos[Y] - PB*pos[X]*pos[Z] + PD;
            delta[Z] = - pos[Z] + PB*pos[X]*pos[Y] + pos[X]*pos[Z];
        }
};

#endif
