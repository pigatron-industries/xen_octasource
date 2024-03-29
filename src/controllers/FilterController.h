#ifndef FilterController_h
#define FilterController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class FilterController : public Controller {
    public:

        FilterController() : Controller() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    private:
        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 1);
        ExpInput<AnalogInputSumPinT> filterCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, 10);
        #if defined(OCTASOURCE_MKII)
            LinearInput<AnalogInputSumPinT> resonanceCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 1);
        #endif


        WaveOscillator<Sine> sineOscillator = WaveOscillator<Sine>();
        WaveOscillator<Triangle> triangleOscillator = WaveOscillator<Triangle>();
        WaveOscillator<Saw> sawOscillator = WaveOscillator<Saw>();
        WaveOscillator<Pulse> pulseOscillator = WaveOscillator<Pulse>();

        BaseOscillator* oscillators[OUTPUT_CV_COUNT] = {
            &sineOscillator, &triangleOscillator, &sawOscillator, &pulseOscillator, 
            &sineOscillator, &triangleOscillator, &sawOscillator, &pulseOscillator
        };
        StateVariableFilter filters[OUTPUT_CV_COUNT];

        float ampValue;

        void updateRate();
        void updateFilterFrequency();
        void updateFilterResonance();
        void updateAmp();
};

#endif
