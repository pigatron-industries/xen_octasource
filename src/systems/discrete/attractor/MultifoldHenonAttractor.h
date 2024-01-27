#ifndef MultifoldHenonAttractor_h
#define MultifoldHenonAttractor_h

#include "../DiscreteSystem.h"
#include <math.h>

class MultifoldHenonAttractor : public DiscreteSystemN<2> {
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
                {3.0, 0.9}, 
                {4.0, 0.9}
            );
        }

        const char* getName() { return "MULTIFOLDHENON"; }

        void system() {
            float x = 1 - PA*sin(PX) - PB*PY;
            float y = PX;
            pos[X] = x;
            pos[Y] = y;
        }
};

#endif
