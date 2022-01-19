#ifndef FilterController_h
#define FilterController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace pigatron;

class FilterController : public Controller {
    public:

        FilterController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        AnalogGateInput<OctasourceInputDevice> triggerInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);
        BipolarExpInput<OctasourceInputDevice> bipolarRateCvInput = BipolarExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 5);
        LinearInput<OctasourceInputDevice> filterCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 100);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> resonanceCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0, 1);
        #endif

        Oscillator oscillators[OUTPUT_CV_COUNT];
        StateVariableFilter filters[OUTPUT_CV_COUNT];

        void updateRateBipolar();
        void updateFilterFrequency();
        void updateFilterResonance();
        void updateAmp();
};

#endif
