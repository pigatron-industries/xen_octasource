#ifndef ClockController_h
#define ClockController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include "lib/DistortedClock.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class ClockController : public Controller {
    public:
        enum Preset {
            INTEGER,
            EVEN,
            ODD,
            POWER2,
            PRIME,
            FIBONACCI,
            PPQN24
        };

        enum InputMode {
            PRESET,
            CUSTOM1,
            CUSTOM2,
            CUSTOM3,
            CUSTOM4,
            CUSTOM5,
            CUSTOM6,
            CUSTOM7,
            CUSTOM8
        };

        ClockController() : Controller(Preset::PPQN24) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        LinearInput<AnalogInputSumPinT> rateCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 0, 30);
        LinearInput<AnalogInputSumPinT> lengthInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 4.1, 32.9);
        LinearInput<AnalogInputSumPinT> distortionXCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> distortionYCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 1);
        #endif

        AnalogGateOutput<AnalogOutputDeviceT> gateOutputs[8] = {
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[0]),
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[1]),
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[2]),
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[3]),
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[4]),
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[5]),
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[6]),
            AnalogGateOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[7])
        };

        GateInput<> rangeInput = GateInput<>(Hardware::hw.rangeSwitchPin, false);

        DistortedClock<TwoLineFunction, 32> clock;
        DistortedClock<SmoothStepFunction, 32> smoothClock;
        ClockDivider clockDividers[8];
        ClockGate clockGate[8];

        float distortionX, distortionY;

        void tick();
        void setClockDivisorLength(int channel, int divisor, int length);
        
};

#endif
