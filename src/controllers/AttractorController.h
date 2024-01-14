#ifndef AttractorController_h
#define AttractorController_h

#include "../Controller.h"
#include "../Hardware.h"
#include "systems/differential/attractor/LorenzAttractor.h"
#include "systems/differential/attractor/Lorenz83Attractor.h"
#include "systems/differential/attractor/ThomasAttractor.h"
#include "systems/differential/attractor/AizawaAttractor.h"
#include "systems/differential/attractor/DadrasAttractor.h"
#include "systems/differential/attractor/ChenAttractor.h"
#include "systems/differential/attractor/RosslerAttractor.h"
#include "systems/differential/attractor/HalvorsenAttractor.h"
#include "systems/differential/attractor/ChuaMultiScrollAttractor.h"
#include "systems/differential/attractor/RabinovichFabrikantAttractor.h"
#include "systems/differential/attractor/ThreeScrollUnifiedAttractor.h"
#include "systems/differential/attractor/FourWingAttractor.h"
#include "display/PixelTrail.h"
#include <eurorack.h>

class AttractorController : public ParameterizedController<2> {
    public:
        AttractorController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();

    private:
        enum Parameter {
            ATTRACTOR1,
            ATTRACTOR2
        };

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

        PixelTrail<100> pixelTrail1;
        PixelTrail<100> pixelTrail2;
        
        void updateRate();
        void updateAmp();
};

#endif
