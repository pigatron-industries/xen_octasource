#ifndef ThreeBodyController_h
#define ThreeBodyController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/physical/ThreeBody.h"

class ThreeBodyController : public Controller {
    public:
        enum Mode {
            STABLE1,
            FIGURE8_STABLE_V1A,
            FIGURE8_CHAOTIC_V17A,
            BROUCKE_A2,
            BROUCKE_ASYMETRICAL,
            CHAOTIC1_BOUNCE,
            CHAOTIC1_ANTIGRAV,
            CHAOTIC1_WRAP,
            CHAOTIC2,
            CHAOTIC3
        };

        ThreeBodyController() : Controller(Mode::CHAOTIC3) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, 2);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0.1, 1);
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
