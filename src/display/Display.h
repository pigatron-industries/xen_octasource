#ifndef Display_h
#define Display_h

#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <eurorack_dsp.h>

using namespace eurorack;

class Display {
    public:
        Display() {}
        void init();

        void title(const char* text);
        void drawWaveShape(WaveShape* waveShape, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t n = 1);
    
    protected: 
        U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2 = U8G2_SSD1306_64X32_1F_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
};

#endif
