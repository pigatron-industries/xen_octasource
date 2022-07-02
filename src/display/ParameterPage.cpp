#include "ParameterPage.h"

void ParameterPage::setLabel(int line, const char* text) {
    Hardware::hw.display.text(text, Display::LINE_HEIGHT*line, DISPLAY_FONT_WIDTH);
}

void ParameterPage::setValue(int line, int value) {
    Hardware::hw.display.text(value, Display::LINE_HEIGHT*line, DISPLAY_FONT_WIDTH*valueStart);
}

void ParameterPage::selectLine(int line) {
    Hardware::hw.display.text(" ", Display::LINE_HEIGHT*selectedLine, 0, DISPLAY_FONT_WIDTH);
    selectedLine = line;
    Hardware::hw.display.text(">", Display::LINE_HEIGHT*selectedLine, 0, DISPLAY_FONT_WIDTH);
}