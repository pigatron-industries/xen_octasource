#ifndef ThreeScrollUnifiedAttractor_h
#define ThreeScrollUnifiedAttractor_h

#include "Attractor.h"

class ThreeScrollUnifiedAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = -0.29;
            pos.y = -0.25;
            pos.z = -0.59;
            xMult = 0.025;
            yMult = 0.02;
            zMult = 0.025;
            xOffset = 0;
            yOffset = 0;
            zOffset = -90;
            speedMult = 0.25;
        }

        void system() {
            delta.x = a*(pos.y - pos.x) + d*pos.x*pos.z;
            delta.y = c*pos.x - pos.x*pos.z + f*pos.y;
            delta.z = b*pos.z + pos.x*pos.y - e*pos.x*pos.x;
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
