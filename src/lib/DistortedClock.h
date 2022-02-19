#ifndef DistortedClock_h
#define DistortedClock_h

#include <eurorack_dsp.h>

namespace eurorack {

    template<class F, int N>
    class DistortedClock : public Clock {
        public:
            DistortedClock() { calculatePhaseIncrements(); }
            F& getFunction() { return distortionFunction; }
            void setLength(int length) { this->length = length; phaseDivision = 1.0/length; }
            void calculatePhaseIncrements();

        protected:
            virtual bool processInternal();

        private:
            int currentTick = -1;
            int length = N;
            float phaseMaxs[N];
            F distortionFunction;

            float phaseDivision = 1.0/N;
    };

    template<class F, int N>
    inline bool DistortedClock<F, N>::processInternal() {
        bool ticked = Clock::processInternal();
        if(ticked) {
            currentTick++;
            currentTick %= length;
            setPhaseMax(phaseMaxs[currentTick]);
        }
        return ticked;
    }

    template<class F, int N>
    inline void DistortedClock<F, N>::calculatePhaseIncrements() {
        float phase = 0;
        float distortedPhase = 0;

        for(int i = 0; i < length; i++) {
            float nextPhase = phase + phaseDivision;
            float nextDistortedPhase = distortionFunction.get(nextPhase);

            phaseMaxs[i] = (nextDistortedPhase - distortedPhase)*length;

            phase = nextPhase;
            distortedPhase = nextDistortedPhase;
        }
    }

}

#endif
