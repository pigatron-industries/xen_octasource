#ifndef ConstraintSpring_h
#define ConstraintSpring_h

#include "Constraint.h"

class ConstraintSpring : public Constraint {
    public:
        ConstraintSpring(Body& body1, Body& body2, float restLength = 1, float stiffness = 1) : 
            Constraint(), body1(body1), body2(body2) {
                this->restLength = restLength;
                this->stiffness = stiffness;
        }
        virtual void apply();
    
    private:
        Body& body1;
        Body& body2;
        float stiffness;
        float restLength;
};

#endif