#ifndef DiscreteAttractorController_h
#define DiscreteAttractorController_h

#include "Controller.h"
#include "../clock/ClockedController.h"
#include "systems/discrete/attractor/CliffordAttractor.h"
#include "systems/discrete/attractor/TinkerbellMap.h"
#include "systems/discrete/attractor/JoshiBlackmoreMap.h"

using namespace eurorack;

#define MID_FREQUENCY 10
#define MULT_FREQUENCY 3

class DiscreteAttractorController : public ParameterizedController<1>, public ClockedController {
    public:
        enum Parameter {
            ATTRACTOR1,
        };

        DiscreteAttractorController() : ParameterizedController(), ClockedController(MID_FREQUENCY, MULT_FREQUENCY) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void cycleValue(int amount);
        virtual void update();
        virtual void process();
        virtual void onClock();

    private:
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        LinearInput<AnalogInputSumPinT> interpolationCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 1);


        TypeSelector<DiscreteSystemN<2>, 
                        CliffordAttractor,
                        TinkerbellMap,
                        JoshiBlackmoreMap> attractors1;

        float amp;
};

#endif
