#ifndef JoshiBlackmoreMap_h
#define JoshiBlackmoreMap_h

#include "../DiscreteSystem.h"
#include <math.h>

class JoshiBlackmoreMap : public DiscreteSystemN<2> {
    public:
        void init() {
            DiscreteSystemN::init();
            pos[X] = 0.1;
            pos[Y] = 0.1;
            mult[X] = 2;
            mult[Y] = 2;
            offset[X] = 0;
            offset[Y] = 0;
            float b = ((1 + sqrtf(5))/2)*M_2_PI;
            initParams(
                {2.6, b}, 
                {6.1, b}
            );
        }

        const char* getName() { return "JOSHIBLACKMORE"; }

        void system() {
            float c = powf(M_E, - pos[X]*pos[X] - pos[Y]*pos[Y]);
            float x = A * c * (pos[X] * cos(B) - pos[Y] * sin(B));
            float y = A * c * (pos[X] * sin(B) + pos[Y] * cos(B));
            pos[X] = x;
            pos[Y] = y;
        }

};

#endif
