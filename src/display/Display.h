#ifndef Display_h
#define Display_h

#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>

class Display {
    public:
        Display() {}
        void init();

        void title(const char* text);
    
    protected: 
        U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2 = U8G2_SSD1306_64X32_1F_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
};

#endif
