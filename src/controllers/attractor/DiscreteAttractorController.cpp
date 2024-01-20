#include "DiscreteAttractorController.h"


void DiscreteAttractorController::init(float sampleRate) {
    ClockedController::init(sampleRate);
    configParam(Parameter::ATTRACTOR1, 0, attractors1.getSize()-1);
    for(size_t i = 0; i < attractors1.getSize(); i++) {
        attractors1[i]->init();
    }
    init();
}

void DiscreteAttractorController::init() {
    Serial.println("Discrete Attractor");
    Hardware::hw.display.text("D ATTRACTOR");
    attractors1.select(parameters[Parameter::ATTRACTOR1].value);
    Hardware::hw.display.textLine(attractors1.getSelected()->getName(), OLEDDisplay::TEXTLINE_2);
}

void DiscreteAttractorController::cycleValue(int amount) {
    Serial.println(parameters.getSelectedIndex());
    parameters.getSelected().cycle(amount);

    attractors1.select(parameters[Parameter::ATTRACTOR1].value);
    Hardware::hw.display.textLine(attractors1.getSelected()->getName(), OLEDDisplay::TEXTLINE_2);

    save();
}

void DiscreteAttractorController::update() {
    ClockedController::updateRate();

    if(ampCvInput.update()) {
        amp = ampCvInput.getValue();
    }

    if(interpolationCvInput.update()) {
        attractors1.getSelected()->setInterpolation(interpolationCvInput.getValue());
    }

    Hardware::hw.updateOutputLeds();
}

void DiscreteAttractorController::process() {
    ClockedController::process();
}

void DiscreteAttractorController::onClock() {
    DiscreteSystemN<2>* attractor = attractors1.getSelected();
    attractor->process();
    Vector<2> output = attractor->getPos();

    Hardware::hw.cvOutputPins[0]->analogWrite(output[X]*amp);
    Hardware::hw.cvOutputPins[1]->analogWrite(output[Y]*amp);
}
