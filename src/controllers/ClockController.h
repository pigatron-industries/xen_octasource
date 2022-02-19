#ifndef ClockController_h
#define ClockController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include "lib/DistortedClock.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class ClockController : public Controller {
    public:
        enum Mode {
            INTEGER,
            EVEN,
            ODD,
            POWER2,
            PRIME,
            FIBONACCI,
            PPQN24
        };
        ClockController() : Controller(Mode::PPQN24) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        LinearInput<OctasourceInputDevice> rateCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, -5, 5, 0, 20);
        LinearInput<OctasourceInputDevice> distortionXCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 1);
        //LinearInput<OctasourceInputDevice> distortionXCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 100000);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> distortionYCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0, 1);
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

        DistortedClock<TwoLineFunction, 16> clock;

        //Clock clock;
        ClockDivider clockDividers[8];
        Timer timer[8];

        float distortionX, distortionY;

        void tick();
        void updateOutputLeds();
        
};

#endif
