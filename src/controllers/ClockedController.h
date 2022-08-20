#ifndef ClockedController_h
#define ClockedController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define SAMPLERATE_DIVIDER 8

class ClockedController : public Controller {
    public:

        ClockedController(): Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();
        virtual void onClock() = 0;

    private:
        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        LinearInput<AnalogInputSumPinT> rateCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 0, 10);
        IntegerInput<AnalogInputSumPinT> syncMultCvInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5.0, 5.0, -7, 7);

        Clock clock;
        ClockDivider syncDivider = ClockDivider(SAMPLERATE_DIVIDER);

        float syncFrequency;

        void updateRate(bool force = false);
        void updateSync();
};

#endif
