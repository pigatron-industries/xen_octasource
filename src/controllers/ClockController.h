#ifndef ClockController_h
#define ClockController_h

#include "AbstractOscillatorController.h"
#include "Clock.h"
#include "ClockDivider.h"

using namespace pigatron;

class ClockController : public AbstractOscillatorController {
    public:
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        AnalogTriggerOutput<MAX11300Device> triggerOutputs[OUTPUT_CV_COUNT] = {
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[0]),
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[1]),
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[2]),
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[3]),
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[4]),
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[5]),
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[6]),
            AnalogTriggerOutput<MAX11300Device>(*Hardware::hw.cvOutputPins[7])
        };

        Clock clock;
        ClockDivider clockDividers[8];

        void tick();
        
};

#endif
