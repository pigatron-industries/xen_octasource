#ifndef MetzAttractor_h
#define MetzAttractor_h

#include "../DiscreteSystem.h"
#include <math.h>

class MetzAttractor : public DiscreteSystemN<2> {
    public:
        void init() {
            DiscreteSystemN::init();
            pos[X] = 70;
            pos[Y] = 100;
            mult[X] = 0.09;
            mult[Y] = 0.02;
            offset[X] = -87;
            offset[Y] = -250;
            initParams(
                {4.155, 10}, 
                {4.175, 10}
            );
        }

        const char* getName() { return "METZ"; }

        void system() {
            float x = PA*PX*exp((1-sqrt(1+PY))/PB);
            float y = PA*PX - x;
            pos[X] = x;
            pos[Y] = y;
        }
};

#endif
