#ifndef ChenAttractor_h
#define ChenAttractor_h

#include "Attractor.h"
#include <math.h>

class ChenAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            x = 0.1;
            y = 0.1;
            z = 0.1;
            xMult = 0.25;
            yMult = 0.3;
            zMult = 0.8;
            xOffset = 0;
            yOffset = 0;
            zOffset = -9.5;
            speedMult = 1.5; //Breaks if it goes too fast
        }

        Deltas system(float x, float y, float z) {
            Deltas dt;
            dt.dxdt = a*x - y*z;
            dt.dydt = b*y + x * z;
            dt.dzdt = c*z + x*y/3;
            return dt;
        }

    private:
        float a = 5;
        float b = -10;
        float c = -0.38;
};

#endif
