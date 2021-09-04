#include "ClockController.h"

void ClockController::init() {
    clock.init(sampleRate);
    clockDividers[0].setDivisor(1);
    clockDividers[1].setDivisor(2);
    clockDividers[2].setDivisor(3);
    clockDividers[3].setDivisor(4);
    clockDividers[4].setDivisor(5);
    clockDividers[5].setDivisor(6);
    clockDividers[6].setDivisor(7);
    clockDividers[7].setDivisor(8);
}

void ClockController::update() {
    if(ratePotInput.update()) {
        float rateValue = ratePotInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            clock.setFrequency(rateValue);
        }
    }
}

void ClockController::process() {
    if(clock.process()) {
        tick();
    }

    for(int i = 0; i < 8; i++) {
        triggerOutputs[i].update();
    }
}

void ClockController::tick() {
    for(int i = 0; i < 8; i++) {
        if(clockDividers[i].tick()) {
            triggerOutputs[i].trigger();
        }
    }
}