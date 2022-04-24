#include "QuantizerController.h"

void QuantizerController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
    scale.enable(3);
    scale.enable(5);
    scale.enable(7);
    scale.enable(10);
    
}

void QuantizerController::init() {
    Serial.println("Quantizer");
    Hardware::hw.display.text("QUANTIZER");
}

void QuantizerController::update() {
    // if(syncInput.update()) {
    //     if(syncInput.isTriggeredOn()) {
    //         float value = Hardware::hw.modeCvPin.analogRead();
    //         if(pitchQuantizer.quantize(value)) {
    //             triggerOutput.trigger();
    //         }
    //     }
    // }

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
