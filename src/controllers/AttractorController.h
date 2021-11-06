#ifndef AttractorController_h
#define AttractorController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/attractor/LorenzAttractor.h"
#include "systems/attractor/Lorenz83Attractor.h"
#include "systems/attractor/ThomasAttractor.h"
#include "systems/attractor/AizawaAttractor.h"
#include "systems/attractor/DadrasAttractor.h"
#include "systems/attractor/ChenAttractor.h"
#include "systems/attractor/RosslerAttractor.h"
#include "systems/attractor/HalvorsenAttractor.h"
#include "systems/attractor/ChuaMultiScrollAttractor.h"
#include "systems/attractor/RabinovichFabrikantAttractor.h"
#include "systems/attractor/ThreeScrollUnifiedAttractor.h"
#include "systems/attractor/FourWingAttractor.h"

#define ATTRACTOR_COUNT 12

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

        LorenzAttractor lorenzAttractor1;
        LorenzAttractor lorenzAttractor2;
        Lorenz83Attractor lorenz83Attractor1;
        Lorenz83Attractor lorenz83Attractor2;
        ThomasAttractor thomasAttractor1;
        ThomasAttractor thomasAttractor2;
        AizawaAttractor aizawaAttractor1;
        AizawaAttractor aizawaAttractor2;
        DadrasAttractor dadrasAttractor1;
        DadrasAttractor dadrasAttractor2;
        ChenAttractor chenAttractor1;
        ChenAttractor chenAttractor2;
        RosslerAttractor rosslerAttractor1;
        RosslerAttractor rosslerAttractor2;
        HalvorsenAttractor halvorsenAttractor1;
        HalvorsenAttractor halvorsenAttractor2;
        ChuaMultiScrollAttractor chuaMultiScrollAttractor1;
        ChuaMultiScrollAttractor chuaMultiScrollAttractor2;
        RabinovichFabrikantAttractor rabinovichFabrikantAttractor1;
        RabinovichFabrikantAttractor rabinovichFabrikantAttractor2;
        ThreeScrollUnifiedAttractor threeScrollUnifiedAttractor1;
        ThreeScrollUnifiedAttractor threeScrollUnifiedAttractor2;
        FourWingAttractor fourWingAttractor1;
        FourWingAttractor fourWingAttractor2;

        ContinuousSystemN<3>* attractors1[ATTRACTOR_COUNT] = {
            &lorenzAttractor1,
            &lorenz83Attractor1,
            &thomasAttractor1,
            &aizawaAttractor1,
            &dadrasAttractor1,
            &chenAttractor1,
            &rosslerAttractor1,
            &halvorsenAttractor1,
            &chuaMultiScrollAttractor1,
            &rabinovichFabrikantAttractor1,
            &threeScrollUnifiedAttractor1,
            &fourWingAttractor1
        };

        ContinuousSystemN<3>* attractors2[ATTRACTOR_COUNT] = {
            &lorenzAttractor2,
            &lorenz83Attractor2,
            &thomasAttractor2,
            &aizawaAttractor2,
            &dadrasAttractor2,
            &chenAttractor2,
            &rosslerAttractor2,
            &halvorsenAttractor2,
            &chuaMultiScrollAttractor2,
            &rabinovichFabrikantAttractor2,
            &threeScrollUnifiedAttractor2,
            &fourWingAttractor2
        };

        float amp;
        
        void updateRate();
        void updateAmp();
};

#endif
