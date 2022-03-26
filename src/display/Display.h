#ifndef Display_h
#define Display_h

#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <eurorack_dsp.h>
#include "PixelTrail.h"

using namespace eurorack;

class Display {
    public:
        Display() {}
        void init();

        void clear();
        void update();
        void text(const char* text, uint8_t x = TEXTLINE_1);
        void drawWaveShape(WaveShape* waveShape, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t n = 1, bool bipolar = true);

        template<int N>
        void drawPixelTrail(PixelTrail<N>& trail, Pixel pixel);
    
        static constexpr uint8_t TEXTLINE_1 = 0;
        static constexpr uint8_t TEXTLINE_2 = 8;
        static constexpr uint8_t TEXTLINE_3 = 16;
        static constexpr uint8_t TEXTLINE_4 = 24;
    
    protected: 
        U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2 = U8G2_SSD1306_64X32_1F_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
};


template<int N>
void Display::drawPixelTrail(PixelTrail<N>& trail, Pixel newPixel) {
    Pixel prevPixel = trail.getPrev();
    if(prevPixel.x != newPixel.x || prevPixel.y != newPixel.y) {
        Pixel lastPixel = trail.push(newPixel);
        u8g2.setDrawColor(0);
        u8g2.drawPixel(lastPixel.x, lastPixel.y);
        u8g2.setDrawColor(1);
        u8g2.drawPixel(newPixel.x, newPixel.y);        
    }
}

#endif
