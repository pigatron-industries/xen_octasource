#ifndef SpringPendulum_h
#define SpringPendulum_h

#include "../ContinuousSystem.h"
#include "engine/PhysicalSystem.h"

class SpringPendulum : public ContinuousSystemN<2> {
    public:
        void init(float sampleRate);
        void process();

    private:

        PhysicalSystem<2, 1, 1> physics;

};

#endif
