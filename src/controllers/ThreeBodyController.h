#ifndef ThreeBodyController_h
#define ThreeBodyController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/physical/ThreeBody.h"

class ThreeBodyController : public Controller {
    public:
        enum Mode {
            STABLE1,
            STABLE_BUTTERFLY1,
            STABLE_DRAGONFLY1,
            STABLE_FIGURE8,
            BROUKE_A2,
            STABLE4,
            CHAOTIC_BOUNCE1,
            CHAOTIC_BOUNCE2,
            CHAOTIC_BOUNCE3,
            CHAOTIC_WRAP1
        };

        ThreeBodyController() : Controller(Mode::CHAOTIC_WRAP1) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, 2);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        LinearInput<OctasourceInputDevice> param1CvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0.1, 1);
        LinearInput<OctasourceInputDevice> param2CvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0.1, 0.9);

        ThreeBody threeBody;

        float amp = 1;
        
        void updateRate();
        void updateAmp();
        void updateParams();

        void printBodies();
        void printBody(Body body);
};

#endif
