#ifndef PhasedController_h
#define PhasedController_h

#include "AbstractOscillatorController.h"

using namespace pigatron;

class PhasedController : public AbstractOscillatorController {
    public:
        virtual void init();
        virtual void update();
        virtual void process();

    private:
};

#endif
