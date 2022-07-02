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
            slopeGenerator.init(sampleRate);
            slopeGenerator.getShape().setStartValue(0);
            slopeGenerator.getShape().setEndValue(1);
        }

        void start(float frequency, int length, float slope = 0) {
            this->length = length;
            counter = 0;
            active = true;
            if(slope < 0) {
                slopeGenerator.getShape().setStartValue(1);
                slopeGenerator.getShape().setEndValue(1+slope);
            } else {
                slopeGenerator.getShape().setStartValue(1-slope);
                slopeGenerator.getShape().setEndValue(1);
            }
            oscillator.setFrequency(frequency);
            oscillator.setPhase(0);
            slopeGenerator.setFrequency(frequency/length);
            slopeGenerator.setPhase(0);
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
                return (oscillator.process() + 0.5) * slopeGenerator.process();
            }

            return 0;
        }

        int length;
        int counter;
        bool active;
        Clock clock;
        WaveOscillator<T> oscillator;
        WaveOscillator<Line> slopeGenerator;
};

#endif