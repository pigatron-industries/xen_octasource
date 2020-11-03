#include "OctaSource.h"
#include "../Config.h"

#include "modes/PhasedSource.h"
#include "modes/MultipliedSource.h"
#include "modes/UncorrelatedSource.h"
#include "modes/BurstSource.h"
#include "modes/ClockSource.h"
#include "modes/BoidSource.h"

#define AMP_SCALE 5

OctaSource::OctaSource() {
    _source[0] = new PhasedSource();
    _source[1] = new MultipliedSource();
    _source[2] = new UncorrelatedSource();
    _source[3] = new BurstSource();
    _source[4] = new ClockSource();
    _source[5] = new BoidSource();
}

uint8_t OctaSource::cycleMode() {
    _mode += 1;
    if(_mode >= MODE_COUNT) {
        _mode = 0;
    }
    initMode();
    return _mode;
}

void OctaSource::setMode(uint8_t mode) {
    _mode = mode;
    initMode();
}

uint8_t OctaSource::cycleSubMode(long movement) {
    return _source[_mode]->setModeIncrement(movement);
}

void OctaSource::setSubMode(uint8_t submode) {
    _source[_mode]->setMode(submode);
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

void OctaSource::setPosition(float position) {
    _source[_mode]->setPosition(position);
}

void OctaSource::setTriggerValue(float value) {
    _source[_mode]->setTriggerValue(value);
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

bool OctaSource::getTriggerOut() {
    return _source[_mode]->getTriggerOut();
}

float OctaSource::getFrequencyHz() {
    return _source[_mode]->getFrequencyHz();
}

float OctaSource::getPosition() {
    return _source[_mode]->getPosition();
}

long OctaSource::getSubMode() {
    return _source[_mode]->getMode();
}
