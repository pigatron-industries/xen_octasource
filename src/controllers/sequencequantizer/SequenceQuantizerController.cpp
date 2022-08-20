#include "SequenceQuantizerController.h"

void SequenceQuantizerController::init(float sampleRate) {
    ClockedController::init(sampleRate);
    display.init();
    init();
}

void SequenceQuantizerController::init() {
    Serial.println("Sequence Quantizer");
    display.render();
}

void SequenceQuantizerController::update() {
    ClockedController::update();
    // valueInput.update();
    dejaVuInput.update();
    triggerOutput.update();

    if(lengthInput.update()) {
        display.setLength(lengthInput.getValue());
    }

    Hardware::hw.updateOutputLeds();
}

void SequenceQuantizerController::onClock() {
    triggerOutput.trigger();

    position++;
    if(position >= lengthInput.getIntValue()) {
        position = 0;
    }

    //sequence.values[position] = smooth(sequence.values[position], Hardware::hw.modeCvPin.analogRead(), dejaVuInput.getValue());

    if(random(0, 100) < dejaVuInput.getValue()) {
        sequence.values[position] = Hardware::hw.modeCvPin.analogRead();
    }
    
    Hardware::hw.cvOutputPins[0]->analogWrite(sequence.values[position]);
}
