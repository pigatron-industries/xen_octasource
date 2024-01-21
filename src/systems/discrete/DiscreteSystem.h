#ifndef DiscreteSystem_h
#define DiscreteSystem_h

#include "../Vector.h"
#include "lib/interpolationutil.h"
#include <eurorack.h>

#define PA params[0]
#define PB params[1]
#define PC params[2]
#define PD params[3]
#define PE params[4]
#define PF params[5]

#define PX pos[X]
#define PY pos[Y]
#define PZ pos[Z]

class DiscreteSystem {
    public: 
        virtual void init() {}
        virtual const char* getName() { return ""; }
        virtual void process() = 0;
        virtual float getOutput(int i) = 0;
        virtual void setPreset(int preset) {}
        virtual void setParams(float value) {
            if(presets > 0) {
                int newPreset = (int)(value*presets);
                if(preset != newPreset) {
                    preset = newPreset;
                    setPreset(newPreset);
                }
            } else {
                params = interpolator.interpolate(value);
            }
        }
        void setParam(int i, float value) {
            params[i] = value;
        }

    protected:
        ArrayInterpolator<10> interpolator;
        Array<float, 10> params;
        int presets = 0;
        int preset = 0;

        void initParams(std::initializer_list<float> list1, std::initializer_list<float> list2) {
            interpolator.init(list1, list2);
            params = interpolator.interpolate(0);
        }
};

template<int N>
class DiscreteSystemN : public DiscreteSystem {
    public:
        virtual void init() {
            DiscreteSystem::init();
            for(int i = 0; i < N; i++) {
                pos[i] = 0;
                mult[i] = 1;
                offset[i] = 0;
                limits.val[i] = 99999;
            }
        }

        virtual void system() {};

        void setPosition(Vector<N> position) { pos = position; }
        void changePosition(Vector<N> change) { pos += change; }

        void setOffset(Vector<N> offset) { this->offset = offset; }
        void setScale(Vector<N> scale) { this->mult = scale; }

        float getOutput(int i) { return (pos[i]+offset.val[i])*mult.val[i]; }
        Vector<N> getPos() { return (pos+offset)*mult; }

        void process() {
            system();
            limit();
        }

        bool limit() {
            if(pos[X] > limits[X]) {
                pos[X] = limits[X];
                return true;
            } else if(pos[X] < -limits[X]) {
                pos[X] = -limits[X];
                return true;
            }
            return false;
        }

    protected:
        Vector<N> pos;
        Vector<N> mult;
        Vector<N> offset;
        Vector<N> limits;
};

#endif
