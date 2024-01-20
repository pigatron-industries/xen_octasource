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
            initParams(
                {1.3, 0.11, 0, 10.82, 14.286}, 
                {1.3, 0.11, 0, 10.82, 14.286}
            );
        }

        const char* getName() { return "MULTI SCROLL"; }

        void system() {
            float h = -PB*sinf((M_PI*pos[X])/(2*PA) + PC);
            delta[X] = PD*(pos[Y]-h);
            delta[Y] = pos[X] - pos[Y] + pos[Z];
            delta[Z] = -PE*pos[Y];
        }
};

#endif
