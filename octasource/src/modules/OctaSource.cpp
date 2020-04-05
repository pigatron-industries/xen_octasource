#include "OctaSource.h"

#include "modes/PhasedSource.h"
#include "modes/MultipliedSource.h"
#include "modes/UncorrelatedSource.h"
#include "modes/BurstSource.h"

#define AMP_SCALE 5

OctaSource::OctaSource() {
    _mode = 0;
    _source[0] = new PhasedSource();
    _source[1] = new MultipliedSource();
    _source[2] = new UncorrelatedSource();
    _source[3] = new BurstSource();
    initMode();
}

void OctaSource::cycleMode() {
    _mode += 1;
    if(_mode >= MODE_COUNT) {
        _mode = 0;
    }
    initMode();
}

void OctaSource::initMode() {
    _source[_mode]->init();
}

void OctaSource::setFrequencyHz(float frequencyHz) {
    _source[_mode]->setFrequencyHz(frequencyHz);
}

void OctaSource::setAmplitude(float amplitude) {
    _source[_mode]->setAmplitude(amplitude);
}

void OctaSource::setWave(float wave) {
    _source[_mode]->setWave(wave);
}

void OctaSource::trigger() {
    _source[_mode]->trigger();
}

void OctaSource::execute(unsigned long timeDiff) {
    _source[_mode]->execute(timeDiff);
}

float OctaSource::getOutput(uint8_t index) {
    return _source[_mode]->getOutput(index);
}
