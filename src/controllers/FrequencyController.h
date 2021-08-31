#ifndef FrequencyController_h
#define FrequencyController_h

#include "AbstractOscillatorController.h"

using namespace pigatron;

class FrequencyController : public AbstractOscillatorController {
    public:
        enum Mode {
            LINEAR,
            EXP
        };

        FrequencyController() : AbstractOscillatorController(Mode::EXP) {}
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        void updateRate();
};

#endif
