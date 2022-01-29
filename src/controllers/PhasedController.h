#ifndef PhasedController_h
#define PhasedController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include "common/WaveShapes.h"
#include <eurorack_dsp.h>

#if defined(OCTASOURCE_MKII)
    #define PHASED_LAST_MODE Mode::EXPONENTIAL_VCO
#endif
#if defined(OCTASOURCE_MKI)
    #define PHASED_LAST_MODE Mode::BIPOLAR_LFO
#endif

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
        void updateRateBipolar();
        void updateRateExponential();
        void updateAmp();
        void updateWave();
        void updatePhase();

        WaveList<4> waveList = WaveList<4>(WaveShapes::waveShapes);
        WaveOscillator<WaveList<4>&> oscillators[OUTPUT_CV_COUNT] = {
            WaveOscillator<WaveList<4>&>(waveList), 
            WaveOscillator<WaveList<4>&>(waveList), 
            WaveOscillator<WaveList<4>&>(waveList), 
            WaveOscillator<WaveList<4>&>(waveList), 
            WaveOscillator<WaveList<4>&>(waveList), 
            WaveOscillator<WaveList<4>&>(waveList), 
            WaveOscillator<WaveList<4>&>(waveList), 
            WaveOscillator<WaveList<4>&>(waveList)
        };

        float ampValue = 0;
};

#endif
