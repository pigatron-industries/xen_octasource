#ifndef ClockController_h
#define ClockController_h

#include "AbstractOscillatorController.h"
#include "lib/Clock.h"
#include "lib/ClockDivider.h"

using namespace pigatron;

class ClockController : public AbstractOscillatorController {
    public:
        enum Mode {
            INTEGER,
            PPQN24
        };
        ClockController() : AbstractOscillatorController(Mode::PPQN24) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
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

        void tick();
        
};

#endif
