#ifndef QuantizerController_h
#define QuantizerController_h

#include <eurorack_dsp.h>
#include "../Controller.h"
#include "../Hardware.h"
#include "lib/ClockDivider.h"

class SlewController : public Controller {
    public:

        SlewController() : Controller(0) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        LinearInput<OctasourceInputDevice> timeCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, -5, 5, 0.1, 1);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        
        ClockDivider clockDivider = ClockDivider(8);
        StateVariableFilter filters[OUTPUT_CV_COUNT];
        float value;  
};

#endif