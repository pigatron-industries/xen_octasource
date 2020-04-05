#ifndef OctaSource_h
#define OctaSource_h

#include <inttypes.h>

#include "generators/Oscillator.h"
#include "modes/AbstractSource.h"

#define MODE_COUNT 4


class OctaSource {

public:
    OctaSource();
    void cycleMode();


    void execute(unsigned long timeDiff);
    float getOutput(uint8_t index);

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float amplitude);
    void setWave(float wave);
    void trigger();

    uint8_t getMode() {
        return _mode;
    }

private:

    AbstractSource* _source[MODE_COUNT];
    uint8_t _mode;

    void initMode();




    // Oscillator _oscillators[OSCILLATOR_COUNT];
    // float _outputs[OSCILLATOR_COUNT];
    //
    // void setFrequencyAll(float frequencyHz);
    // void setFrequencyMultipliedMode(float frequencyHz);
    // void setFrequencyUncorrelatedMode(float frequencyHz);
    //
    // void initPhaseAll();
    // void initPhasedMode();
    // void initUncorrelatedMode();




};

#endif
