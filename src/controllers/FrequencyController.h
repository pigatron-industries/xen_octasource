#ifndef FrequencyController_h
#define FrequencyController_h

#include "Controller.h"
#include "lib/io/BipolarExpInput.h"
#include <eurorack_dsp.h>

using namespace pigatron;

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

        Sine sine;
        Triangle triangle;
        Saw saw;
        Pulse pulse;

        WaveShape* waveShapes[4] = {&sine, &triangle, &saw, &pulse};
        WaveList<4> waveList = WaveList<4>(waveShapes);

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

        AnalogGateInput<OctasourceInputDevice> triggerInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);
        BipolarExpInput<OctasourceInputDevice> bipolarRateCvInput = BipolarExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
        ExpInput<OctasourceInputDevice> expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
        LinearInput<OctasourceInputDevice> waveCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 5);
        LinearInput<OctasourceInputDevice> ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 5);
        #if defined(OCTASOURCE_MKII)
            LinearInput<OctasourceInputDevice> phaseCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, -0.125, 0.125);
        #endif
};

#endif
