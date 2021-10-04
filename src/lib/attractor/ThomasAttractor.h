#ifndef ThomasAttractor_h
#define ThomasAttractor_h

#include "Attractor.h"
#include <math.h>

class ThomasAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            x = 0.1;
            y = 0;
            z = 0;
            xMult = 1.75;
            yMult = 1.75;
            zMult = 1.75;
            xOffset = -1.5;
            yOffset = -1.5;
            zOffset = -1.5;
            speedMult = 4;
        }

        Deltas system(float x, float y, float z) {
            Deltas d;
            d.dxdt = sinf(y)-b*x;
            d.dydt = sinf(z)-b*y;
            d.dzdt = sinf(x)-b*z;
            return d;
        }

        void setB(float b) { this->b = b; }

    private:
        float b = 0.208186;
};

#endif
