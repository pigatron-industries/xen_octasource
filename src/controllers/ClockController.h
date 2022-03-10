#ifndef ClockController_h
#define ClockController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include "lib/DistortedClock.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class ClockController : public Controller {
    public:
        enum Preset {
            INTEGER,
            EVEN,
            ODD,
            POWER2,
            PRIME,
            FIBONACCI,
            PPQN24
        };

        enum InputMode {
            PRESET,
            CUSTOM1,
            CUSTOM2,
            CUSTOM3,
            CUSTOM4,
            CUSTOM5,
            CUSTOM6,
            CUSTOM7,
            CUSTOM8
        };

        ClockController() : Controller(Preset::PPQN24) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        LinearInput<OctasourceInputDevice> rateCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, -5, 5, 0, 30);
        LinearInput<OctasourceInputDevice> lengthInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 4.1, 16.9);
        LinearInput<OctasourceInputDevice> distortionXCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> distortionYCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0, 1);
        #endif

        AnalogGateOutput<OctasourceOutputDevice> gateOutputs[8] = {
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[0]),
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[1]),
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[2]),
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[3]),
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[4]),
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[5]),
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[6]),
            AnalogGateOutput<OctasourceOutputDevice>(*Hardware::hw.cvOutputPins[7])
        };

        TriggerOutput<> triggerOutput = TriggerOutput<>(Hardware::hw.gateOutPin, 20000);

        DistortedClock<TwoLineFunction, 16> clock;
        DistortedClock<SmoothStepFunction, 16> smoothClock;
        ClockDivider clockDividers[8];
        ClockGate clockGate[8];

        float distortionX, distortionY;

        void tick();
        void setClockDivisorLength(int channel, int divisor, int length);
        void updateOutputLeds();
        
};

#endif
