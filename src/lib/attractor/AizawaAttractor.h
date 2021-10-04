#ifndef AizawaAttractor_h
#define AizawaAttractor_h

#include "Attractor.h"
#include <math.h>

class AizawaAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            x = 0.1;
            y = 0;
            z = 0;
            xMult = 2.75;
            yMult = 2.75;
            zMult = 3.75;
            xOffset = 0;
            yOffset = 0;
            zOffset = -0.75;
            speedMult = 1;
        }

        Deltas system(float x, float y, float z) {
            Deltas dt;
            dt.dxdt = x*(z-b) - d*y;
            dt.dydt = d*x + y*(z-b);
            dt.dzdt = c + a*z - (z*z*z/3) - (x*x+y*y)*(1+e*z) + f*z*x*x*x;
            return dt;
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
