#ifndef Chua9ScrollAttractor_h
#define Chua9ScrollAttractor_h

#include "Attractor.h"
#include <math.h>

class ChuaMultiScrollAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0;
            pos.z = 0;
            xMult = 0.2;
            yMult = 8;
            zMult = 0.2;
            xOffset = 0;
            yOffset = 0;
            zOffset = 0;
            speedMult = 2;
            limits.x = 20;
        }

        void system() {
            float h = -b*sinf((M_PI*pos.x)/(2*a) + d);
            delta.x = alpha*(pos.y-h);
            delta.y = pos.x - pos.y + pos.z;
            delta.z = -beta*pos.y;
        }


    private:
        float alpha = 10.82;
        float beta = 14.286;
        float a = 1.3;
        float b = 0.11;
        float c = 7;
        float d = 0;
};

#endif
