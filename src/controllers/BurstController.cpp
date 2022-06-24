#include "BurstController.h"

void BurstController::init(float sampleRate) {
    for(int i = 0; i < outputs; i++) {
        bursts[i].clock.init(sampleRate);
    }
    init();
}

void BurstController::init() {
    Serial.println("Burst");
    Hardware::hw.display.text("BURST");

    outputs = mode.value + 1;
    char line2[11];
    snprintf_P(line2, sizeof(line2), PSTR("OUTPUTS: %d"), outputs);
    Hardware::hw.display.text(line2, Display::TEXTLINE_2);
    outputs = mode.value + 1;
}

void BurstController::update() {
    if(triggerInput.update() && triggerInput.isTriggeredOn()) {
        burstRateInput.update();
        burstLengthInput.update();
        bursts[nextOutput].start(burstRateInput.getValue(), burstLengthInput.getValue());
        triggerOutputs[nextOutput].trigger();
        nextOutput++;
        if(nextOutput >= outputs) {
            nextOutput = 0;
        }
    }

    Hardware::hw.updateOutputLeds(Colour(0, 0, 0), Colour(0, 1, 0));
}

void BurstController::process() {
    for(int i = 0; i < outputs; i++) {
        triggerOutputs[i].update();
        if(bursts[i].process()) {
            triggerOutputs[i].trigger();
        }
    }
}
