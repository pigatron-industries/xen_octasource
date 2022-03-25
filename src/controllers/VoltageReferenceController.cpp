#include "VoltageReferenceController.h"

void VoltageReferenceController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void VoltageReferenceController::init() {
    Serial.println("Voltage Reference");
    Hardware::hw.display.title("REFERENCE");
}

void VoltageReferenceController::update() {
    Hardware::hw.updateOutputLeds();
}

void VoltageReferenceController::process() {
    Hardware::hw.cvOutputPins[7]->analogWrite(-5);
    Hardware::hw.cvOutputPins[6]->analogWrite(-2);
    Hardware::hw.cvOutputPins[5]->analogWrite(-1);

    Hardware::hw.cvOutputPins[0]->analogWrite(0);
    Hardware::hw.cvOutputPins[4]->analogWrite(0);

    Hardware::hw.cvOutputPins[1]->analogWrite(1);
    Hardware::hw.cvOutputPins[2]->analogWrite(2);
    Hardware::hw.cvOutputPins[3]->analogWrite(5);
}
