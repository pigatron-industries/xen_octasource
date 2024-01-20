#ifndef TinkerbellMap_h
#define TinkerbellMap_h

#include "../DiscreteSystem.h"
#include <math.h>

class TinkerbellMap : public DiscreteSystemN<2> {
    public:
        void init() {
            DiscreteSystemN::init();
            pos[X] = -0.72;
            pos[Y] = -0.64;
            mult[X] = 2;
            mult[Y] = 2;
            offset[X] = 0;
            offset[Y] = 0;
            initParams(
                {0.9, -0.6013, 2.0, 0.5}, 
                {0.9, -0.5, 2.15, 0.5}
            );
        }

        const char* getName() { return "TINKERBELL"; }

        void system() {
            float x = pos[X]*pos[X] - pos[Y]*pos[Y] + A*pos[X] + B*pos[Y];
            float y = 2*pos[X]*pos[Y] + C*pos[X] + D*pos[Y];
            pos[X] = x;
            pos[Y] = y;
        }
};

#endif
