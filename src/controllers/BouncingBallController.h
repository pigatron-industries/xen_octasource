#ifndef BouncingBallController_h
#define BouncingBallController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/differential/physical/BouncingBall.h"

class BouncingBallController : public ParameterizedController<1> {
    public:
        BouncingBallController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();

    private:
        enum Parameter {
            MODE
        };
        enum Mode {
            BOUNCE_STEPPED,
            BOUNCE_TRIGGERS,
            STEPPED_TRIGGERS,
            ROTATE
        };

        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 1);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        LinearInput<AnalogInputSumPinT> dampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0.5, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> param2CvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0.1, 0.9);
        #endif

        AnalogTriggerOutput<AnalogOutputDeviceT> triggerOutputs[4] = {
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[1], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[3], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[5], 20000),
            AnalogTriggerOutput<AnalogOutputDeviceT>(*Hardware::hw.cvOutputPins[7], 20000)
        };

        BouncingBall bouncingBalls[4] = {
            BouncingBall(),
            BouncingBall(),
            BouncingBall(),
            BouncingBall()
        };

        int rotateOutput = 0;

        float amp;
        
        void setMode(uint8_t mode);
        void updateRate();
        void updateAmp();
        void updateDamp();
};

#endif
