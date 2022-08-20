#include "SequenceQuantizerDisplay.h"

void SequenceQuantizerDisplay::init() {
    page.addComponent(&title);
    page.addComponent(&lengthField);

    page.setContext(&Hardware::hw.display);
    page.layout();
}

void SequenceQuantizerDisplay::render() {
    Hardware::hw.display.clear();
    page.render();
    Hardware::hw.display.update();
}

void SequenceQuantizerDisplay::setLength(uint8_t length) {
    lengthField.setValue(length);
    Hardware::hw.display.update();
}
