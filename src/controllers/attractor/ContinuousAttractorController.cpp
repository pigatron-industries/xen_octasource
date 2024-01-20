#include "ContinuousAttractorController.h"

void ContinuousAttractorController::init(float sampleRate) {
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

void ContinuousAttractorController::init() {
    Serial.println("Continuous Attractor");
    Hardware::hw.display.text("C ATTRACTOR");
    attractors1.select(parameters[Parameter::ATTRACTOR1].value);
    Hardware::hw.display.textLine(attractors1.getSelected()->getName(), OLEDDisplay::TEXTLINE_2);
    attractors2.select(parameters[Parameter::ATTRACTOR2].value);
    Hardware::hw.display.textLine(attractors2.getSelected()->getName(), OLEDDisplay::TEXTLINE_3);
}

void ContinuousAttractorController::cycleValue(int amount) {
    Serial.println(parameters.getSelectedIndex());
    parameters.getSelected().cycle(amount);

    attractors1.select(parameters[Parameter::ATTRACTOR1].value);
    Hardware::hw.display.textLine(attractors1.getSelected()->getName(), OLEDDisplay::TEXTLINE_2);
    attractors2.select(parameters[Parameter::ATTRACTOR2].value);
    Hardware::hw.display.textLine(attractors2.getSelected()->getName(), OLEDDisplay::TEXTLINE_3);

    save();
}

void ContinuousAttractorController::update() {
    updateRate();
    updateAmp();
    updateParams();
    updateRotation();
    Hardware::hw.updateOutputLeds();
    
    // RangeScale scale = RangeScale(-5, 5, 0, 32);
    // float x = Hardware::hw.cvOutputPins[1]->getAnalogValue();
    // float y = Hardware::hw.cvOutputPins[2]->getAnalogValue();
    // float z = Hardware::hw.cvOutputPins[3]->getAnalogValue();
    // Hardware::hw.display.drawPixelTrail(pixelTrail1, Pixel(scale.convert(x), scale.convert(y)));
    // Hardware::hw.display.drawPixelTrail(pixelTrail2, Pixel(32+scale.convert(x), scale.convert(z)));
}

void ContinuousAttractorController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        for(size_t i = 0; i < attractors1.getSize(); i++) {
            attractors1[i]->setSpeed(rateValue);
            attractors2[i]->setSpeed(rateValue);
        }
    }
}

void ContinuousAttractorController::updateAmp() {
    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }
}

void ContinuousAttractorController::updateParams() {
    if(paramsCvInput.update()) {
        attractors1.getSelected()->setInterpolation(paramsCvInput.getValue());
    }
}

void ContinuousAttractorController::updateRotation() {
    if (rotateCvInput.update()) {
        rotation = rotateCvInput.getValue();
    }
}

void ContinuousAttractorController::process() {
    ContinuousSystemN<3>* attractor = attractors1.getSelected();
    attractor->process();
    Vector<3> output = attractor->getPos();
    
    Hardware::hw.cvOutputPins[0]->analogWrite(output[X]*amp);
    Hardware::hw.cvOutputPins[1]->analogWrite(output[Y]*amp);
    Hardware::hw.cvOutputPins[2]->analogWrite(output[Z]*amp);

    Vector<2> rotated = rotate3dAndFlatten(output, 45*M_PI/180, -35*M_PI/180);
    Vector<2> rotated2d = rotate2d(rotated, rotation);
    Hardware::hw.cvOutputPins[3]->analogWrite(rotated2d[X]*amp);
    Hardware::hw.cvOutputPins[4]->analogWrite(rotated2d[Y]*amp);

    attractor = attractors2.getSelected();
    attractor->process();
    Hardware::hw.cvOutputPins[5]->analogWrite(attractor->getOutput(X)*amp);
    Hardware::hw.cvOutputPins[6]->analogWrite(attractor->getOutput(Y)*amp);
    Hardware::hw.cvOutputPins[7]->analogWrite(attractor->getOutput(Z)*amp);

    Hardware::hw.gateOutPin.digitalWrite(attractor->getOutput(Z) > 0);
}