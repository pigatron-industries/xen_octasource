#include "BurstSource.h"


void BurstSource::init() {
    _oscillators[0].setPosition(0);
    _oscillators[1].setPosition(-(MAX_POSITION/8)*1);
    _oscillators[2].setPosition(-(MAX_POSITION/8)*2);
    _oscillators[3].setPosition(-(MAX_POSITION/8)*3);
    _oscillators[4].setPosition(-(MAX_POSITION/8)*4);
    _oscillators[5].setPosition(-(MAX_POSITION/8)*5);
    _oscillators[6].setPosition(-(MAX_POSITION/8)*6);
    _oscillators[7].setPosition(-(MAX_POSITION/8)*7);

    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _oscillators[i].setCycle(false);
    }
}

void BurstSource::trigger() {
    init();
}
