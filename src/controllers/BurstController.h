#ifndef BurstController_h
#define BurstController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include "lib/Burst.h"
#include "display/ParameterPage.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class BurstController : public ParameterizedController<2> {
    public:
        BurstController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();
        virtual int cycleParameter(int amount);
        virtual void cycleValue(int amount);

    private:
        enum Parameter {
            BURST_OUTPUTS,
            BURST_SHAPE
        };

        ParameterPage page;

        AnalogGateInput<AnalogInputPinT> triggerInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.modeCvPin);
        LinearInput<AnalogInputSumPinT> burstRateInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, 1, 30);
        IntegerInput<AnalogInputSumPinT> burstRateMultInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, -8, 7);
        IntegerInput<AnalogInputSumPinT> pulseWidthInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 8);
        IntegerInput<AnalogInputSumPinT> burstLengthInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 1, 30);
        LinearInput<AnalogInputSumPinT> slopeInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, -1, 1);
   
        typedef WaveSelector<Pulse, AsymmetricalTriangle, AsymmetricalTriangle, AsymmetricalTriangle> WaveShapesT;
        WaveShapesT shapes;
        Burst<WaveShapesT&> bursts[8] = {
            Burst<WaveShapesT&>(shapes),
            Burst<WaveShapesT&>(shapes),
            Burst<WaveShapesT&>(shapes),
            Burst<WaveShapesT&>(shapes),
            Burst<WaveShapesT&>(shapes),
            Burst<WaveShapesT&>(shapes),
            Burst<WaveShapesT&>(shapes),
            Burst<WaveShapesT&>(shapes)
        };

        InternalExternalClock externalClock;

        int burstLength = 2;
        int outputs = 8;
        int nextOutput = 0;
        bool sync = false;
        
};

#endif
