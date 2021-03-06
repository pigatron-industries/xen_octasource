#include "ClockSource.h"
#include <Arduino.h>

#define PPQN24 24
#define TRIGGER_TIME 1000

#define CLOCK_MODE_PPQN24 0
#define CLOCK_MODE_DIVIDE 1

#define TRIG_HIGH 5
#define TRIG_LOW 0

void ClockSource::init() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setWave(4);
    }
    _pulseCount = 0;
    _modeCount = 2;
    _outputRotation = 0;
}

void ClockSource::setAmplitude(float rotationTriggerValue) {
    _rotationTriggerValue = rotationTriggerValue;
}

void ClockSource::execute(unsigned long timeDiff) {
    _oscillators[0].execute(timeDiff);

    if(_rotationTrigger.update(_rotationTriggerValue)) {
        if(_rotationTrigger.risingEdge()) {
            rotateOutputs();
        }
    }

    if(_oscillators[0].getTriggerOut()) {
        _triggerTimer.start(TRIGGER_TIME);
        _pulseCount++;
        if(_pulseCount == PPQN24*12) {
           _pulseCount = 0;
        }

        if(_mode == CLOCK_MODE_PPQN24) {
            _outputs[getRotatedOutputIndex(0)] = _pulseCount % 1 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(1)] = _pulseCount % 6 == 0 ? TRIG_HIGH : TRIG_LOW;  //Sixteenth note
            _outputs[getRotatedOutputIndex(2)] = _pulseCount % 8 == 0 ? TRIG_HIGH : TRIG_LOW;  //Triplet
            _outputs[getRotatedOutputIndex(3)] = _pulseCount % 12 == 0 ? TRIG_HIGH : TRIG_LOW; //Eighth note
            _outputs[getRotatedOutputIndex(4)] = _pulseCount % 24 == 0 ? TRIG_HIGH : TRIG_LOW; //Quarter note
            _outputs[getRotatedOutputIndex(5)] = _pulseCount % 32 == 0 ? TRIG_HIGH : TRIG_LOW; //Third note
            _outputs[getRotatedOutputIndex(6)] = _pulseCount % 48 == 0 ? TRIG_HIGH : TRIG_LOW; //Semitone
            _outputs[getRotatedOutputIndex(7)] = _pulseCount % 96 == 0 ? TRIG_HIGH : TRIG_LOW; //Whole note
        } else if(_mode == CLOCK_MODE_DIVIDE) {
            _outputs[getRotatedOutputIndex(0)] = _pulseCount % 1 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(1)] = _pulseCount % 2 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(2)] = _pulseCount % 3 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(3)] = _pulseCount % 4 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(4)] = _pulseCount % 5 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(5)] = _pulseCount % 6 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(6)] = _pulseCount % 7 == 0 ? TRIG_HIGH : TRIG_LOW;
            _outputs[getRotatedOutputIndex(7)] = _pulseCount % 8 == 0 ? TRIG_HIGH : TRIG_LOW;
        }

    } else if(_triggerTimer.isStopped()) {
        for(int i = 0; i < OSCILLATOR_COUNT; i++) {
            _outputs[i] = LOW;
        }
    }
}

void ClockSource::trigger() {
    _oscillators[0].reset();
}

void ClockSource::setFrequencyHz(float frequencyHz) {
    _frequency = frequencyHz*8;
    float frequency = calculateSwingFrequency(_frequency);
    _oscillators[0].setFrequencyHz(frequency);
}

void ClockSource::setWave(float wave) {
    _swing = wave/2 + 0.9;
    if(_swing < 1) {
        _swing = 1;
    }
}

float ClockSource::calculateSwingFrequency(float frequency) {

    int ppqn = 4;
    if(_mode == CLOCK_MODE_PPQN24) {
        ppqn = PPQN24;
    }

    float freqQuarterNote = frequency/ppqn;
    float timeQuarterNote = 1/freqQuarterNote;

    float timeQuarterNote1 = timeQuarterNote/_swing;
    float timeQuarterNote2 = (timeQuarterNote*2)-timeQuarterNote1;

    float freqQuarterNote1 = 1/timeQuarterNote1;
    float freqQuarterNote2 = 1/timeQuarterNote2;

    if((_pulseCount / ppqn) % 2 == 0) {
        return freqQuarterNote1*ppqn;
    } else {
        return freqQuarterNote2*ppqn;
    }
}

void ClockSource::rotateOutputs() {
    _outputRotation++;
    if(_outputRotation == OSCILLATOR_COUNT) {
        _outputRotation = 0;
    }
}

uint8_t ClockSource::getRotatedOutputIndex(uint8_t index) {
    uint8_t rotatedIndex = index + _outputRotation;
    if(rotatedIndex >= OSCILLATOR_COUNT) {
        rotatedIndex = rotatedIndex - OSCILLATOR_COUNT;
    }
    return rotatedIndex;
}
