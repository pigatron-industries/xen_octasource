#include "ClockDisplay.h"

void ClockDisplay::init() {
    page.addComponent(&title);

    page.addComponent(&clockRow1);
    clockRow1.addComponent(&clockFields[0]);
    clockRow1.addComponent(&clockFields[1]);
    clockRow1.addComponent(&clockFields[2]);
    clockRow1.addComponent(&clockFields[3]);
    page.addComponent(&clockRow2);
    clockRow2.addComponent(&clockFields[4]);
    clockRow2.addComponent(&clockFields[5]);
    clockRow2.addComponent(&clockFields[6]);
    clockRow2.addComponent(&clockFields[7]);
    page.addComponent(&clockRow3);
    clockRow3.addComponent(&lengthField);
    clockRow3.addComponent(&pauseField);
    clockRow3.addComponent(&sourceField);

    page.setContext(&Hardware::hw.display);
    page.layout();
}

void ClockDisplay::render() {
    Hardware::hw.display.clear();
    page.render();
    Hardware::hw.display.update();
}

void ClockDisplay::focusClock(uint8_t output) {
    focusManager.setFocus(&clockFields[output]);
}

void ClockDisplay::focusPause() {
    focusManager.setFocus(&pauseField);
}

void ClockDisplay::setClock(uint8_t output, bool divide, uint8_t value) {
    clockFields[output].setFormat(divide ? "/%d" : "x%d");
    clockFields[output].setValue(value);
    Hardware::hw.display.update();
}

void ClockDisplay::setLength(uint8_t length) {
    lengthField.setValue(length);
    Hardware::hw.display.update();
}

void ClockDisplay::setPause(bool pause) {
    pauseField.setValue(pause ? "--" : ">>");
    Hardware::hw.display.update();
}

void ClockDisplay::setSource(uint8_t source) {
    sourceField.setValue(source == 0 ? "INT" : "EXT");
    Hardware::hw.display.update();
}