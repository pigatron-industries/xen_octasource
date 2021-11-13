#ifndef ContinuousSystem_h
#define ContinuousSystem_h

#include "Vector.h"

#define X 0
#define Y 1
#define Z 2
#define W 3

class ContinuousSystem {
    public: 
        virtual void init(float sampleRate) {
            this->sampleRate = sampleRate;
            sampleRateRecip = 1/sampleRate;
            dt = sampleRateRecip;
        };
        virtual void process() = 0;
        virtual float getOutput(int i) = 0;
        virtual void setParam(int i, float value) {};
        void setSpeed(float speed) { dt = sampleRateRecip*speedMult*speed; }
    protected:
        float sampleRate, sampleRateRecip;
        float dt;
        float speedMult = 1;
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

        float getOutput(int i) { return (pos[i]+offset.val[i])*mult.val[i]; }

        void process() {
            system();
            pos += delta * dt;

            if(pos[X] > limits[X]) {
                pos[X] = limits[X];
            } else if(pos[X] < -limits[X]) {
                pos[X] = -limits[X];
            }
        };

    protected:
        Vector<N> pos;
        Vector<N> delta;
        Vector<N> mult;
        Vector<N> offset;
        Vector<N> limits;
};

#endif
