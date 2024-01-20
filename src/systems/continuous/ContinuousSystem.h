#ifndef ContinuousSystem_h
#define ContinuousSystem_h

#include "../Vector.h"
#include "lib/interpolationutil.h"

#define PA params[0]
#define PB params[1]
#define PC params[2]
#define PD params[3]
#define PE params[4]
#define PF params[5]

class ContinuousSystem {
    public: 
        virtual void init(float sampleRate) {
            this->sampleRate = sampleRate;
            sampleRateRecip = 1/sampleRate;
            setSpeed(speed);
        }
        virtual const char* getName() { return ""; }
        virtual void process() = 0;
        virtual float getOutput(int i) = 0;
        void setParam(int i, float value) {
            params[i] = value;
        }
        void setInterpolation(float value) {
            params = interpolator.interpolate(value);
        }
        void setSpeed(float speed) { 
            this->speed = speed; 
            dt = sampleRateRecip*speedMult*speed; 
        }

    protected:
        float sampleRate, sampleRateRecip;
        float dt;
        float speed = 1;
        float speedMult = 1;

        ArrayInterpolator<10> interpolator;
        Array<float, 10> params;

        void initParams(std::initializer_list<float> list1, std::initializer_list<float> list2) {
            interpolator.init(list1, list2);
            setInterpolation(0);
        }
};

template<int N>
class ContinuousSystemN : public ContinuousSystem {
    public:
        virtual void init(float sampleRate) {
            ContinuousSystem::init(sampleRate);
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
            pos += delta * dt;
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
        Vector<N> delta;
        Vector<N> mult;
        Vector<N> offset;
        Vector<N> limits;
};

#endif
