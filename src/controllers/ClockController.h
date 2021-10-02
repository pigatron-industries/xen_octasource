#ifndef ClockController_h
#define ClockController_h

#include "AbstractOscillatorController.h"
#include "Clock.h"
#include "ClockDivider.h"

using namespace pigatron;

class ClockController : public AbstractOscillatorController {
    public:
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    private:
        AnalogTriggerOutput<OctasourceOutputDevice> triggerOutputs[8] = {
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[0]),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[1]),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[2]),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[3]),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[7])
        };

        Clock clock;
        ClockDivider clockDividers[8];

        void tick();
        
};

#endif
