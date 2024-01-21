#ifndef HopalongAttractor_h
#define HopalongAttractor_h

#include "../DiscreteSystem.h"
#include <math.h>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class HopalongAttractor : public DiscreteSystemN<2> {
    public:
        void init() {
            DiscreteSystemN::init();
            presets = 5;
            offset = {0, -0.4};
            mult = {2, 2};
            limits = {20, 20};
            initParams(
                {0.4, 1.0, 0.0}, 
                {0.4, 1.0, 0.0}
            );
            setPreset(0);
        }

        virtual void setPreset(int preset) {
            Serial.print("setPreset ");
            Serial.println(preset);
            switch (preset) {
                case 0:
                    pos = {0.1, 0.1};
                    mult = {6, 6};
                    break;
                case 1:
                    pos = {1.1, 1.1};
                    mult = {2.5, 2.5};
                    break;
                case 2: 
                    pos = {1.4, 1.4};
                    mult = {2, 2};
                    break;
                case 3:
                    pos = {2, 2};
                    mult = {1.8, 1.8};
                    break;
                case 4:
                    pos = {2.4, 2.4};
                    mult = {1.2, 1.2};
                    break;
            }
        }

        const char* getName() { return "HOPALONG"; }

        void system() {
            float x = PY - sgn(PX)*sqrtf(abs(PB*PX - PC));
            float y = PA - PX;
            pos[X] = x;
            pos[Y] = y;
        }

};

#endif
