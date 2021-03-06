#include "PhasedSource.h"


void PhasedSource::init() {
    setPosition(0);
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setCycle(true);
    }
}

void PhasedSource::trigger() {
    init();
}

void PhasedSource::setPosition(float position) {
  _oscillators[0].setPosition(position);
  _oscillators[1].setPosition(position + (MAX_POSITION/8)*1);
  _oscillators[2].setPosition(position + (MAX_POSITION/8)*2);
  _oscillators[3].setPosition(position + (MAX_POSITION/8)*3);
  _oscillators[4].setPosition(position + (MAX_POSITION/8)*4);
  _oscillators[5].setPosition(position + (MAX_POSITION/8)*5);
  _oscillators[6].setPosition(position + (MAX_POSITION/8)*6);
  _oscillators[7].setPosition(position + (MAX_POSITION/8)*7);
}
