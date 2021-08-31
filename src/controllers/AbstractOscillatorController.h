#ifndef AbstractOscillatorController_h
#define AbstractOscillatorController_h

#include <Arduino.h>
#include <eurorack_dsp.h>
#include "../Controller.h"
#include "../Hardware.h"
#include "BipolarExpInput.h"

using namespace pigatron;

class AbstractOscillatorController : public Controller {
    public:
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    protected:
        Oscillator oscillators[OUTPUT_CV_COUNT];
        float outputValues[OUTPUT_CV_COUNT];

        BipolarExpInput<MAX11300AnalogInputPin&> ratePotInput = BipolarExpInput<MAX11300AnalogInputPin&>(Hardware::hw.ratePotPin);
        LinearInput<MAX11300AnalogInputPin&> wavePotInput = LinearInput<MAX11300AnalogInputPin&>(Hardware::hw.wavePotPin, -5, 5, 0, 5);
        LinearInput<MAX11300AnalogInputPin&> ampPotInput = LinearInput<MAX11300AnalogInputPin&>(Hardware::hw.ampPotPin, -5, 5, 0, 5);

        void updateRate();
        void updateAmp();
        void updateWave();
        void updateOutput();
};

#endif
