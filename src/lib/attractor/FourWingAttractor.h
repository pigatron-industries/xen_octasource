#ifndef FourWingAttractor_h
#define FourWingAttractor_h

#include "Attractor.h"

class FourWingAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0;
            pos.z = 0;
            xMult = 2;
            yMult = 2;
            zMult = 2;
            xOffset = 0;
            yOffset = 0;
            zOffset = 0;
            speedMult = 4;
        }

        void system() {
            delta.x = a*pos.x + pos.y*pos.z;
            delta.y = b*pos.x + c*pos.y - pos.x*pos.z;
            delta.z = - pos.z - pos.x*pos.y;
        }

    private:
        float a = 0.2;
        float b = 0.01;
        float c = -0.4;
};

#endif
