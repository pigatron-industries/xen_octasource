#ifndef QuantizerController_h
#define QuantizerController_h

#include "Controller.h"
#include "lib/quantizer/PitchQuantizer.h"

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

        Scale scale = Scale(12);
        PitchQuantizer pitchQuantizer = PitchQuantizer(scale);

        float quantizedValue = 0;

        // void updateRate();
        // void updateAmp();
        // void updateWave();
        // void updatePhase();
        // void updateSync();
};

#endif
