#ifndef Controls_h
#define Controls_h

#include <eurorack.h>
#include "Hardware.h"
#include "lib/io/BipolarExpInput.h"

class Controls {
    public:
        static AnalogGateInput<OctasourceInputDevice> syncInput;
        static BipolarExpInput<OctasourceInputDevice> bipolarRateCvInput;
        static ExpInput<OctasourceInputDevice> expRateCvInput;
        static LinearInput<OctasourceInputDevice> ampCvInput;

        // mod 1
        static LinearInput<OctasourceInputDevice> waveCvInput;

        // mod 2
        #if defined(OCTASOURCE_MKII)
            static LinearInput<OctasourceInputDevice> mod2CvInput;
        #endif

        static TriggerOutput<> triggerOutput;
};

#endif
