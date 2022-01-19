#ifndef PhasedController_h
#define PhasedController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace pigatron;

#if defined(OCTASOURCE_MKII)
    #define PHASED_LAST_MODE Mode::EXPONENTIAL_VCO
#endif
#if defined(OCTASOURCE_MKI)
    #define PHASED_LAST_MODE Mode::BIPOLAR_LFO
#endif

class PhasedController : public Controller {
    public:
        enum Mode {
            BIPOLAR_LFO,
            EXPONENTIAL_VCO
        };

        PhasedController() : Controller(PHASED_LAST_MODE) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        void updateRate();
        void updateRateBipolar();
        void updateRateExponential();
        void updateAmp();
        void updateWave();
        void updatePhase();

        Oscillator oscillators[OUTPUT_CV_COUNT];

        AnalogGateInput<OctasourceInputDevice> triggerInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);
        BipolarExpInput<OctasourceInputDevice> bipolarRateCvInput = BipolarExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
        LinearInput<OctasourceInputDevice> waveCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 5);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 5);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> phaseCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, -0.125, 0.125);
        #endif
};

#endif
