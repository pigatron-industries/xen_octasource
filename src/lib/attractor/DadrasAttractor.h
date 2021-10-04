#ifndef DadrasAttractor_h
#define DadrasAttractor_h

#include "Attractor.h"
#include <math.h>

class DadrasAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0.1;
            pos.z = 0.1;
            xMult = 0.25;
            yMult = 0.4;
            zMult = 0.35;
            xOffset = 0;
            yOffset = 0;
            zOffset = 0;
            speedMult = 1;
        }

        void system() {
            delta.x = pos.y - a*pos.x + b*pos.y*pos.z;
            delta.y = c*pos.y - pos.x*pos.z + pos.z;
            delta.z = d*pos.x*pos.y - e*pos.z;
        }

    private:
        float a = 3;
        float b = 2.7;
        float c = 1.7;
        float d = 2;
        float e = 9;
};

#endif
