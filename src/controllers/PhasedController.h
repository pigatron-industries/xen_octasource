#ifndef PhasedController_h
#define PhasedController_h

#include <Arduino.h>
#include <eurorack_dsp.h>
#include "AbstractOscillatorController.h"
#include "../Hardware.h"
#include "BipolarExpInput.h"

using namespace pigatron;

class PhasedController : public AbstractOscillatorController {
    public:
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    private:
};

#endif
