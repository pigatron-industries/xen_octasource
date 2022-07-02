#ifndef Physics_h
#define Physics_h

#include <eurorack.h>
#include "Body.h"
#include "Constraint.h"
#include "Force.h"


template<int B, int C, int F>
class PhysicalSystem {
    public:
        void update(float dt);
        void addBody(Body* body) { bodies.add(body); }
        void addConstraint(Constraint* constraint) { constraints.add(constraint); }
        void addForce(Force* force) { forces.add(force); }

    private:
        Array<Body*, B> bodies;
        Array<Constraint*, C> constraints;
        Array<Force*, F> forces;
};

template<int B, int C, int F>
void PhysicalSystem<B, C, F>::update(float dt) {
    for(int i = 0; i < constraints.size(); i++) {
        constraints[i]->apply();
    }

    for(int i = 0; i < bodies.size(); i++) {
        for(int j = 0; j < forces.size(); j++) {
            forces[j]->apply(bodies[i]);
        }
        bodies[i]->updatePosition(dt);
    }
}


#endif
