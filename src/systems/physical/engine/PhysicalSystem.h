#ifndef Physics_h
#define Physics_h

#include "Body.h"
#include "Constraint.h"
#include "Force.h"


template<int B, int C, int F>
class PhysicalSystem {
    public:
        void update(float dt);

    private:
        Body bodies[B];
        Constraint* constraints[C];
        Force* forces[F];
    
        Vector<2> forceGravity;
};

template<int B, int C, int F>
void PhysicalSystem<B, C, F>::update(float dt) {
    for(Constraint* constraint : constraints) {
        constraint->apply();
    }

    for(Body& body : bodies) {
        for(Force* force : forces) {
            forces->apply(body);
        }
        body.updatePosition(dt);
    }
}


#endif
