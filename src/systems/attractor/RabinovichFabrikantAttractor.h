#ifndef RabinovichFabrikantAttractor_h
#define RabinovichFabrikantAttractor_h

#include "../ContinuousSystem.h"

class RabinovichFabrikantAttractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos[X] = 0.1;
            pos[Y] = 0.1;
            pos[Z] = 0.1;
            mult[X] = 1.75;
            mult[Y] = 1.75;
            mult[Z] = 6;
            offset[X] = 0;
            offset[Y] = 0;
            offset[Z] = -0.5; //-0.75;
            speedMult = 2;
        }

        const char* getName() { return "RABINOVICH"; }

        void system() {
            delta[X] = pos[Y]*(pos[Z]-1+pos[X]*pos[X]) + b*pos[X];
            delta[Y] = pos[X]*(3*pos[Z]+1-pos[X]*pos[X]) + b*pos[Y];
            delta[Z] = - 2*pos[Z]*(a + pos[X]*pos[Y]);
        }

    private:
        float a = 0.98; //0.14;
        float b = 0.10;
};

#endif
