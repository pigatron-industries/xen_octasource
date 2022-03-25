#ifndef Controls_h
#define Controls_h

#include <eurorack.h>
#include "Hardware.h"
#include "lib/io/BipolarExpInput.h"

class Controls {
    public:
        static Controls controls;

        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        BipolarExpInput<AnalogInputSumPinT> bipolarRateCvInput = BipolarExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin);
        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 5);
        LinearInput<AnalogInputSumPinT> waveCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 5);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> phaseCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 5);
        #endif

        TriggerOutput<DigitalOutputDeviceT> triggerOutput = TriggerOutput<DigitalOutputDeviceT>(Hardware::hw.gateOutPin, 20000);
};

#endif
