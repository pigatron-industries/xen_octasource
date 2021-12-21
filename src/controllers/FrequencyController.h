#ifndef FrequencyController_h
#define FrequencyController_h

#include "AbstractOscillatorController.h"

using namespace pigatron;

class FrequencyController : public AbstractOscillatorController {
    public:
        enum Mode {
            LINEAR,
            EXP,
            UNCORRELATED,
            PLANETARY
        };

        FrequencyController() : AbstractOscillatorController(Mode::PLANETARY) {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    protected:
        void setRate(float baseFrequency);

    private:
        void updateRate();
};

#endif
