#ifndef DoublePendulumController_h
#define DoublePendulumController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/physical/DoublePendulum.h"
#include <eurorack_dsp.h>

#define SAMPLE_RATE_DIVISOR 2

class DoublePendulumController : public Controller {
    public:
        DoublePendulumController() : Controller(0) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<AnalogInputPinT> expRateCvInput = ExpInput<AnalogInputPinT>(Hardware::hw.rateCvPin, 1);
        LinearInput<AnalogInputPinT> ampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        LinearInput<AnalogInputPinT> param1CvInput = LinearInput<AnalogInputPinT>(Hardware::hw.waveCvPin, -5, 5, 0.1, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputPinT> param2CvInput = LinearInput<AnalogInputPinT>(Hardware::hw.phaseCvPin, -5, 5, 0.1, 0.9);
        #endif

        DoublePendulum doublePendulum;
        ClockDivider clockDivider = ClockDivider(SAMPLE_RATE_DIVISOR);

        float amp;
        
        void updateRate();
        void updateAmp();
        void updateParams();
};

#endif
