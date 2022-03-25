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
        LinearInput<AnalogInputSumPinT> rateCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 0, 10);
        LinearInput<AnalogInputSumPinT> chanceCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, -5, 5);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> phaseCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, -0.125, 0.125);
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
