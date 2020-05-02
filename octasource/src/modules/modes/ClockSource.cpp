#include "ClockSource.h"

#define PPQN 24

void ClockSource::init() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setWave(4);
    }
    _pulseCount = 0;
}

void ClockSource::execute(unsigned long timeDiff) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        float output = _oscillators[i].execute(timeDiff);
        if(_frequency > 0) {
            if(output > 0.5) {
                _outputs[i] = 5;
            } else {
                _outputs[i] = 0;
            }
        } else {
          if(output < -0.5) {
              _outputs[i] = 5;
          } else {
              _outputs[i] = 0;
          }
        }
    }

    if(_oscillators[0].getTriggerOut()) {
        _pulseCount++;
        if(_pulseCount == PPQN*2) {
            _pulseCount = 0;
        }
    }
}

void ClockSource::setFrequencyHz(float frequencyHz) {
    _frequency = frequencyHz*8;
    float frequency = calculateSwingFrequency(_frequency);
    _oscillators[0].setFrequencyHz(frequency);
    _oscillators[1].setFrequencyHz(frequency/6);
    _oscillators[2].setFrequencyHz(frequency/8);  //Triplets
    _oscillators[3].setFrequencyHz(frequency/12);
    _oscillators[4].setFrequencyHz(frequency/24); //Quarter notes
    _oscillators[5].setFrequencyHz(frequency/48);
    _oscillators[6].setFrequencyHz(frequency/72);
    _oscillators[7].setFrequencyHz(frequency/96);
}

float ClockSource::calculateSwingFrequency(float frequency) {
    float freqQuarterNote = frequency/PPQN;
    float timeQuarterNote = 1/freqQuarterNote;

    float timeQuarterNote1 = timeQuarterNote/_swing;
    float timeQuarterNote2 = (timeQuarterNote*2)-timeQuarterNote1;

    float freqQuarterNote1 = 1/timeQuarterNote1;
    float freqQuarterNote2 = 1/timeQuarterNote2;

    if(_pulseCount >= PPQN) {
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
