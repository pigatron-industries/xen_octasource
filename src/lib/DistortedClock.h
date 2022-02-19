#ifndef DistortedClock_h
#define DistortedClock_h

#include <eurorack_dsp.h>

namespace eurorack {

    template<class F, int N>
    class DistortedClock : public Clock {
        public:
            DistortedClock() { calculatePhaseIncrements(); }
            F& getFunction() { return distortionFunction; }
            void calculatePhaseIncrements();

        protected:
            virtual bool processInternal();

        private:
            int currentTick = -1;
            float phaseMaxs[N];
            F distortionFunction;

            float phaseDivision = 1.0/N;

            
    };

    template<class F, int N>
    inline bool DistortedClock<F, N>::processInternal() {
        bool ticked = Clock::processInternal();
        if(ticked) {
            currentTick++;
            currentTick %= N;
            setPhaseMax(phaseMaxs[currentTick]);
        }
        return ticked;
    }

    template<class F, int N>
    inline void DistortedClock<F, N>::calculatePhaseIncrements() {
        float phase = 0;
        float distortedPhase = 0;

        for(size_t i = 0; i < N; i++) {
            float nextPhase = phase + phaseDivision;
            float nextDistortedPhase = distortionFunction.get(nextPhase);

            phaseMaxs[i] = (nextDistortedPhase - distortedPhase)*N;

            phase = nextPhase;
            distortedPhase = nextDistortedPhase;
        }
    }

}

#endif
