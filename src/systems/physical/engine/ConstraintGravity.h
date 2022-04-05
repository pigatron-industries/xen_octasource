#ifndef ConstraintGravity_h
#define ConstraintGravity_h

#include "Constraint.h"

class ConstraintGravity : public Constraint {
    public:
        ConstraintGravity(Body& body1, Body& body2, float G = 1) : 
            Constraint(), body1(body1), body2(body2) {
                this->G = G;
        }
        virtual void apply();
    
    private:
        Body& body1;
        Body& body2;
        float G;
};

#endif