#ifndef DistortedClock_h
#define DistortedClock_h

#include <eurorack_dsp.h>

#define DISTORTION_TICKS_MAX 16

namespace eurorack {

    template<class F>
    class DistortedClock : public InternalExternalClock {
        public:
            DistortedClock() { calculatePhaseIncrements(); }
            F& getFunction() { return distortionFunction; }
            void setLength(int ticksMax) { this->ticksMax = ticksMax; phaseDivision = 1.0/ticksMax; }
            void calculatePhaseIncrements();

        protected:
            virtual bool processInternal();

        private:
            int currentTick = -1;
            int ticksMax = DISTORTION_TICKS_MAX;
            float phaseMaxs[DISTORTION_TICKS_MAX];
            F distortionFunction;

            float phaseDivision = 1.0/ticksMax;
    };

    template<class F>
    inline bool DistortedClock<F>::processInternal() {
        bool ticked = InternalExternalClock::processInternal();
        if(ticked) {
            currentTick++;
            currentTick %= ticksMax;
            setPhaseMax(phaseMaxs[currentTick]);
        }
        return ticked;
    }

    template<class F>
    inline void DistortedClock<F>::calculatePhaseIncrements() {
        float phase = 0;
        float distortedPhase = 0;

        for(int i = 0; i < ticksMax; i++) {
            float nextPhase = phase + phaseDivision;
            float nextDistortedPhase = distortionFunction.get(nextPhase);

            phaseMaxs[i] = (nextDistortedPhase - distortedPhase) * ticksMax;

            phase = nextPhase;
            distortedPhase = nextDistortedPhase;
        }
    }

}

#endif
