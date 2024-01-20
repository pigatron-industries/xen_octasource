#ifndef ContinuousAttractorController_h
#define ContinuousAttractorController_h

#include "Controller.h"
#include "Hardware.h"
#include "systems/continuous/attractor/LorenzAttractor.h"
#include "systems/continuous/attractor/Lorenz83Attractor.h"
#include "systems/continuous/attractor/ThomasAttractor.h"
#include "systems/continuous/attractor/AizawaAttractor.h"
#include "systems/continuous/attractor/DadrasAttractor.h"
#include "systems/continuous/attractor/ChenAttractor.h"
#include "systems/continuous/attractor/RosslerAttractor.h"
#include "systems/continuous/attractor/HalvorsenAttractor.h"
#include "systems/continuous/attractor/ChuaMultiScrollAttractor.h"
#include "systems/continuous/attractor/RabinovichFabrikantAttractor.h"
#include "systems/continuous/attractor/ThreeScrollUnifiedAttractor.h"
#include "systems/continuous/attractor/FourWingAttractor.h"
#include "display/PixelTrail.h"
#include <eurorack.h>

class ContinuousAttractorController : public ParameterizedController<2> {
    public:
        ContinuousAttractorController() : ParameterizedController() {}
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
        LinearInput<AnalogInputSumPinT> paramsCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 1);
        LinearInput<AnalogInputSumPinT> rotateCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, -M_PI, M_PI);


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
        float rotation;

        PixelTrail<100> pixelTrail1;
        PixelTrail<100> pixelTrail2;
        
        void updateRate();
        void updateAmp();
        void updateParams();
        void updateRotation();
};

#endif
