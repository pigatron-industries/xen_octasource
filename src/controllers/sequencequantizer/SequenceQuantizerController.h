#ifndef SequenceQuantizerController_h
#define SequenceQuantizerController_h

#include "../ClockedController.h"
#include "SequenceQuantizerDisplay.h"

using namespace eurorack;

#define MAX_SEQUENCE_LENGTH 32

class Sequence {
    public:
        float values[MAX_SEQUENCE_LENGTH];
        bool triggers[MAX_SEQUENCE_LENGTH];
};

class SequenceQuantizerController : public Controller, public ClockedController {
    public:
        SequenceQuantizerController() : Controller(), ClockedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();
        virtual void onClock();

    private:
        TriggerOutput<DigitalOutputDeviceT> triggerOutput = TriggerOutput<DigitalOutputDeviceT>(Hardware::hw.gateOutPin, 20000);

        LinearInput<AnalogInputSumPinT> dejaVuInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 100);
        // LinearInput<AnalogInputSumPinT> ampInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        #if defined(OCTASOURCE_MKII)
            IntegerInput<AnalogInputSumPinT> lengthInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 2, 32);
        #endif

        AnalogTriggerOutput<AnalogOutputDeviceT> triggerOutputs[4] = {
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[7])
        };

        SequenceQuantizerDisplay display;

        Sequence sequence[4];
        uint16_t position = 0;

};

#endif
