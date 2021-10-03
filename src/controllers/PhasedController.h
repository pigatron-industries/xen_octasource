#ifndef PhasedController_h
#define PhasedController_h

#include "AbstractOscillatorController.h"

using namespace pigatron;

#if defined(OCTASOURCE_MKII)
    #define PHASED_LAST_MODE Mode::EXPONENTIAL_VCO
#endif
#if defined(OCTASOURCE_MKI)
    #define PHASED_LAST_MODE Mode::BIPOLAR_LFO
#endif

class PhasedController : public AbstractOscillatorController {
    public:
        enum Mode {
            BIPOLAR_LFO,
            EXPONENTIAL_VCO
        };

        PhasedController() : AbstractOscillatorController(PHASED_LAST_MODE) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

        void updatePhase();

    private:
};

#endif
