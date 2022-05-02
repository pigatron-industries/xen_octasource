#ifndef QuantizerController_h
#define QuantizerController_h

#include "Controller.h"
#include <quantizer/PitchQuantizer.h>

using namespace eurorack;

class QuantizerController : public Controller {
    public:

        QuantizerController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        TriggerOutput<DigitalOutputDeviceT> triggerOutput = TriggerOutput<DigitalOutputDeviceT>(Hardware::hw.gateOutPin, 20000);

        Tuning tuning = Tuning(12);
        ScaleDef scale = ScaleDef({0, 2, 4, 5, 7, 9, 10});
        PitchQuantizer pitchQuantizer = PitchQuantizer(tuning);

        float quantizedValue = 0;

        // void updateRate();
        // void updateAmp();
        // void updateWave();
        // void updatePhase();
        // void updateSync();
};

#endif
