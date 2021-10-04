#ifndef HalvorsenAttractor_h
#define HalvorsenAttractor_h

#include "Attractor.h"

class HalvorsenAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0.1;
            pos.z = 0.1;
            xMult = 0.4;
            yMult = 0.5;
            zMult = 0.5;
            xOffset = 2.75;
            yOffset = 3;
            zOffset = 2.75;
            speedMult = 1;
        }

        void system() {
            delta.x = -a*pos.x - 4*pos.y - 4*pos.z - pos.y*pos.y;
            delta.y = -a*pos.y - 4*pos.z - 4*pos.x - pos.z*pos.z;
            delta.z = -a*pos.z - 4*pos.x - 4*pos.y - pos.x*pos.x;
        }

    private:
        float a = 1.4;
};

#endif
