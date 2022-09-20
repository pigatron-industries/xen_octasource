#ifndef ClockedController_h
#define ClockedController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define SAMPLERATE_DIVIDER 8

class ClockedController {
    public:

        ClockedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();
        virtual void onClock() = 0;

    protected:
        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        ExpInput<AnalogInputSumPinT> rateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 1, 2);
        IntegerInput<AnalogInputSumPinT> syncMultCvInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5.0, 5.0, -7, 7);

        Clock clock;
        ClockDivider syncDivider = ClockDivider(SAMPLERATE_DIVIDER);

        float syncFrequency;

        bool updateRate(bool force = false);
        void updateSync();
};

#endif
