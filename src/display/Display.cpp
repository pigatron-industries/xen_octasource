#include "Display.h"

void Display::init() {
    u8g2.begin();
    u8g2.clearBuffer();	
    u8g2.sendBuffer();
}

void Display::title(const char* text) {
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setDrawColor(0);
    u8g2.drawBox(0, 0, 64, 7);
    u8g2.setDrawColor(1);
    u8g2.drawStr(0, 6, text);
    u8g2.sendBuffer();
}

