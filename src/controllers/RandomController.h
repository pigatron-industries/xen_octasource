#ifndef RandomController_h
#define RandomController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

class RandomController : public Controller {
    public:
        RandomController() : Controller(0) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        LinearInput<AnalogInputPinT> rateCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.rateCvPin, -5, 5, 0, 10);
        LinearInput<AnalogInputPinT> chanceCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.waveCvPin, -5, 5, -5, 5);
        LinearInput<AnalogInputPinT> ampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputPinT> phaseCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.phaseCvPin, -5, 5, -0.125, 0.125);
        #endif

        AnalogTriggerOutput<AnalogOutputDeviceT> triggerOutputs[4] = {
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[0], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[2], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[4], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[6], 20000)
        };

        Clock clock;
        float chanceValue;
        float amp;

        void tick();
        
};

#endif
