#ifndef Chua9ScrollAttractor_h
#define Chua9ScrollAttractor_h

#include "../ContinuousSystem.h"
#include <math.h>

class ChuaMultiScrollAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0;
            pos[Z] = 0;
            mult[X] = 0.2;
            mult[Y] = 8;
            mult[Z] = 0.2;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = 0;
            speedMult = 2;
            limits[X] = 20;
        }

        void system() {
            float h = -b*sinf((M_PI*pos[X])/(2*a) + d);
            delta[X] = alpha*(pos[Y]-h);
            delta[Y] = pos[X] - pos[Y] + pos[Z];
            delta[Z] = -beta*pos[Y];
        }


    private:
        float alpha = 10.82;
        float beta = 14.286;
        float a = 1.3;
        float b = 0.11;
        float c = 7;
        float d = 0;
};

#endif
