#ifndef ChenAttractor_h
#define ChenAttractor_h

#include "Attractor.h"
#include <math.h>

class ChenAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0.1;
            pos.z = 0.1;
            xMult = 0.25;
            yMult = 0.3;
            zMult = 0.8;
            xOffset = 0;
            yOffset = 0;
            zOffset = -9.5;
            speedMult = 1.5; //Breaks if it goes too fast
        }

        void system() {
            delta.x = a*pos.x - pos.y*pos.z;
            delta.y = b*pos.y + pos.x*pos.z;
            delta.z = c*pos.z + pos.x*pos.y/3;
        }

    private:
        float a = 5;
        float b = -10;
        float c = -0.38;
};

#endif
