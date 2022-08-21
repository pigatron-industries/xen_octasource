#include "ClockController.h"
#include "common/Controls.h"

void ClockController::init(float sampleRate) {
    ClockedController::init(sampleRate);
    display.init();
    display.focusClock(0);

    for(int i = 0; i < 8; i++) {
        clockMultipliers[i].init(sampleRate);
        parameters[i].last = 30;
        parameters[i].value = 15; //15 = /1
        display.setClock(i, true, 1);
    }

    init();
}

void ClockController::init() {
    Serial.println("Clock");
    display.render();
    for(int i = 0; i < 8; i++) {
        clockDividers[i].reset();
    }
}

int ClockController::cycleMode(int amount) {
    parameters.cycle(amount);
    display.focusClock(parameters.getSelectedIndex());
    return parameters.getSelectedIndex(); 
}

void ClockController::cycleValue(int amount) {
    uint8_t output = parameters.getSelectedIndex();
    parameters.getSelected().cycle(amount);

    if(parameters.getSelected().value < 15) {
        uint8_t multiplier = 16-parameters.getSelected().value;
        multipliers[output] = multiplier;
        updateMultiplierRates();
        display.setClock(output, false, multiplier);
    } else {
        uint8_t divisor = parameters.getSelected().value-14;
        multipliers[output] = 0;
        clockDividers[output].setDivisor(divisor);
        display.setClock(output, true, divisor);
    }
}

void ClockController::update() {
    if(ClockedController::updateRate()) {
        updateMultiplierRates();
    }

    for(int i = 0; i < 8; i++) {
        triggerOutputs[i].update();
    }

    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
}

void ClockController::updateMultiplierRates() {
    for(int i = 0; i < 8; i++) {
        if(multipliers[i] > 0) {
            clockMultipliers[i].setFrequency(clock.getFrequency() * multipliers[i]);
        }
    }
}

void ClockController::process() {
    ClockedController::process();
    triggerOutput.update();

    for(int i = 0; i < 8; i++) {
        if(multipliers[i] > 0 && clockMultipliers[i].process()) {
            triggerOutputs[i].trigger();
        }
        triggerOutputs[i].update();
    }
}

void ClockController::onClock() {
    syncClocks();
    triggerOutput.trigger();
    for(int i = 0; i < 8; i++) {
        if(multipliers[i] == 0 && clockDividers[i].tick()) {
            triggerOutputs[i].trigger();
        }
    }
}

void ClockController::syncClocks() {
    for(int i = 0; i < 8; i++) {
        clockMultipliers[i].reset();
        if(multipliers[i] > 0) {
            triggerOutputs[i].trigger();
        }
    }
}