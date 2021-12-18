#include "ClockController.h"

void ClockController::init(float sampleRate) {
    clock.init(sampleRate);
    init();
}

void ClockController::init() {
    for(int i = 0; i < 8; i++) {
        clockDividers[i].reset();
    }
    switch(mode.value) {
        case Mode::INTEGER:
            clockDividers[0].setDivisor(1);
            clockDividers[1].setDivisor(2);
            clockDividers[2].setDivisor(3);
            clockDividers[3].setDivisor(4);
            clockDividers[4].setDivisor(5);
            clockDividers[5].setDivisor(6);
            clockDividers[6].setDivisor(7);
            clockDividers[7].setDivisor(8);
            break;
        case Mode::POWER2:
            clockDividers[0].setDivisor(1);
            clockDividers[1].setDivisor(2);
            clockDividers[2].setDivisor(4);
            clockDividers[3].setDivisor(8);
            clockDividers[4].setDivisor(16);
            clockDividers[5].setDivisor(32);
            clockDividers[6].setDivisor(64);
            clockDividers[7].setDivisor(128);
            break;
        case Mode::PPQN24:
            clockDividers[0].setDivisor(1); // Clock
            clockDividers[1].setDivisor(6);
            clockDividers[2].setDivisor(8); //24/3
            clockDividers[3].setDivisor(12);
            clockDividers[4].setDivisor(24);
            clockDividers[5].setDivisor(32);//96/3
            clockDividers[6].setDivisor(48);
            clockDividers[7].setDivisor(96);
            break;
    }
}

void ClockController::update() {
    if(bipolarRateCvInput.update()) {
        float rateValue = bipolarRateCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            clock.setFrequency(rateValue);
        }
    }

    if(sloppinessCvInput.update()) {
        sloppiness = sloppinessCvInput.getValue();
    }

    if(triggerInput.update() && triggerInput.isTriggeredOn()) {
        tick();
        clock.reset();
    }
}

void ClockController::process() {
    if(clock.process()) {
        tick();
    }

    for(int i = 0; i < 8; i++) {
        triggerOutputs[i].update();
        if(timer[i].hasJustStopped()) {
            triggerOutputs[i].trigger();
        }
    }
}

void ClockController::tick() {
    for(int i = 0; i < 8; i++) {
        if(clockDividers[i].tick()) {
            timer[i].start(random(sloppiness));
            //triggerOutputs[i].trigger();
        }
    }
}