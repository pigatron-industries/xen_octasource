#ifndef AizawaAttractor_h
#define AizawaAttractor_h

#include "Attractor.h"
#include <math.h>

class AizawaAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0;
            pos.z = 0;
            xMult = 2.75;
            yMult = 2.75;
            zMult = 3.75;
            xOffset = 0;
            yOffset = 0;
            zOffset = -0.75;
            speedMult = 1;
        }

        void system() {
            delta.x = pos.x*(pos.z-b) - d*pos.y;
            delta.y = d*pos.x + pos.y*(pos.z-b);
            delta.z = c + a*pos.z - (pos.z*pos.z*pos.z/3) - (pos.x*pos.x+pos.y*pos.y)*(1+e*pos.z) + f*pos.z*pos.x*pos.x*pos.x;
        }

    private:
        float a = 0.95;
        float b = 0.7;
        float c = 0.6;
        float d = 3.5;
        float e = 0.25;
        float f = 0.1;
};

#endif
