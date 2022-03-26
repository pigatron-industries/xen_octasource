#include "AttractorController.h"

void AttractorController::init(float sampleRate) {
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
    Hardware::hw.display.text(attractors1[mode.value]->getName(), Display::TEXTLINE_2);
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
    ContinuousSystem* attractor = attractors1[mode.value];
    attractor->process();
    Hardware::hw.cvOutputPins[1]->analogWrite(attractor->getOutput(X)*amp);
    Hardware::hw.cvOutputPins[2]->analogWrite(attractor->getOutput(Y)*amp);
    Hardware::hw.cvOutputPins[3]->analogWrite(attractor->getOutput(Z)*amp);

    attractor = attractors2[mode.value];
    attractor->process();
    Hardware::hw.cvOutputPins[7]->analogWrite(attractor->getOutput(X)*amp);
    Hardware::hw.cvOutputPins[6]->analogWrite(attractor->getOutput(Y)*amp);
    Hardware::hw.cvOutputPins[5]->analogWrite(attractor->getOutput(Z)*amp);

    Hardware::hw.gateOutPin.digitalWrite(attractor->getOutput(Z) > 0);
}