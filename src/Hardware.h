#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <hardware/max11300/MAX11300.h>
#include <eurorack_max11300.h>
#include "hwconfig.h"

class Hardware {
    public:
        static Hardware hw;
        void init();

        // Native pins
        DigitalInput(ENCODER_BTN_PIN);

        // Direct connections
        RotaryEncoder encoder = RotaryEncoder(ENCODER_PIN1, ENCODER_PIN2);
        PushButton<> encoderButton = PushButton<>(DENCODER_BTN_PIN);

        // MAX11300
        MAX11300Device max11300 = MAX11300Device(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);

        AnalogInputOutputPin<MAX11300Device>& rateCvPin = max11300.pins[RATE_CV_PIN];
        AnalogInputOutputPin<MAX11300Device>& ratePotPin = max11300.pins[RATE_POT_PIN];
        AnalogInputOutputPin<MAX11300Device>& waveCvPin = max11300.pins[WAVE_CV_PIN];
        AnalogInputOutputPin<MAX11300Device>& wavePotPin = max11300.pins[WAVE_POT_PIN];
        AnalogInputOutputPin<MAX11300Device>& ampCvPin = max11300.pins[LENGTH_CV_PIN];
        AnalogInputOutputPin<MAX11300Device>& ampPotPin = max11300.pins[LENGTH_POT_PIN];
        AnalogInputOutputPin<MAX11300Device>& triggerInPin = max11300.pins[TRIGGER_IN_PIN];

        AnalogInputOutputPin<MAX11300Device>* cvOutputPins[OUTPUT_CV_COUNT] = {
            &max11300.pins[OUTPUT_CV_PIN_START],
            &max11300.pins[OUTPUT_CV_PIN_START+1],
            &max11300.pins[OUTPUT_CV_PIN_START+2],
            &max11300.pins[OUTPUT_CV_PIN_START+3],
            &max11300.pins[OUTPUT_CV_PIN_START+4],
            &max11300.pins[OUTPUT_CV_PIN_START+5],
            &max11300.pins[OUTPUT_CV_PIN_START+6],
            &max11300.pins[OUTPUT_CV_PIN_START+7]
        }; 
};

#endif