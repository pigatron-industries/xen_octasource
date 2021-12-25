#ifndef RandomController_h
#define RandomController_h

#include "Controller.h"
#include "lib/Clock.h"
#include "lib/ClockDivider.h"
#include "lib/io/BipolarExpInput.h"

class RandomController : public Controller {
    public:
        RandomController() : Controller(0) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        AnalogGateInput<OctasourceInputDevice> triggerInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);
        LinearInput<OctasourceInputDevice> rateCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, -5, 5, 0, 10);
        LinearInput<OctasourceInputDevice> chanceCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, -5, 5);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> phaseCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, -0.125, 0.125);
        #endif

        AnalogTriggerOutput<OctasourceOutputDevice> triggerOutputs[2] = {
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[0], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[1], 20000)
        };

        Clock clock;
        float chanceValue;
        float noise;
        float amp;

        void tick();
        
};

#endif
