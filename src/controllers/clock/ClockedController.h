#ifndef ClockedController_h
#define ClockedController_h

#include "Controller.h"
#include "lib/DistortedClock.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define SAMPLERATE_DIVIDER 8

class ClockedController {
    public:

        ClockedController(float mid = 1, float base = 2) :
            rateCvInput(Hardware::hw.rateSumPin, mid, base) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();
        virtual void onClock() = 0;

    protected:
        ExpInput<AnalogInputSumPinT> rateCvInput;
        IntegerInput<AnalogInputSumPinT> syncMultCvInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5.0, 5.0, -7, 7);
        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);

        DistortedClock<TwoLineFunction> clock;
        ClockDivider syncDivider = ClockDivider(SAMPLERATE_DIVIDER);

        float syncFrequency;

        bool updateRate(bool force = false);
        void updateSync();
};

#endif
