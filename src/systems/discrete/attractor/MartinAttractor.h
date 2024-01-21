#ifndef MartinAttractor_h
#define MartinAttractor_h

#include "../DiscreteSystem.h"
#include <math.h>

class MartinAttractor : public DiscreteSystemN<2> {
    public:
        void init() {
            DiscreteSystemN::init();
            setParams(0);
        }

        virtual void setParams(float value) {
            if (value < 0.5 and preset != 0) {
                preset = 0;
                pos = {0.1, 0.1};
                mult = {1, 1};
                offset = {-2, -2};
                initParams(
                    {5}, 
                    {5}
                );
            } else if (value >= 0.5 and preset != 1) {
                preset = 1;
                pos = {0.9, 0.8};
                mult = {0.2, 0.2};
                offset = {-2, -2};
                limits = {40, 40};
                initParams(
                    {3.4}, 
                    {3.4}
                );
            }
        }

        const char* getName() { return "MARTIN"; }

        void system() {
            float x = pos[Y] - sinf(pos[X]);
            float y = PA - pos[X];
            pos[X] = x;
            pos[Y] = y;
            if(limit()) {
                Serial.println("limit");
                pos = {0.9, 0.8};
            }
        }

        int preset = -1;
};

#endif
