#ifndef RabinovichFabrikantAttractor_h
#define RabinovichFabrikantAttractor_h

#include "Attractor.h"

class RabinovichFabrikantAttractor : public Attractor {
    public:
        void init(float sampleRate) {
            Attractor::init(sampleRate);
            pos.x = 0.1;
            pos.y = 0.1;
            pos.z = 0.1;
            xMult = 1.75;
            yMult = 1.75;
            zMult = 6;
            xOffset = 0;
            yOffset = 0;
            zOffset = -0.5; //-0.75;
            speedMult = 2;
        }

        void system() {
            delta.x = pos.y*(pos.z-1+pos.x*pos.x) + b*pos.x;
            delta.y = pos.x*(3*pos.z+1-pos.x*pos.x) + b*pos.y;
            delta.z = - 2*pos.z*(a + pos.x*pos.y);
        }

    private:
        float a = 0.98; //0.14;
        float b = 0.10;
};

#endif
