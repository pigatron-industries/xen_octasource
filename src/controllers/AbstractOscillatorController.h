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
        AbstractOscillatorController(int lastMode = 0) : Controller(lastMode) {}
        virtual void init();
        virtual void update();
        virtual void process();

    protected:
        Oscillator oscillators[OUTPUT_CV_COUNT];
        float outputValues[OUTPUT_CV_COUNT];

        AnalogGateInput<MAX11300Device> triggerInput = AnalogGateInput<MAX11300Device>(Hardware::hw.triggerInPin);
        BipolarExpInput<MAX11300Device> ratePotInput = BipolarExpInput<MAX11300Device>(Hardware::hw.ratePotPin);
        LinearInput<MAX11300Device> wavePotInput = LinearInput<MAX11300Device>(Hardware::hw.wavePotPin, -5, 5, 0, 5);
        LinearInput<MAX11300Device> ampPotInput = LinearInput<MAX11300Device>(Hardware::hw.ampPotPin, -5, 5, 0, 5);

        void updateRate();
        void updateAmp();
        void updateWave();
};

#endif
