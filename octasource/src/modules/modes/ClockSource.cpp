#include "ClockSource.h"

#define PPQN 24

void ClockSource::init() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setWave(4);
    }
}

void ClockSource::execute(unsigned long timeDiff) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _outputs[i] = _oscillators[i].execute(timeDiff);
    }

    if(_oscillators[0].getTriggerOut()) {
        _pulseCount++;
        if(_pulseCount == PPQN) {
            _pulseCount = 0;
            // Set swing frequency
        }
    }
}

void ClockSource::setFrequencyHz(float frequencyHz) {
    float freq = frequencyHz*8;
    _oscillators[0].setFrequencyHz(freq);
    _oscillators[1].setFrequencyHz(freq/6);
    _oscillators[2].setFrequencyHz(freq/8);  //Triplets
    _oscillators[3].setFrequencyHz(freq/12);
    _oscillators[4].setFrequencyHz(freq/24); //Quarter notes
    _oscillators[5].setFrequencyHz(freq/48);
    _oscillators[6].setFrequencyHz(freq/72);
    _oscillators[7].setFrequencyHz(freq/96);
}

void ClockSource::setWave(float wave) {
}
