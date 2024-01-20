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
            initParams(
                {40, 1.833, 55, 0.16, 0.65, 20}, 
                {40, 1.833, 55, 0.16, 0.65, 20}
            );
        }

        const char* getName() { return "THREE SCROLL"; }

        void system() {
            delta[X] = PA*(pos[Y] - pos[X]) + PD*pos[X]*pos[Z];
            delta[Y] = PC*pos[X] - pos[X]*pos[Z] + PF*pos[Y];
            delta[Z] = PB*pos[Z] + pos[X]*pos[Y] - PE*pos[X]*pos[X];
        }
};

#endif
