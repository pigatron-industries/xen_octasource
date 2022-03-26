#include "Display.h"
#include <eurorack.h>

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

void Display::drawWaveShape(WaveShape* waveShape, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t n) {
    u8g2.setDrawColor(0);
    u8g2.drawBox(x, y, width*n, height);
    u8g2.setDrawColor(1);

    float phaseInc = 1.0/float(width);
    float phase = 0;
    RangeScale scale = RangeScale(-1, 1, 0, height-1);

    for(uint8_t i = 0; i < width; i++) {
        float value = waveShape->get(phase);
        uint8_t pixelValue = scale.convert(value);

        for(int j = 0; j < n; j++) {
            uint8_t nx = x+(width*j);
            u8g2.drawPixel(nx+i, y+pixelValue);
        }

        phase += phaseInc;
    }

    u8g2.sendBuffer();
}