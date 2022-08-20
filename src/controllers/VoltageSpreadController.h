#ifndef VoltageSpreadController_h
#define VoltageSpreadController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define SAMPLERATE_DIVIDER 8

class VoltageSpreadController : public Controller {
    public:
        enum Mode {
            EXP
        };

        VoltageSpreadController() : Controller(Mode::EXP) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    protected:
        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        LinearInput<AnalogInputSumPinT> spreadCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 0, 1);

        //LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 5);
        //LinearInput<AnalogInputSumPinT> waveCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 5);
        //LinearInput<AnalogInputSumPinT> spreadCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 1);

        float voltageOffsets[OUTPUT_CV_COUNT];
        ClockDivider clockDivider = ClockDivider(SAMPLERATE_DIVIDER);

        void setRate(float baseFrequency, float spread);
        void updateRate();
        void updateAmp();
        void updateWave();

};

#endif
