#include "ClockController.h"
#include "common/Controls.h"

#define MAX_CLOCK_VALUE 30
#define DEFAULT_CLOCK_VALUE 15  // 15 = "/1" or unison

void ClockController::load() {
    Config::config.load(config);
    for(int i = 0; i < 8; i++) {
        parameters[i].last = MAX_CLOCK_VALUE;
        if(config.data.check != 0 || config.data.clock[i] > MAX_CLOCK_VALUE) { 
            config.data.clock[i] = DEFAULT_CLOCK_VALUE; 
        }
        parameters[i].value = config.data.clock[i];
    }
}

void ClockController::save() {
    config.data.check = 0;
    Config::config.save(config);
}

void ClockController::init(float sampleRate) {
    ClockedController::init(sampleRate);
    display.init();
    display.focusClock(0);

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

int ClockController::cycleMode(int amount) {
    parameters.cycle(amount);
    display.focusClock(parameters.getSelectedIndex());
    return parameters.getSelectedIndex(); 
}

void ClockController::cycleValue(int amount) {
    uint8_t output = parameters.getSelectedIndex();
    uint8_t value = parameters.getSelected().cycle(amount);
    config.data.clock[output] = value;
    if(isMultiplier(output)) {
        display.setClock(output, false, getMultiplier(output));
    } else {
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
    return config.data.clock[channel] < 15;
}

bool ClockController::isDivider(int channel) {
    return config.data.clock[channel] > 15;
}

uint8_t ClockController::getMultiplier(int channel) {
    return 16 - config.data.clock[channel];
}

uint8_t ClockController::getDivider(int channel) {
    return config.data.clock[channel] - 14;
}
