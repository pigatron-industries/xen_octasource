#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void QuantizerController::init() {
    Serial.println("Quantizer");
    Hardware::hw.display.text("QUANTIZER");
}

void QuantizerController::update() {
    if(syncInput.update()) {
        if(syncInput.isTriggeredOn()) {
            float value = Hardware::hw.modeCvPin.analogRead();
            quantizedValue = pitchQuantizer.quantize(value);
        }
    }

    Hardware::hw.updateOutputLeds();
}

void QuantizerController::process() {
    Hardware::hw.cvOutputPins[0]->analogWrite(quantizedValue);
}
