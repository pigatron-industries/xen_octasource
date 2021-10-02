#ifndef PhasedController_h
#define PhasedController_h

#include "AbstractOscillatorController.h"

using namespace pigatron;

class PhasedController : public AbstractOscillatorController {
    public:
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    private:
};

#endif
