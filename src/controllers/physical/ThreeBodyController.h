#ifndef ThreeBodyController_h
#define ThreeBodyController_h

#include "Controller.h"
#include "Hardware.h"
#include "systems/continuous/physical/ThreeBody.h"

class ThreeBodyController : public ParameterizedController<1> {
    public:
        ThreeBodyController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        enum Parameter {
            MODE
        };
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

        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 2);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 1);
        LinearInput<AnalogInputSumPinT> sizeCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0.1, 1);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> dampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 1);
        #endif

        ThreeBody threeBody;
        int oscBody = 0;

        float amp = 1;
        float size = 1;
        float totalGain = 1;
        
        void updateRate();
        void updateAmp();
        void updateSize();
        void updateDamp();

        void printBodies();
        void printBody(Body body);
};

#endif