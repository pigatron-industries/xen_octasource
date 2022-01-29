#ifndef FrequencyController_h
#define FrequencyController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include "common/WaveShapes.h"
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
