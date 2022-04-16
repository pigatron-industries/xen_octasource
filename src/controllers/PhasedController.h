#ifndef PhasedController_h
#define PhasedController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#if defined(OCTASOURCE_MKII)
    #define PHASED_LAST_MODE Mode::EXPONENTIAL_VCO
#endif
#if defined(OCTASOURCE_MKI)
    #define PHASED_LAST_MODE Mode::BIPOLAR_LFO
#endif

#define SAMPLERATE_DIVIDER 8

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
        void updateAmp();
        void updateWave();
        void updatePhase();
        void updateSync();
        void resetPhases();

        void setFrequency(float frequency);

        WaveSelector<Sine, Triangle, Saw, Pulse> waveSelector;
        WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&> oscillators[OUTPUT_CV_COUNT] = {
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector)
        };

        Clock clock;
        ClockDivider clockDivider = ClockDivider(SAMPLERATE_DIVIDER);

        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        AnalogGateInput<AnalogInputPinT> hardSyncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.modeCvPin);
        BipolarExpInput<AnalogInputSumPinT> bipolarRateCvInput = BipolarExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin);
        IntegerInput<AnalogInputSumPinT> syncMultCvInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5, 5, -8, 8);
        ExpInput<AnalogInputSumPinT> expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin);
        LinearInput<AnalogInputSumPinT> waveCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 5);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 5);

        float ampValue = 0;
        float syncFrequency;
};

#endif
