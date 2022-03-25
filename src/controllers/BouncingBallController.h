#ifndef BouncingBallController_h
#define BouncingBallController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/physical/BouncingBall.h"

class BouncingBallController : public Controller {
    public:
        enum Mode {
            BOUNCE,
            TRIGGERS,
            ROTATE
        };
        BouncingBallController() : Controller(Mode::ROTATE) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<AnalogInputPinT> expRateCvInput = ExpInput<AnalogInputPinT>(Hardware::hw.rateCvPin, 10);
        LinearInput<AnalogInputPinT> ampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        LinearInput<AnalogInputPinT> dampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.waveCvPin, -5, 5, 0.5, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputPinT> param2CvInput = LinearInput<AnalogInputPinT>(Hardware::hw.phaseCvPin, -5, 5, 0.1, 0.9);
        #endif

        AnalogTriggerOutput<AnalogOutputDeviceT> triggerOutputs[4] = {
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[0], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[2], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[4], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[6], 20000)
        };

        BouncingBall bouncingBalls[4] = {
            BouncingBall(),
            BouncingBall(),
            BouncingBall(),
            BouncingBall()
        };

        int rotateOutput = 0;

        float amp;
        
        void updateRate();
        void updateAmp();
        void updateDamp();
};

#endif
