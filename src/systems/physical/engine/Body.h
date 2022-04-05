#ifndef Body_h
#define Body_h

#include "../../Vector.h"

class Body {
    public:
        Body(Vector<2> position, float mass = 1, Vector<2> velocity = Vector<2>(0, 0)) {
            setMass(mass);
        }

        void setMass(float mass) {
            this->mass = mass;
            massRecip = 1.0/mass;
        }

        float getMass() { return mass; }
        float getMassRecip() { return massRecip; }
        Vector<2> getPosition() { return position; }
        void applyAcceleration(Vector<2> acceleration) { newAcceleration += acceleration; }

        void updatePosition(float dt) {
            acceleration = newAcceleration;
            velocity += acceleration * dt;
            position += velocity * dt;
            newAcceleration = Vector<2>(0, 0);
        }

    private:
        float mass = 1;
        float massRecip;
        Vector<2> position = Vector<2>(0, 0);
        Vector<2> velocity = Vector<2>(0, 0);
        Vector<2> acceleration = Vector<2>(0, 0);
        Vector<2> newAcceleration = Vector<2>(0, 0);
};

#endif