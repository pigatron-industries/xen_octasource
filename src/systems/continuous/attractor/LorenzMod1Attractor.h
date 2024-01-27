#ifndef LorenzMod1Attractor_h
#define LorenzMod1Attractor_h

#include "../ContinuousSystem.h"

class LorenzMod1Attractor : public ContinuousSystemN<3> {
    public:
        void init(float sampleRate) {
            ContinuousSystemN::init(sampleRate);
            pos = {1, 1, 1};
            mult = {0.1, 0.1, 0.1};
            offset = {0, 0, 0};
            speedMult = 1;
            initParams(
                {0.1, 4, 14, 0.08}, 
                {0.1, 4, 14, 0.086}
            );
        }

        const char* getName() { return "LORENZMOD1"; }

        void system() {
            DX = -PA*PX + PY*PY - PZ*PZ + PA*PC;
            DY = PX*(PY - PB*PZ) + PD;
            DZ = PZ + PX*(PB*PY + PZ);
        }
};

#endif
