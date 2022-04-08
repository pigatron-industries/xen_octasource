#ifndef BodyFixed_h
#define BodyFixed_h

#include "Body.h"

class BodyFixed : public Body {
    public:
        BodyFixed(Vector<2> position) : Body(position) {
        }

        virtual void updatePosition(float dt) {
            newAcceleration = Vector<2>(0, 0);
        }
};

#endif