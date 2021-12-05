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
        void setStartVelocity(float startVelocity) { this->startVelocity = startVelocity; }
        void setAcceleration(float acceleration) { this->acceleration = acceleration; }

        void setStartVelocityForHeight(float height) { startVelocity = calcInitVelocityForHeight(height); }

        bool getBounced() { return bounced; }
        float getBounceHeight() { return bounceHeight; }

        void process();

    private:
        float damp = 0.9;
        float startVelocity = 3;
        float acceleration = 1;

        float time;
        float bounceVelocity;
        float bounceHeight;
        bool bounced;

        float calcHeightAtTime(float initVelocity, float time);
        float calcTimeToHeight(float startVelocity, float height);
        float calcTimeToMaxHeight(float startVelocity);
        float calcInitVelocityForHeight(float height);
};

#endif
