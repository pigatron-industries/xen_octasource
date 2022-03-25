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
        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 1);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        LinearInput<AnalogInputSumPinT> param1CvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0.1, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> param2CvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0.1, 0.9);
        #endif

        DoublePendulum doublePendulum;
        ClockDivider clockDivider = ClockDivider(SAMPLE_RATE_DIVISOR);

        float amp;
        
        void updateRate();
        void updateAmp();
        void updateParams();
};

#endif
