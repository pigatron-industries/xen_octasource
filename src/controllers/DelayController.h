#ifndef DelayController_h
#define DelayController_h

#include <eurorack_dsp.h>
#include "../Controller.h"
#include "../Hardware.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define OUTPUTS 8
#define DELAYBUFFER_SIZE ((MEMPOOL_SIZE/OUTPUTS)-1)
#define SAMPLERATE_DIVIDER 8

class DelayController : public ParameterizedController<1> {
    public:
        DelayController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        enum Parameter {
            MODE
        };
        enum Mode {
            DELAY,
            SLEW
        };

        LinearInput<AnalogInputSumPinT> timeCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 0.02, 1);
        LinearInput<AnalogInputPinT> ampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.ampPotPin, -5, 5, 0, 1);
        
        ClockDivider clockDivider = ClockDivider(SAMPLERATE_DIVIDER);
        DelayLine delays[OUTPUT_CV_COUNT];
        StateVariableFilter filters[OUTPUT_CV_COUNT];

        float value;
};

#endif