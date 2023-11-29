#include "ClockController.h"
#include "common/Controls.h"

#define MAX_CLOCK_VALUE 30
#define DEFAULT_CLOCK_VALUE 15  // 15 = "/1" or unison
#define LOWEST_MULTIPLIER_DIVIDER 2


void ClockController::init(float sampleRate) {
    for(int i = 0; i < 8; i++) {
        this->configParam(i, DEFAULT_CLOCK_VALUE, MAX_CLOCK_VALUE);
    }

    ClockedController::init(sampleRate);
    display.init();
    display.focusClock(0);

    clock.setLength(2); // TODO: make configurable

    for(int i = 0; i < 15; i++) {
        clockMultipliers[i].init(sampleRate);
        clockDividers[i].setDivisor(i+2);
    }

    for(int i = 0; i < 8; i++) {
        updateClock(i);
    }

    init();
}

void ClockController::init() {
    Serial.println("Clock");
    display.render();
    for(int i = 0; i < 15; i++) {
        clockDividers[i].reset();
    }
}

int ClockController::cycleParameter(int amount) {
    parameters.cycle(amount);
    display.focusClock(parameters.getSelectedIndex());
    return parameters.getSelectedIndex(); 
}

void ClockController::cycleValue(int amount) {
    uint8_t output = parameters.getSelectedIndex();
    uint8_t value = parameters.getSelected().cycle(amount);
    config.data.clock[output] = value;
    if(isMultiplier(output)) {
        Serial.println("muliplier");
        Serial.println(value);
        Serial.println(getMultiplier(output));
        display.setClock(output, false, getMultiplier(output));
    } else {
        Serial.println("divider");
        Serial.println(value);
        Serial.println(getDivider(output));
        display.setClock(output, true, getDivider(output));
    }
    save();
}

void ClockController::updateClock(uint8_t output) {
    if(isMultiplier(output)) {
        display.setClock(output, false, getMultiplier(output));
    } else {
        display.setClock(output, true, getDivider(output));
    }
}

void ClockController::update() {
    if(ClockedController::updateRate()) {
        updateMultiplierRates();
    }

    for(int i = 0; i < 8; i++) {
        triggerOutputs[i].update();
    }

    if(distortionXCvInput.update()) {
        clock.getFunction().setMidPoint(distortionXCvInput.getValue(), 0.5);
        clock.calculatePhaseIncrements();
    }

    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
}

void ClockController::updateMultiplierRates() {
    for(int i = 0; i < 15; i++) {
        clockMultipliers[i].setFrequency((clock.getFrequency()/MULIPLIER_BASE) * (i+2));
    }
}

void ClockController::process() {
    ClockedController::process();
    triggerOutput.update();

    for(int i = 0; i < 8; i++) {
        uint8_t multiplierIndex = getMultiplier(i) - LOWEST_MULTIPLIER_DIVIDER;
        if(isMultiplier(i) && clockMultipliers[multiplierIndex].process()) {
            triggerOutputs[i].trigger();
        }
        triggerOutputs[i].update();
    }
}

void ClockController::onClock() {
    syncClocks();
    triggerOutput.trigger();

    for(int i = 0; i < NUM_DIVIDERS; i++) {
        clockDividers[i].tick();
    }

    for(int i = 0; i < 8; i++) {
        uint8_t dividerIndex = getDivider(i) - LOWEST_MULTIPLIER_DIVIDER;
        if(isDivider(i) && clockDividers[dividerIndex].getTrigger()) {
            triggerOutputs[i].trigger();
        }
        if(!isDivider(i)) {
            triggerOutputs[i].trigger();
        }
    }

    for(int i = 0; i < NUM_DIVIDERS; i++) {
        clockDividers[i].getAndResetTrigger();
    }
}

void ClockController::syncClocks() {
    for(int i = 0; i < NUM_MULTIPLIERS; i++) {
        clockMultipliers[i].reset();
    }
}

bool ClockController::isMultiplier(int channel) {
    return parameters[channel].value < NUM_MULTIPLIERS;
}

bool ClockController::isDivider(int channel) {
    return parameters[channel].value > NUM_MULTIPLIERS;
}

uint8_t ClockController::getMultiplier(int channel) {
    return NUM_MULTIPLIERS + 1 - parameters[channel].value;
}

uint8_t ClockController::getDivider(int channel) {
    return parameters[channel].value - NUM_MULTIPLIERS + 1;
}

//  0   1   2   3   4   5   6    7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29 30
// *16 *15 *14 *13 *12 *11 *10  *9  *8  *7  *6  *5  *4  *3  *2   1  /2  /3  /4  /5  /6  /7  /8  /9  /10 /11 /12 /13 /14 /15 /16