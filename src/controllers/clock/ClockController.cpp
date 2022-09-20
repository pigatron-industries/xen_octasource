#include "ClockController.h"
#include "common/Controls.h"

void ClockController::init(float sampleRate) {
    ClockedController::init(sampleRate);
    display.init();
    display.focusClock(0);

    for(int i = 0; i < 15; i++) {
        clockMultipliers[i].init(sampleRate);
        clockDividers[i].setDivisor(i+2);
    }

    for(int i = 0; i < 8; i++) {
        parameters[i].last = 30;
        parameters[i].value = 15; //  15 = /1
        channelSetting[i] = 15;
        display.setClock(i, true, 1);
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

int ClockController::cycleMode(int amount) {
    parameters.cycle(amount);
    display.focusClock(parameters.getSelectedIndex());
    return parameters.getSelectedIndex(); 
}

void ClockController::cycleValue(int amount) {
    uint8_t output = parameters.getSelectedIndex();
    uint8_t value = parameters.getSelected().cycle(amount);
    channelSetting[output] = value;
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

    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
}

void ClockController::updateMultiplierRates() {
    for(int i = 0; i < 15; i++) {
        clockMultipliers[i].setFrequency(clock.getFrequency() * (i+2));
    }
}

void ClockController::process() {
    ClockedController::process();
    triggerOutput.update();

    for(int i = 0; i < 8; i++) {
        if(isMultiplier(i) && clockMultipliers[getMultiplier(i)-2].process()) {
            triggerOutputs[i].trigger();
        }
        triggerOutputs[i].update();
    }
}

void ClockController::onClock() {
    syncClocks();
    triggerOutput.trigger();

    for(int i = 0; i < 15; i++) {
        clockDividers[i].tick();
    }

    for(int i = 0; i < 8; i++) {
        if(isDivider(i) && clockDividers[getDivider(i)-2].getTrigger()) {
            triggerOutputs[i].trigger();
        }
        if(!isDivider(i)) {
            triggerOutputs[i].trigger();
        }
    }

    for(int i = 0; i < 15; i++) {
        clockDividers[i].getAndResetTrigger();
    }
}

void ClockController::syncClocks() {
    for(int i = 0; i < 16; i++) {
        clockMultipliers[i].reset();
    }
}

bool ClockController::isMultiplier(int channel) {
    return channelSetting[channel] < 15;
}

bool ClockController::isDivider(int channel) {
    return channelSetting[channel] > 15;
}

uint8_t ClockController::getMultiplier(int channel) {
    return 16 - channelSetting[channel];
}

uint8_t ClockController::getDivider(int channel) {
    return channelSetting[channel] - 14;
}
