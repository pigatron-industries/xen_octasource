#ifndef ClockController_h
#define ClockController_h

#include "Controller.h"
#include "controllers/ClockedController.h"
#include "ClockDisplay.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class ClockController : public ParameterizedController<8>, public ClockedController {
    public:
        enum Parameters {
            CLOCK1,
            CLOCK2,
            CLOCK3,
            CLOCK4,
            CLOCK5,
            CLOCK6,
            CLOCK7,
            CLOCK8
        };

        ClockController() : ParameterizedController(), ClockedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual int cycleMode(int amount);
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();
        virtual void onClock();

    private:
        ClockDisplay display;

        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        LinearInput<AnalogInputSumPinT> rateCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 0, 30);
        LinearInput<AnalogInputSumPinT> lengthInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 4.1, 32.9);
        LinearInput<AnalogInputSumPinT> distortionXCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> distortionYCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 1);
        #endif

        TriggerOutput<DigitalOutputDeviceT> triggerOutput = TriggerOutput<DigitalOutputDeviceT>(Hardware::hw.gateOutPin, 20000);
        AnalogTriggerOutput<AnalogOutputDeviceT> triggerOutputs[8] = {
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[0]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[1]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[2]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[3]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[7])
        };

        GateInput<> rangeInput = GateInput<>(Hardware::hw.rangeSwitchPin, false);

        uint8_t multipliers[8];
        ClockDivider clockDividers[8];
        Clock clockMultipliers[8];

        void updateMultiplierRates();
        void syncClocks();
        
};

#endif
