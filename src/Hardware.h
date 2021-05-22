#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <hardware/max11300/MAX11300.h>
#include <hardware/max11300/MAX11300Pin.h>
#include "hwconfig.h"

class Hardware {
    public:
        static Hardware hw;
        void init();

        MAX11300 max11300 = MAX11300(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);
        MAX11300Pin cvPins[20] = {
            MAX11300Pin(max11300, 0),
            MAX11300Pin(max11300, 1),
            MAX11300Pin(max11300, 2),
            MAX11300Pin(max11300, 3),
            MAX11300Pin(max11300, 4),
            MAX11300Pin(max11300, 5),
            MAX11300Pin(max11300, 6),
            MAX11300Pin(max11300, 7),
            MAX11300Pin(max11300, 8),
            MAX11300Pin(max11300, 9),
            MAX11300Pin(max11300, 10),
            MAX11300Pin(max11300, 11),
            MAX11300Pin(max11300, 12),
            MAX11300Pin(max11300, 13),
            MAX11300Pin(max11300, 14),
            MAX11300Pin(max11300, 15),
            MAX11300Pin(max11300, 16),
            MAX11300Pin(max11300, 17),
            MAX11300Pin(max11300, 18),
            MAX11300Pin(max11300, 19)
        };
};

#endif