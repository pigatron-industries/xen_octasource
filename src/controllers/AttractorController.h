#ifndef AttractorController_h
#define AttractorController_h

#include "AbstractOscillatorController.h"
#include "lib/attractor/LorenzAttractor.h"
#include "lib/attractor/Lorenz83Attractor.h"
#include "lib/attractor/ThomasAttractor.h"
#include "lib/attractor/AizawaAttractor.h"
#include "lib/attractor/DadrasAttractor.h"
#include "lib/attractor/ChenAttractor.h"
#include "lib/attractor/RosslerAttractor.h"
#include "lib/attractor/HalvorsenAttractor.h"
#include "lib/attractor/ChuaMultiScrollAttractor.h"

#define ATTRACTOR_COUNT 9

class AttractorController : public Controller {
    public:
        AttractorController() : Controller(ATTRACTOR_COUNT-1) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin, 1);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 1);
        //LinearInput<OctasourceInputDevice> cCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 5);

        LorenzAttractor lorenzAttractor;
        Lorenz83Attractor lorenz83Attractor;
        ThomasAttractor thomasAttractor;
        AizawaAttractor aizawaAttractor;
        DadrasAttractor dadrasAttractor;
        ChenAttractor chenAttractor;
        RosslerAttractor rosslerAttractor;
        HalvorsenAttractor halvorsenAttractor;
        ChuaMultiScrollAttractor chuaMultiScrollAttractor;

        Attractor* attractors[ATTRACTOR_COUNT] = {
            &lorenzAttractor,
            &lorenz83Attractor,
            &thomasAttractor,
            &aizawaAttractor,
            &dadrasAttractor,
            &chenAttractor,
            &rosslerAttractor,
            &halvorsenAttractor,
            &chuaMultiScrollAttractor
        };

        float amp;
        
        void updateRate();
        void updateAmp();
};

#endif
