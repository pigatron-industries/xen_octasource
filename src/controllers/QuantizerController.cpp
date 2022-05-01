#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
    tuning.enable({3, 5, 7, 10});
}

void QuantizerController::init() {
    Serial.println("Quantizer");
    Hardware::hw.display.text("QUANTIZER");
}

void QuantizerController::update() {
    triggerOutput.update();
    Hardware::hw.updateOutputLeds();
}

void QuantizerController::process() {
    if(syncInput.update()) {
        if(syncInput.isTriggeredOn()) {
            float value = Hardware::hw.modeCvPin.analogRead();
            if(pitchQuantizer.quantize(value)) {
                triggerOutput.trigger();
            }
        }
    }

    Hardware::hw.cvOutputPins[0]->analogWrite(pitchQuantizer.getNote().value);
}
