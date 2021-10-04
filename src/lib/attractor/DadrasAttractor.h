#ifndef DadrasAttractor_h
#define DadrasAttractor_h

#include "Attractor.h"
#include <math.h>

class DadrasAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            x = 0.1;
            y = 0.1;
            z = 0.1;
            xMult = 0.25;
            yMult = 0.4;
            zMult = 0.35;
            xOffset = 0;
            yOffset = 0;
            zOffset = 0;
            speedMult = 1;
        }

        Deltas system(float x, float y, float z) {
            Deltas dt;
            dt.dxdt = y - a*x + b*y*z;
            dt.dydt = c*y - x*z + z;
            dt.dzdt = d*x*y - e*z;
            return dt;
        }

    private:
        float a = 3;
        float b = 2.7;
        float c = 1.7;
        float d = 2;
        float e = 9;
};

#endif
