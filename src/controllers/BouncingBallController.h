#ifndef BouncingBallController_h
#define BouncingBallController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/physical/BouncingBall.h"

class BouncingBallController : public Controller {
    public:
        enum Mode {
            GRAVITY,
            ROTATE
        };
        BouncingBallController() : Controller(Mode::ROTATE) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        AnalogGateInput<OctasourceInputDevice> triggerInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, 10);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        LinearInput<OctasourceInputDevice> dampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0.5, 1);
        TriggerOutput<> triggerOutput = TriggerOutput<>(Hardware::hw.gateOutPin, 20000);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> param2CvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0.1, 0.9);
        #endif

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
