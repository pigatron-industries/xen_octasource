#ifndef FrequencyController_h
#define FrequencyController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

class FrequencyController : public Controller {
    public:
        enum Mode {
            LINEAR,
            EXP,
            UNCORRELATED,
            PLANETARY
        };

        FrequencyController() : Controller(Mode::PLANETARY) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    protected:
        void setRate(float baseFrequency);
        void updateRate();
        void updateAmp();
        void updateWave();

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

        float ampValue = 0;
};

#endif
