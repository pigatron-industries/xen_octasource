#ifndef HadleyAttractor_h
#define HadleyAttractor_h

#include "../ContinuousSystem.h"

class HadleyAttractor : public ContinuousSystemN<3> {
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
            speedMult = 2;
            initParams(
                {0.25, 4, 8, 1}, 
                {0.25, 4, 8, 1}
            );
        }

        const char* getName() { return "HADLEY"; }

        void system() {
            // Serial.println(PB);
            float xy = pos[X]*pos[Y];
            float xz = pos[X]*pos[Z];
            delta[X] = -pos[Y]*pos[Y] - pos[Z]*pos[Z] - PA*pos[X] + PA*PC;
            delta[Y] = xy - PB*xz - pos[Y] + PD;
            delta[Z] = PB*xy + xz - pos[Z];
        }

};

#endif
