#ifndef ClockController_h
#define ClockController_h

#include "Controller.h"
#include "controllers/ClockedController.h"
#include "ClockDisplay.h"
#include <eurorack_dsp.h>

#define NUM_DIVIDERS 15
#define NUM_MULTIPLIERS 15
#define MULIPLIER_BASE 16

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
        virtual int cycleParameter(int amount);
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();
        virtual void onClock();

    private:
        struct ClockParameters {
            uint8_t check = 0;
            uint8_t clock[8];
        };
        ConfigField<ClockParameters> config;

        ClockDisplay display;

        IntegerInput<AnalogInputSumPinT> lengthInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 2, 16);
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

        // uint8_t channelSetting[8];
    
        ClockDivider clockDividers[NUM_DIVIDERS];
        Clock clockMultipliers[NUM_MULTIPLIERS];

        void updateMultiplierRates();
        void updateClock(uint8_t output);
        void syncClocks();
        
        bool isMultiplier(int channel);
        bool isDivider(int channel);
        uint8_t getMultiplier(int channel);
        uint8_t getDivider(int channel);
};

#endif
