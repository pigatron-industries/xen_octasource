#include "ClockMultiplierController.h"

void ClockMultiplierController::init(float sampleRate) {
    mainClock.init(sampleRate);
    for(int i = 0; i < 9; i++) {
        clocks[i].init(sampleRate);
        clocks[i].setFrequency(1);
    }
    init();
}

void ClockMultiplierController::init() {
    Hardware::hw.display.text("CLOCK MULT");
}

void ClockMultiplierController::update() {
    updateRate();
    updateRange();
    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
}

void ClockMultiplierController::updateRate() {
    if(mainClock.getState() != Clock::State::CLK_EXTERNAL) {
        if(rateCvInput.update()) {
            setRate(rateCvInput.getValue());
        }
    } else if(mainClock.getState() == Clock::State::CLK_EXTERNAL) {
        float externalFrequency = mainClock.getFrequency();
        if(externalFrequency != syncFrequency || syncMultCvInput.update()) {
            syncFrequency = externalFrequency;
            int multInputValue = syncMultCvInput.getIntValue();
            float mult = multInputValue >= 0 ? multInputValue+1 : 1/float(-multInputValue);
            setRate(syncFrequency * mult);
        }
    }
}

void ClockMultiplierController::setRate(float frequency) {
    for(int i = 0; i < 9; i++) {
        clocks[i].setFrequency(frequency*(i+1));
    }
}

void ClockMultiplierController::updateRange() {
    if(rangeInput.update()) {
        if(rangeInput.getValue()) {
            for(int i = 0; i < 8; i++) {
                triggerOutputs[i].setZeroVoltage(-5);
            }
        } else {
            for(int i = 0; i < 8; i++) {
                triggerOutputs[i].setZeroVoltage(0);
            }
        }
    }
}

void ClockMultiplierController::updateSync() {
    if(syncInput.update() && syncInput.isTriggeredOn()) {
        mainClock.externalTick(); 
    }
}

void ClockMultiplierController::syncClocks() {
    for(int i = 0; i < 9; i++) {
        clocks[i].reset();
    }
    for(int i = 0; i < 8; i++) {
        triggerOutputs[i].trigger();
    }
    triggerOutput.trigger();
}

void ClockMultiplierController::process() {
    if(clocks[0].process()) {
        syncClocks();
    }
    triggerOutput.update();

    for(int i = 0; i < 8; i++) {
        if(clocks[i+1].process()) {
            triggerOutputs[i].trigger();
        }
        triggerOutputs[i].update();
    }

    mainClock.process();
    if(clockDivider.tick()) {
        updateSync();
    }
}