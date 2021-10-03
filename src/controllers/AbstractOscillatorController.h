#ifndef AbstractOscillatorController_h
#define AbstractOscillatorController_h

#include <Arduino.h>
#include <eurorack_dsp.h>
#include "../Controller.h"
#include "../Hardware.h"
#include "lib/io/BipolarExpInput.h"

using namespace pigatron;

class AbstractOscillatorController : public Controller {
    public:
        AbstractOscillatorController(int lastMode = 0) : Controller(lastMode) {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process();

    protected:
        Oscillator oscillators[OUTPUT_CV_COUNT];

        AnalogGateInput<OctasourceInputDevice> triggerInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);

        BipolarExpInput<OctasourceInputDevice> bipolarRateCvInput = BipolarExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);

        LinearInput<OctasourceInputDevice> waveCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 5);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 5);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> phaseCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, -0.125, 0.125);
        #endif

        void updateRateBipolar();
        void updateRateExponential();
        void updateAmp();
        void updateWave();
};

#endif
