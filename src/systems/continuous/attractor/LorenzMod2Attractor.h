#ifndef LorenzMod2Attractor_h
#define LorenzMod2Attractor_h

#include "../ContinuousSystem.h"

class LorenzMod2Attractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos = {0.1, 0, 0};
            mult = {0.3, 0.3, 0.3};
            offset = {0, 0, 0};
            speedMult = 1;
            initParams(
                {0.9, 5, 9.9, 1}, 
                {0.9, 5, 9.9, 1}
            );
        }

        const char* getName() { return "LORENZMOD2"; }

        void system() {
            DX = -PA*PX + PY*PY - PZ*PZ + PA*PC;
            DY = PX*(PY - PB*PZ) + PD;
            DZ = -PZ + PX*(PB*PY + PZ);
        }
};

#endif
