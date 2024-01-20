#ifndef ForceGravity_h
#define ForceGravity_h

#include "Force.h"

class ForceGravity : public Force {
    public:
        ForceGravity(Vector<2> acceleration = Vector<2>(0, -9.8)) : Force() {
            this->acceleration = acceleration;
        }
        inline virtual void apply(Body* body);

    private:
        Vector<2> acceleration;
};

void ForceGravity::apply(Body* body) {
    body->applyAcceleration(acceleration);
}

#endif