#ifndef StrangeAttractor_h
#define StrangeAttractor_h

#include "Attractor.h"

class LorenzAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            x = 0.1;
            y = 0;
            z = 0;
            xMult = 0.2;
            yMult = 0.2;
            zMult = 0.2;
            zOffset = -25;
        }

        Deltas system(float x, float y, float z) {
            Deltas d;
            d.dxdt = a*(y-x);
            d.dydt = x*(c-z) - y;
            d.dzdt = x*y - b*z;
            return d;
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
