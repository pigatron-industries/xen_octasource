#ifndef ThreeScrollUnifiedAttractor_h
#define ThreeScrollUnifiedAttractor_h

#include "../ContinuousSystem.h"

class ThreeScrollUnifiedAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = -0.29;
            pos[Y] = -0.25;
            pos[Z] = -0.59;
            mult[X] = 0.025;
            mult[Y] = 0.02;
            mult[Z] = 0.025;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = -90;
            speedMult = 0.25;
        }

        void system() {
            delta[X] = a*(pos[Y] - pos[X]) + d*pos[X]*pos[Z];
            delta[Y] = c*pos[X] - pos[X]*pos[Z] + f*pos[Y];
            delta[Z] = b*pos[Z] + pos[X]*pos[Y] - e*pos[X]*pos[X];
        }

    private:
        float a = 40;
        float d = 0.16;
        float c = 55;
        float f = 20;
        float b = 1.833;
        float e = 0.65;
        
};

#endif
