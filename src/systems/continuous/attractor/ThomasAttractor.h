#ifndef ThomasAttractor_h
#define ThomasAttractor_h

#include "../ContinuousSystem.h"
#include <math.h>

class ThomasAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0;
            pos[Z] = 0;
            mult[X] = 1.75;
            mult[Y] = 1.75;
            mult[Z] = 1.75;
            offset[X] = -1.5;
            offset[Y] = -1.5;
            offset[Z] = -1.5;
            speedMult = 4;
            initParams(
                {0.208186}, 
                {0.208186}
            );
        }

        const char* getName() { return "THOMAS"; }

        void system() {
            delta[X] = sinf(pos[Y])-PB*pos[X];
            delta[Y] = sinf(pos[Z])-PB*pos[Y];
            delta[Z] = sinf(pos[X])-PB*pos[Z];
        }

};

#endif
