#ifndef FilterController_h
#define FilterController_h

#include <eurorack_dsp.h>
#include "AbstractOscillatorController.h"


class FilterController : public AbstractOscillatorController {
    public:

        FilterController() : AbstractOscillatorController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        LinearInput<OctasourceInputDevice> filterCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 100);
        LinearInput<OctasourceInputDevice> resonanceCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0, 1);

        StateVariableFilter filters[OUTPUT_CV_COUNT];

        void updateRateBipolar();
        void updateFilterFrequency();
        void updateFilterResonance();
};

#endif
