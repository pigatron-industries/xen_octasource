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
        }

        void system() {
            delta[X] = a*pos[X] + pos[Y]*pos[Z];
            delta[Y] = b*pos[X] + c*pos[Y] - pos[X]*pos[Z];
            delta[Z] = - pos[Z] - pos[X]*pos[Y];
        }

    private:
        float a = 0.2;
        float b = 0.01;
        float c = -0.4;
};

#endif
