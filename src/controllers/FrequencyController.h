#ifndef FrequencyController_h
#define FrequencyController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define SAMPLERATE_DIVIDER 8

class FrequencyController : public ParameterizedController<1> {
    public:
        FrequencyController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    protected:
        enum Parameter {
            MODE
        };
        enum Mode {
            LINEAR,
            EXP,
            POLYRHYTHM,
            INTERVAL,
            UNCORRELATED,
            PLANETARY
        };

        void setRate(float baseFrequency);
        void updateRate();
        void updateAmp();
        void updateWave();
        void updateSync();

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
        ExpInput<AnalogInputSumPinT> rateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, 10);
        IntegerInput<AnalogInputSumPinT> syncMultCvInput = IntegerInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin, -5.0, 5.0, -7, 7);
        LinearInput<AnalogInputSumPinT> ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 5);
        LinearInput<AnalogInputSumPinT> waveCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 5);

        float ampValue = 0;
        float syncFrequency;
};

#endif
