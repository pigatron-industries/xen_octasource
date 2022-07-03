#ifndef TrochoidController_h
#define TrochoidController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/parametric/Hypotrochoid.h"
#include <eurorack_dsp.h>

#define SAMPLE_RATE_DIVISOR 2

class TrochoidController : public Controller {
    public:
        enum Mode {
            HYPOTROCHOID
        };
        TrochoidController() : Controller(Mode::HYPOTROCHOID) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 10);
        LinearInput<AnalogInputSumPinT> largeRadiusInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 4);
        LinearInput<AnalogInputSumPinT> smallRadiusInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0.05, 4);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> pointRadiusInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 4);
        #endif

        Hypotrochoid hypotrochoid;
        
        void updateRate();
        void updateParams();
};

#endif
