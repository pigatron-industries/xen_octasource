#ifndef Burst_h
#define Burst_h

#include <eurorack_dsp.h>

template<class T = WaveShape>
class Burst {
    public:
        Burst(T t) : oscillator(t) {  }

        void init(float sampleRate) {
            clock.init(sampleRate);
            oscillator.init(sampleRate);
            oscillator.setAmplitude(0.5);
        }

        void start(float frequency, int length) {
            this->length = length;
            counter = 0;
            active = true;
            oscillator.setFrequency(frequency);
            oscillator.setPhase(0);
            clock.setFrequency(frequency);
            clock.reset();
        }

        float process() {
            if(active && clock.process()) {
                counter++;
                if(counter >= length) {
                    active = false;
                }
            }

            if(active) {
                return oscillator.process() + 0.5;
            }

            return 0;
        }

        int length;
        int counter;
        bool active;
        Clock clock;
        WaveOscillator<T> oscillator;
};

#endif