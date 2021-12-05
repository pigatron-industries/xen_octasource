#ifndef BouncingBall_h
#define BouncingBall_h

#include "../ContinuousSystem.h"
#include <eurorack.h>


class BouncingBall : public ContinuousSystemN<1> {
    public:

        void init(float sampleRate);
        void trigger();
        void setParam(int param, float value);
        void setDamp(float damp) { this->damp = damp; }

        void process();

    private:
        float damp = 0.9;
        float startVelocity = 3;
        float acceleration = 1;

        float time;
        float bounceVelocity;

        float calcStartBounceTimeAtHeight();
};

#endif
