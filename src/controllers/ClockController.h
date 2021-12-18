#ifndef ClockController_h
#define ClockController_h

#include "Controller.h"
#include "lib/Clock.h"
#include "lib/ClockDivider.h"
#include "lib/io/BipolarExpInput.h"

class ClockController : public Controller {
    public:
        enum Mode {
            INTEGER,
            EVEN,
            ODD,
            POWER2,
            PPQN24
        };
        ClockController() : Controller(Mode::PPQN24) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        AnalogGateInput<OctasourceInputDevice> triggerInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);
        LinearInput<OctasourceInputDevice> rateCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, -5, 5, 0, 10);
        //LinearInput<OctasourceInputDevice> waveCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 5);
        LinearInput<OctasourceInputDevice> sloppinessCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 100000);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> phaseCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, -0.125, 0.125);
        #endif

        AnalogTriggerOutput<OctasourceOutputDevice> triggerOutputs[8] = {
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[0], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[1], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[2], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[3], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[4], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[5], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[6], 20000),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[7], 20000)
        };

        Clock clock;
        ClockDivider clockDividers[8];
        Timer timer[8];

        float sloppiness = 0;

        void tick();
        
};

#endif
