#ifndef SpringPendulum_h
#define SpringPendulum_h

#include "../ContinuousSystem.h"
#include "engine/PhysicalSystem.h"
#include "engine/ConstraintSpring.h"
#include "engine/ForceGravity.h"

class SpringPendulum : public ContinuousSystemN<2> {
    public:
        SpringPendulum();
        void setInitialConditions(Vector<2> bodyPosition, Vector<2> bodyVelocity);
        void setSpringStiffness(float stiffness) { spring.setStiffness(stiffness); };
        void init(float sampleRate);
        void process();

    private:

        PhysicalSystem<2, 1, 1> physics;

        Body fixedBody = Body(Vector<2>(0, 0), Body::Type::FIXED);
        Body body = Body(Vector<2>(0, -3), Body::Type::FREE, 0.5, Vector<2>(0.01, 0.5));
        ConstraintSpring spring = ConstraintSpring(fixedBody, body, 2.5, 6);
        ForceGravity gravity = ForceGravity(Vector<2>(0, -9.8));

};

#endif
