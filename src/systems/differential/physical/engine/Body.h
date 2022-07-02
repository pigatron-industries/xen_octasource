#ifndef Body_h
#define Body_h

#include "../../../Vector.h"

class Body {
    public:
        enum Type {
            FIXED, FREE
        };

        Body(Vector<2> position = Vector<2>(0, 0), Type type = Type::FREE, float mass = 1, Vector<2> velocity = Vector<2>(0, 0)) {
            this->type = type;
            this->position = position;
            this->velocity = velocity;
            setMass(mass);
        }

        void setMass(float mass) {
            this->mass = mass;
            massRecip = 1.0/mass;
        }

        void setPosition(Vector<2> position) { this->position = position; }
        void setVelocity(Vector<2> velocity) { this->velocity = velocity; }

        float getMass() { return mass; }
        float getMassRecip() { return massRecip; }
        Vector<2>& getPosition() { return position; }
        Vector<2>& getVelocity() { return velocity; }
        Vector<2>& getAcceleration() { return acceleration; }
        
        void applyAcceleration(Vector<2> acceleration) { 
            if(type == Type::FREE) { 
                newAcceleration += acceleration; 
            } 
        }

        void updatePosition(float dt) {
            if(type == Type::FREE) {
                acceleration = newAcceleration;
                velocity += acceleration * dt;
                position += velocity * dt;
                newAcceleration = Vector<2>(0, 0);
            }
        }

    private:
        Type type;
        float mass = 1;
        float massRecip;
        Vector<2> position = Vector<2>(0, 0);
        Vector<2> velocity = Vector<2>(0, 0);
        Vector<2> acceleration = Vector<2>(0, 0);
        Vector<2> newAcceleration = Vector<2>(0, 0);
};

#endif