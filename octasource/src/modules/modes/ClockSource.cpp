#include "ClockSource.h"
#include <Arduino.h>

#define PPQN 24
#define TRIGGER_TIME 1000

void ClockSource::init() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setWave(4);
    }
    _pulseCount = 0;
}

void ClockSource::execute(unsigned long timeDiff) {
    _oscillators[0].execute(timeDiff);

    if(_oscillators[0].getTriggerOut()) {
        _triggerTimer.start(TRIGGER_TIME);
        _pulseCount++;
        if(_pulseCount == PPQN*12) {
           _pulseCount = 0;
        }

        _outputs[0] = 5;
        _outputs[1] = _pulseCount % 6 == 0 ? 5 : 0;
        _outputs[2] = _pulseCount % 8 == 0 ? 5 : 0;
        _outputs[3] = _pulseCount % 12 == 0 ? 5 : 0;
        _outputs[4] = _pulseCount % 24 == 0 ? 5 : 0;
        _outputs[5] = _pulseCount % 48 == 0 ? 5 : 0;
        _outputs[6] = _pulseCount % 72 == 0 ? 5 : 0;
        _outputs[7] = _pulseCount % 96 == 0 ? 5 : 0;

    } else if(_triggerTimer.isStopped()) {
        for(int i = 0; i < OSCILLATOR_COUNT; i++) {
            _outputs[i] = 0;
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

float ClockSource::calculateSwingFrequency(float frequency) {
    float freqQuarterNote = frequency/PPQN;
    float timeQuarterNote = 1/freqQuarterNote;

    float timeQuarterNote1 = timeQuarterNote/_swing;
    float timeQuarterNote2 = (timeQuarterNote*2)-timeQuarterNote1;

    float freqQuarterNote1 = 1/timeQuarterNote1;
    float freqQuarterNote2 = 1/timeQuarterNote2;

    if((_pulseCount / PPQN) % 2 == 0) {
        return freqQuarterNote1*PPQN;
    } else {
        return freqQuarterNote2*PPQN;
    }
}

void ClockSource::setWave(float wave) {
    _swing = wave/2 + 0.9;
    if(_swing < 1) {
        _swing = 1;
    }
}
