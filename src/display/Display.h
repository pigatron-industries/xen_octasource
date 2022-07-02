#ifndef Display_h
#define Display_h

#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <eurorack_dsp.h>
#include "PixelTrail.h"

using namespace eurorack;

#define DISPLAY_WIDTH 64

#define DISPLAY_FONT u8g2_font_5x7_mf
#define DISPLAY_FONT_HEIGHT 7
#define DISPLAY_FONT_WIDTH 5

class Display {
    public:
        Display() {}
        void init();

        void clear();
        void update();
        void text(const char* text, uint8_t x = TEXTLINE_1, uint8_t y = 0, uint8_t w = DISPLAY_WIDTH);
        void text(int num, uint8_t x = TEXTLINE_1, uint8_t y = 0, uint8_t w = DISPLAY_WIDTH);
        void drawWaveShape(WaveShape* waveShape, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t n = 1, bool bipolar = true);

        template<int N>
        void drawPixelTrail(PixelTrail<N>& trail, Pixel pixel);
    
        static constexpr uint8_t LINE_HEIGHT = DISPLAY_FONT_HEIGHT+1;
        static constexpr uint8_t TEXTLINE_1 = 0;
        static constexpr uint8_t TEXTLINE_2 = LINE_HEIGHT;
        static constexpr uint8_t TEXTLINE_3 = LINE_HEIGHT*2;
        static constexpr uint8_t TEXTLINE_4 = LINE_HEIGHT*3;
    
    protected: 
        U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2 = U8G2_SSD1306_64X32_1F_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);

        char buffer[13];
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
