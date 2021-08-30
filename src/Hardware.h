#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <hardware/max11300/MAX11300.h>
#include <hardware/max11300/MAX11300AnalogInputPin.h>
#include <hardware/max11300/MAX11300AnalogOutputPin.h>
#include "hwconfig.h"

class Hardware {
    public:
        static Hardware hw;
        void init();

        // Direct connections
        RotaryEncoder encoder = RotaryEncoder(ENCODER_PIN1, ENCODER_PIN2);
        PushButton<> encoderButton = PushButton<>(DigitalInputPin(ENCODER_BTN_PIN));

        MAX11300 max11300 = MAX11300(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);

        MAX11300AnalogInputPin rateCvPin = MAX11300AnalogInputPin(max11300, RATE_CV_PIN);
        MAX11300AnalogInputPin ratePotPin = MAX11300AnalogInputPin(max11300, RATE_POT_PIN);
        MAX11300AnalogInputPin waveCvPin = MAX11300AnalogInputPin(max11300, WAVE_CV_PIN);
        MAX11300AnalogInputPin wavePotPin = MAX11300AnalogInputPin(max11300, WAVE_POT_PIN);
        MAX11300AnalogInputPin ampCvPin = MAX11300AnalogInputPin(max11300, LENGTH_CV_PIN);
        MAX11300AnalogInputPin ampPotPin = MAX11300AnalogInputPin(max11300, LENGTH_POT_PIN);
        MAX11300AnalogInputPin triggerInPin = MAX11300AnalogInputPin(max11300, TRIGGER_IN_PIN);

        MAX11300AnalogOutputPin cvOutputPins[OUTPUT_CV_COUNT] = {
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START),
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START+1),
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START+2),
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START+3),
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START+4),
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START+5),
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START+6),
            MAX11300AnalogOutputPin(max11300, OUTPUT_CV_PIN_START+7)
        };
};

#endif