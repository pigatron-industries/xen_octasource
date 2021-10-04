#ifndef ThomasAttractor_h
#define ThomasAttractor_h

#include "Attractor.h"
#include <math.h>

class ThomasAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0;
            pos.z = 0;
            xMult = 1.75;
            yMult = 1.75;
            zMult = 1.75;
            xOffset = -1.5;
            yOffset = -1.5;
            zOffset = -1.5;
            speedMult = 4;
        }

        void system() {
            delta.x = sinf(pos.y)-b*pos.x;
            delta.y = sinf(pos.z)-b*pos.y;
            delta.z = sinf(pos.x)-b*pos.z;
        }

        void setB(float b) { this->b = b; }

    private:
        float b = 0.208186;
};

#endif
