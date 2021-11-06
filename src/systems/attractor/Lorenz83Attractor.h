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
        }

        void system() {
            delta[X] = - a*pos[X] - pos[Y]*pos[Y] - pos[Z]*pos[Z] + a*f;
            delta[Y] = - pos[Y] + pos[X]*pos[Y] - b*pos[X]*pos[Z] + g;
            delta[Z] = - pos[Z] + b*pos[X]*pos[Y] + pos[X]*pos[Z];
        }

    private:
        float a = 0.95;
        float b = 7.91;
        float f = 4.83;
        float g = 4.66;
};

#endif
