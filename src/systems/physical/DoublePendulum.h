#ifndef DoublePendulum_h
#define DoublePendulum_h

#include "../ContinuousSystem.h"

class Pendulum {
    public:
        float mass;
        float length;

        float angle;
        float velocity;
        float positionX;
        float positionY;
};

class DoublePendulum : public ContinuousSystemN<2> {
    public:
        void init(float sampleRate);
        void setParam(int param, float value);
        void process();

    private:
        Pendulum p1;
        Pendulum p2;

        float g = 9.8;
        float maxVelocity = 10;

        float p2LengthMultMass;
};

#endif
