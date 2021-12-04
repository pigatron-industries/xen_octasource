#ifndef DoublePendulumController_h
#define DoublePendulumController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/physical/DoublePendulum.h"
#include "lib/ClockDivider.h"

#define MODEL_COUNT 1
#define SAMPLE_RATE_DIVISOR 2

class DoublePendulumController : public Controller {
    public:
        DoublePendulumController() : Controller(MODEL_COUNT-1) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, 1);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        LinearInput<OctasourceInputDevice> param1CvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0.1, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> param2CvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0.1, 0.9);
        #endif

        DoublePendulum doublePendulum;
        ClockDivider clockDivider = ClockDivider(SAMPLE_RATE_DIVISOR);

        ContinuousSystemN<2>* models[MODEL_COUNT] = {
            &doublePendulum,
        };

        float amp;
        
        void updateRate();
        void updateAmp();
        void updateParams();
};

#endif