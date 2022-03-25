#ifndef Controls_h
#define Controls_h

#include <eurorack.h>
#include "Hardware.h"
#include "lib/io/BipolarExpInput.h"

class Controls {
    public:
        static AnalogGateInput<AnalogInputPinT> syncInput;
        static BipolarExpInput<AnalogInputSumPinT> bipolarRateCvInput;
        static ExpInput<AnalogInputSumPinT> expRateCvInput;
        static LinearInput<AnalogInputSumPinT> ampCvInput;
        static LinearInput<AnalogInputSumPinT> waveCvInput;
        #if defined(OCTASOURCE_MKII)
            static LinearInput<AnalogInputSumPinT> phaseCvInput;
        #endif

        static TriggerOutput<DigitalOutputDeviceT> triggerOutput;
};

#endif
