#ifndef LorenzAttractor_h
#define LorenzAttractor_h

#include "Attractor.h"

class LorenzAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0;
            pos.z = 0;
            xMult = 0.2;
            yMult = 0.2;
            zMult = 0.2;
            zOffset = -25;
        }

        void system() {
            delta.x = a*(pos.y-pos.x);
            delta.y = pos.x*(c-pos.z) - pos.y;
            delta.z = pos.x*pos.y - b*pos.z;
        }

        void setA(float a) { this->a = a; }
        void setB(float b) { this->b = b; }
        void setC(float c) { this->c = c; }

    private:
        float a = 10.0;
        float b = 8.0/3.0;
        float c = 28.0;
};

#endif
