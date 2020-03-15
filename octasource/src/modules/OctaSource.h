#ifndef OctaSource_h
#define OctaSource_h

#include <inttypes.h>

#include "Oscillator.h"

#define OSCILLATOR_COUNT 8

enum OctasourceMode_t {
  	modePhased,
    modeMultiplied,
    modeUncorrelated,
};


class OctaSource {

public:
    OctaSource();
    void setMode(OctasourceMode_t mode);
    void execute(unsigned long timeDiff);
    float getOutput(uint8_t index);

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float amplitude);
    void setWave(float wave);

private:
    Oscillator _oscillators[OSCILLATOR_COUNT];
    float _outputs[OSCILLATOR_COUNT];

    OctasourceMode_t _mode;

    void setFrequencyAll(float frequencyHz);
    void setFrequencyMultipliedMode(float frequencyHz);

    void matchPhases();
    void phasedModeInit();




};

#endif
