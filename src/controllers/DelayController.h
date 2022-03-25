#ifndef DelayController_h
#define DelayController_h

#include <eurorack_dsp.h>
#include "../Controller.h"
#include "../Hardware.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define DELAYBUFFER_SIZE ((MEMPOOL_SIZE/8)-1)
#define SAMPLERATE_DIVIDER 8

class DelayController : public Controller {
    public:

        enum Mode {
            DELAY,
            SLEW
        };

        DelayController() : Controller(Mode::SLEW) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        LinearInput<AnalogInputPinT> timeCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.rateCvPin, -5, 5, 0.02, 1);
        LinearInput<AnalogInputPinT> ampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        
        ClockDivider clockDivider = ClockDivider(SAMPLERATE_DIVIDER);
        DelayLine delays[OUTPUT_CV_COUNT];
        StateVariableFilter filters[OUTPUT_CV_COUNT];

        float value;
};

#endif