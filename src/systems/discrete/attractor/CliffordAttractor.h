#ifndef CliffordAttractor_h
#define CliffordAttractor_h

#include "../DiscreteSystem.h"
#include <math.h>

class CliffordAttractor : public DiscreteSystemN<2> {
    public:
        void init() {
            DiscreteSystemN::init();
            pos[X] = 0.1;
            pos[Y] = 0.1;
            mult[X] = 1;
            mult[Y] = 1;
            offset[X] = 0;
            offset[Y] = 0;
            initParams(
                {2, -2, 2, -2}, 
                {1.1, -1, 1, 1.5}
            );
        }

        const char* getName() { return "CLIFFORD"; }

        void system() {
            float x = sin(A*pos[Y]) + C*cos(A*pos[X]);
            float y = sin(B*pos[X]) + D*cos(B*pos[Y]);
            pos[X] = x;
            pos[Y] = y;
        }
};

#endif
