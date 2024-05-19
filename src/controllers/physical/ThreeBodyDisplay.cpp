#include "ThreeBodyDisplay.h"


void ThreeBodyDisplay::init() {
    page.addComponent(&title);
    page.addComponent(&typeField);
    page.addComponent(&outputField);

    page.setContext(&Hardware::hw.display);
    page.layout();
}

void ThreeBodyDisplay::render() {
    Hardware::hw.display.clear();
    page.render();
    Hardware::hw.display.update();
}

void ThreeBodyDisplay::focusType() {
    focusManager.setFocus(&typeField);
}

void ThreeBodyDisplay::focusOutput() {
    focusManager.setFocus(&outputField);
}

void ThreeBodyDisplay::setType(char* type) {
    typeField.setValue(type);
    Hardware::hw.display.update();
}

void ThreeBodyDisplay::setOutput(char* outputType) {
    outputField.setValue(outputType);
    Hardware::hw.display.update();
}