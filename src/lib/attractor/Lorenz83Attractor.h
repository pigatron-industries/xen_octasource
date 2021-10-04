#ifndef Lorenz83Attractor_h
#define Lorenz83Attractor_h

#include "Attractor.h"

class Lorenz83Attractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0.1;
            pos.z = 0.1;
            xMult = 1.8;
            yMult = 1.5;
            zMult = 1.5;
            xOffset = -0.75;
            yOffset = -0.25;
            zOffset = -0.25;
            speedMult = 1;
        }

        void system() {
            delta.x = - a*pos.x - pos.y*pos.y - pos.z*pos.z + a*f;
            delta.y = - pos.y + pos.x*pos.y - b*pos.x*pos.z + g;
            delta.z = - pos.z + b*pos.x*pos.y + pos.x*pos.z;
        }

    private:
        float a = 0.95;
        float b = 7.91;
        float f = 4.83;
        float g = 4.66;
};

#endif
