#ifndef ParametricSystem_h
#define ParametricSystem_h

#include "../Vector.h"

class ParametricSystem {
    public:
        ParametricSystem() {}
        virtual void init(float sampleRate) {
            this->sampleRate = sampleRate;
            sampleTime = 1/sampleRate;
            phase = 0;
        }

        void setFrequency(float frequency) {
            increment = sampleTime * frequency;
        }

        virtual void process() {
            incrementPhase();
        }

    protected:
        float maxPhase = 1;
        float sampleRate;
        float sampleTime;
        float increment;
        float phase;

        void incrementPhase() {
            phase += increment;
            if(phase > maxPhase) {
                phase -= maxPhase;
            } else if(phase < 0) {
                phase += maxPhase;
            }
        }
};

template<int N>
class ParametricSystemN : public ParametricSystem {
    public:
        ParametricSystemN() {}
        float getOutput(int i) { return pos[i]; }
        Vector<2>& getOutput() { return pos; }

    protected:
        Vector<2> pos;
};

#endif