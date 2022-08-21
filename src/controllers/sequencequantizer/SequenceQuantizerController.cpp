#include "SequenceQuantizerController.h"

void SequenceQuantizerController::init(float sampleRate) {
    ClockedController::init(sampleRate);
    Controller::init(sampleRate);
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

void SequenceQuantizerController::process() {
    ClockedController::process();
    for(int i = 0; i < 4; i++) {
        triggerOutputs[i].update();
    }
}

void SequenceQuantizerController::onClock() {
    triggerOutput.trigger();

    position++;
    if(position >= lengthInput.getIntValue()) {
        position = 0;
    }

    for(int i = 0; i < 4; i++) {
        if(random(0, 100) < dejaVuInput.getValue()) {
            sequence[i].values[position] = Hardware::hw.modeCvPin.analogRead();
        }
        if(random(0, 100) < dejaVuInput.getValue()) {
            sequence[i].triggers[position] = random(0, 2);
        }
        
        Hardware::hw.cvOutputPins[i]->analogWrite(sequence[i].values[position]);
        if(sequence[i].triggers[position]) {
            triggerOutputs[i].trigger();
        }
    }
}
