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
    triggerOutput.update();
    Hardware::hw.updateOutputLeds();
}

void QuantizerController::process() {
    if(syncInput.update()) {
        if(syncInput.isTriggeredOn()) {
            float value = Hardware::hw.modeCvPin.analogRead();
            Note note = pitchQuantizer.quantizeToScale(value, scale);
            Hardware::hw.cvOutputPins[0]->analogWrite(note.voltage);
        }
    }

}
