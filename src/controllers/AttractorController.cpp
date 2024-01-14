#include "AttractorController.h"

void AttractorController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::ATTRACTOR1, 0, attractors1.getSize()-1);
    configParam(Parameter::ATTRACTOR2, 0, attractors2.getSize()-1);
    for(size_t i = 0; i < attractors1.getSize(); i++) {
        attractors1[i]->init(sampleRate);
        attractors2[i]->init(sampleRate);
        attractors2[i]->changePosition(Vector<3>(0.01, 0, 0));
    }
    init();
}

void AttractorController::init() {
    Serial.println("Attractor");
    Hardware::hw.display.text("ATTRACTOR");
    uint8_t selectedAttractor1 = parameters[Parameter::ATTRACTOR1].value;
    Hardware::hw.display.textLine(attractors1[selectedAttractor1]->getName(), OLEDDisplay::TEXTLINE_2);
    uint8_t selectedAttractor2 = parameters[Parameter::ATTRACTOR2].value;
    Hardware::hw.display.textLine(attractors2[selectedAttractor2]->getName(), OLEDDisplay::TEXTLINE_3);
}

void AttractorController::cycleValue(int amount) {
    Serial.println(parameters.getSelectedIndex());
    uint8_t value = parameters.getSelected().cycle(amount);

    uint8_t selectedAttractor1 = parameters[Parameter::ATTRACTOR1].value;
    Hardware::hw.display.textLine(attractors1[selectedAttractor1]->getName(), OLEDDisplay::TEXTLINE_2);
    uint8_t selectedAttractor2 = parameters[Parameter::ATTRACTOR2].value;
    Hardware::hw.display.textLine(attractors2[selectedAttractor2]->getName(), OLEDDisplay::TEXTLINE_3);

    save();
}

void AttractorController::update() {
    updateRate();
    updateAmp();
    Hardware::hw.updateOutputLeds();
    
    // RangeScale scale = RangeScale(-5, 5, 0, 32);
    // float x = Hardware::hw.cvOutputPins[1]->getAnalogValue();
    // float y = Hardware::hw.cvOutputPins[2]->getAnalogValue();
    // float z = Hardware::hw.cvOutputPins[3]->getAnalogValue();
    // Hardware::hw.display.drawPixelTrail(pixelTrail1, Pixel(scale.convert(x), scale.convert(y)));
    // Hardware::hw.display.drawPixelTrail(pixelTrail2, Pixel(32+scale.convert(x), scale.convert(z)));
}

void AttractorController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(size_t i = 0; i < attractors1.getSize(); i++) {
            attractors1[i]->setSpeed(rateValue);
            attractors2[i]->setSpeed(rateValue);
        }
    }
}

void AttractorController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void AttractorController::process() {
    uint8_t selectedAttractor1 = parameters[Parameter::ATTRACTOR1].value;
    ContinuousSystem* attractor = attractors1[selectedAttractor1];
    attractor->process();
    Hardware::hw.cvOutputPins[1]->analogWrite(attractor->getOutput(X)*amp);
    Hardware::hw.cvOutputPins[2]->analogWrite(attractor->getOutput(Y)*amp);
    Hardware::hw.cvOutputPins[3]->analogWrite(attractor->getOutput(Z)*amp);

    uint8_t selectedAttractor2 = parameters[Parameter::ATTRACTOR2].value;
    attractor = attractors2[selectedAttractor2];
    attractor->process();
    Hardware::hw.cvOutputPins[7]->analogWrite(attractor->getOutput(X)*amp);
    Hardware::hw.cvOutputPins[6]->analogWrite(attractor->getOutput(Y)*amp);
    Hardware::hw.cvOutputPins[5]->analogWrite(attractor->getOutput(Z)*amp);

    Hardware::hw.gateOutPin.digitalWrite(attractor->getOutput(Z) > 0);
}