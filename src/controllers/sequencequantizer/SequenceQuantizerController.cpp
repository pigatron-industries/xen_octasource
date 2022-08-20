#include "SequenceQuantizerController.h"

void SequenceQuantizerController::init(float sampleRate) {
    ClockedController::init(sampleRate);
    init();
}

void SequenceQuantizerController::init() {
    Serial.println("Sequence Quantizer");
    Hardware::hw.display.textLine("SEQUANTIZER");
}

void SequenceQuantizerController::update() {
    ClockedController::update();
    // valueInput.update();
    dejaVuInput.update();
    lengthInput.update();
    triggerOutput.update();

    Hardware::hw.updateOutputLeds();
}

void SequenceQuantizerController::onClock() {
    triggerOutput.trigger();

    position++;
    if(position >= lengthInput.getIntValue()) {
        position = 0;
    }

    sequence.values[position] = smooth(sequence.values[position], Hardware::hw.modeCvPin.analogRead(), dejaVuInput.getValue());
    
    Hardware::hw.cvOutputPins[0]->analogWrite(sequence.values[position]);
}
