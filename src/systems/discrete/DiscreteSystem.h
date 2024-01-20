#ifndef DiscreteSystem_h
#define DiscreteSystem_h

#include "../Vector.h"
#include "lib/interpolationutil.h"
#include <eurorack.h>

#define A params[0]
#define B params[1]
#define C params[2]
#define D params[3]
#define E params[4]
#define F params[5]

class DiscreteSystem {
    public: 
        virtual void init() {}
        virtual const char* getName() { return ""; }
        virtual void process() = 0;
        virtual float getOutput(int i) = 0;
        void setParam(int i, float value) {
            params[i] = value;
        }
        void setInterpolation(float value) {
            params = interpolator.interpolate(value);
        }

    protected:
        ArrayInterpolator<10> interpolator;
        Array<float, 10> params;

        void initParams(std::initializer_list<float> list1, std::initializer_list<float> list2) {
            interpolator.init(list1, list2);
            setInterpolation(0);
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

        void limit() {
            if(pos[X] > limits[X]) {
                pos[X] = limits[X];
            } else if(pos[X] < -limits[X]) {
                pos[X] = -limits[X];
            }
        }

    protected:
        Vector<N> pos;
        Vector<N> mult;
        Vector<N> offset;
        Vector<N> limits;
};

#endif
