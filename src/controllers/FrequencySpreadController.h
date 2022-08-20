#ifndef FrequencySpreadController_h
#define FrequencySpreadController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class FrequencySpreadController : public Controller {
    public:
        enum Mode {
            EXP
        };

        FrequencySpreadController() : Controller(Mode::EXP) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    protected:
        void setRate(float baseFrequency, float spread);
        void updateRate();
        void updateAmp();
        void updateWave();

        WaveSelector<Sine, Triangle, Saw, Pulse> waveSelector;
        WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&> oscillators[OUTPUT_CV_COUNT-1] = {
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector), 
            WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector)
        };

        AnalogGateInput<AnalogInputPinT> syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
        ExpInput<AnalogInputSumPinT> rateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 10);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 5);
        LinearInput<AnalogInputSumPinT> waveCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 5);
        LinearInput<AnalogInputSumPinT> spreadCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 1);

        float ampValue = 0;
        float syncFrequency;
};

#endif
