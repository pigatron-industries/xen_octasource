#ifndef FourierCircleController_h
#define FourierCircleController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/parametric/FourierCircles.h"
#include "controllers/clock/ClockedController.h"
#include <eurorack_dsp.h>

#define NUM_CIRCLES 7
#define MIN_CIRCLE_FREQEUENCY 0.25
#define MAX_CIRCLE_FREQUENCY 4
#define MAX_OUTPUT 5

#define SAMPLE_RATE_DIVISOR 4

class FourierCircleController : public ParameterizedController<1>, public ClockedController {
    public:
        FourierCircleController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();
        virtual void onClock();

    private:
        enum Parameter {
            MODE
        };
        enum Mode {
            RANDOM
        };

        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 1, 2.5);
        LinearInput<AnalogInputSumPinT> ampInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);

        FourierCircles fourierCircles;
        ClockDivider clockDivider = ClockDivider(SAMPLE_RATE_DIVISOR);
        uint8_t clockCount = 0;

        float ampValue = 0;
        
        void randomizeCircles();
        void updateRate();
        void updateParams();
};

#endif
