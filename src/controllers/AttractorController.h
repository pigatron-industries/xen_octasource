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
#include <eurorack.h>

class AttractorController : public Controller {
    public:
        AttractorController() : Controller(attractors1.getSize()-1) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 1);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        //LinearInput<AnalogInputSumPinT> cCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 5);

        TypeSelector<ContinuousSystemN<3>, 
                        LorenzAttractor, 
                        Lorenz83Attractor, 
                        ThomasAttractor, 
                        AizawaAttractor, 
                        DadrasAttractor, 
                        ChenAttractor, 
                        RosslerAttractor, 
                        HalvorsenAttractor, 
                        ChuaMultiScrollAttractor, 
                        RabinovichFabrikantAttractor, 
                        ThreeScrollUnifiedAttractor, 
                        FourWingAttractor> attractors1;
        TypeSelector<ContinuousSystemN<3>, 
                        LorenzAttractor, 
                        Lorenz83Attractor, 
                        ThomasAttractor, 
                        AizawaAttractor, 
                        DadrasAttractor, 
                        ChenAttractor, 
                        RosslerAttractor, 
                        HalvorsenAttractor, 
                        ChuaMultiScrollAttractor, 
                        RabinovichFabrikantAttractor, 
                        ThreeScrollUnifiedAttractor, 
                        FourWingAttractor> attractors2;

        float amp;
        
        void updateRate();
        void updateAmp();
};

#endif
