#include "ShapeController.h"

void ShapeController::init(float sampleRate) {
    ParameterizedController::init(sampleRate);
    renderer.init(sampleRate);
    renderer.setSpeed(400);

    // renderer.addShape(&line);
    renderer.addShape(&square);
    renderer.addShape(&triangle1);
    renderer.addShape(&triangle2);

    triangle1.setOffset({3, 0});
    triangle2.setOffset({-3, 0});
    triangle2.setScale({1, -1});

    oscillator.init(sampleRate);

    init();
}

void ShapeController::init() {
    Serial.println("Shapes");
    Hardware::hw.display.textLine("SHAPES");
}

void ShapeController::update() {
    if(expRateCvInput.update()) {
        Serial.println(expRateCvInput.getValue());
        renderer.setSpeed(expRateCvInput.getValue());
        oscillator.setFrequency(expRateCvInput.getValue());
    }

    Hardware::hw.updateOutputLeds();
}

void ShapeController::process() {
    renderer.process();
    Hardware::hw.cvOutputPins[0]->analogWrite(renderer.getPos()[X]);
    Hardware::hw.cvOutputPins[1]->analogWrite(renderer.getPos()[Y]);
    Hardware::hw.cvOutputPins[3]->analogWrite(oscillator.process());
}

