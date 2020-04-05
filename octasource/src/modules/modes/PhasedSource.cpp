#include "PhasedSource.h"


void PhasedSource::init() {
  _oscillators[0].setPosition(0);
  _oscillators[1].setPosition((MAX_POSITION/8)*1);
  _oscillators[2].setPosition((MAX_POSITION/8)*2);
  _oscillators[3].setPosition((MAX_POSITION/8)*3);
  _oscillators[4].setPosition((MAX_POSITION/8)*4);
  _oscillators[5].setPosition((MAX_POSITION/8)*5);
  _oscillators[6].setPosition((MAX_POSITION/8)*6);
  _oscillators[7].setPosition((MAX_POSITION/8)*7);
}

void PhasedSource::trigger() {
    init();
}
