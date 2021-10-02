#ifndef FrequencyController_h
#define FrequencyController_h

#include "AbstractOscillatorController.h"

using namespace pigatron;

class FrequencyController : public AbstractOscillatorController {
    public:
        enum Mode {
            LINEAR,
            EXP,
            UNCORRELATED
        };

        FrequencyController() : AbstractOscillatorController(Mode::UNCORRELATED) {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    private:
        void updateRate();
};

#endif
