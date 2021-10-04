#ifndef RosslerAttractor_h
#define RosslerAttractor_h

#include "Attractor.h"

class RosslerAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0;
            pos.z = 0;
            xMult = 0.4;
            yMult = 0.5;
            zMult = 0.4;
            xOffset = -1;
            yOffset = 1.5;
            zOffset = -11;
            speedMult = 2;
        }

        void system() {
            delta.x = -(pos.y+pos.z);
            delta.y = pos.x + a*pos.y;
            delta.z = b + pos.z*(pos.x-c);
        }

    private:
        float a = 0.2;
        float b = 0.2;
        float c = 5.7;
};

#endif
