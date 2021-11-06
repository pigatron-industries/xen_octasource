#ifndef ContinuousSystem_h
#define ContinuousSystem_h

#include "Tuple.h"

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
        virtual void system() = 0;
        virtual float getOutput(int i) = 0;
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
                limits.val[i] = 99999;
            }
        }

        void setSpeed(float speed) { dt = sampleRateRecip*speedMult*speed; }
        void setPosition(Tuple<N> position) { pos = position; }
        void changePosition(Tuple<N> change) { pos += change; }

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
        Tuple<N> pos;
        Tuple<N> delta;
        Tuple<N> mult;
        Tuple<N> offset;
        Tuple<N> limits;
};

#endif
