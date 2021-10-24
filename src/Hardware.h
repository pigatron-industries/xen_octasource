#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <hardware/max11300/MAX11300.h>
#include <eurorack_max11300.h>
#include <eurorack_is32fl3738.h>
#include <eurorack_dac8164.h>
#include "lib/io/AnalogInputPinSum.h"
#include "hwconfig.h"

class Hardware {
    public:
        static Hardware hw;
        void init();

        // Native pins
        DigitalInput(encoderBtnPin, ENCODER_BTN_PIN);

        // Direct connections
        RotaryEncoder encoder = RotaryEncoder(ENCODER_PIN1, ENCODER_PIN2);
        PushButton<> encoderButton = PushButton<>(encoderBtnPin);

        #if defined(OCTASOURCE_MKII)
            #define OctasourceInputDevice NativeDevice
            #define OctasourceOutputDevice DAC8164Device

            AnalogInput(waveCvPin, A8)
            AnalogInput(rateCvPin, A6)
            AnalogInput(ampCvPin, A3)
            AnalogInput(phaseCvPin, A7)
            AnalogInput(syncCvPin, A9)
            DigitalOutput(gateOutPin, GATE_OUTPUT_PIN);

            DAC8164Device dac8164a = DAC8164Device(-1, DAC1_SYNC_PIN);
            DAC8164Device dac8164b = DAC8164Device(-1, DAC2_SYNC_PIN);
            AnalogOutputPin<DAC8164Device>* cvOutputPins[OUTPUT_CV_COUNT] = {
                &dac8164b.pins[1],
                &dac8164a.pins[2],
                &dac8164a.pins[1],
                &dac8164a.pins[0],
                &dac8164a.pins[3],
                &dac8164b.pins[0],
                &dac8164b.pins[3],
                &dac8164b.pins[2]
            };

            IS32FL3738Device is32fl3738 = IS32FL3738Device(Wire);
            AnalogOutputPin<IS32FL3738Device>* encoderLeds[16] = {
                &is32fl3738.pins[31],
                &is32fl3738.pins[30],
                &is32fl3738.pins[29],
                &is32fl3738.pins[28],
                &is32fl3738.pins[27],
                &is32fl3738.pins[26],
                &is32fl3738.pins[25],
                &is32fl3738.pins[24],
                &is32fl3738.pins[16],
                &is32fl3738.pins[17],
                &is32fl3738.pins[18],
                &is32fl3738.pins[19],
                &is32fl3738.pins[20],
                &is32fl3738.pins[21],
                &is32fl3738.pins[22],
                &is32fl3738.pins[23]
            };
        #endif

        #if defined(OCTASOURCE_MKI)
            #define OctasourceInputDevice MAX11300Device
            #define OctasourceOutputDevice MAX11300Device

            MAX11300Device max11300 = MAX11300Device(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);
            // AnalogInputPinSum<MAX11300Device> test = AnalogInputPinSum<MAX11300Device>(max11300.pins[RATE_CV_PIN], max11300.pins[RATE_POT_PIN]);
            //AnalogInputOutputPin<MAX11300Device>& rateCvPin = max11300.pins[RATE_CV_PIN];
            AnalogInputOutputPin<MAX11300Device>& rateCvPin = max11300.pins[RATE_POT_PIN];
            //AnalogInputOutputPin<MAX11300Device>& waveCvPin = max11300.pins[WAVE_CV_PIN];
            AnalogInputOutputPin<MAX11300Device>& waveCvPin = max11300.pins[WAVE_POT_PIN];
            //AnalogInputOutputPin<MAX11300Device>& ampCvPin = max11300.pins[LENGTH_CV_PIN];
            AnalogInputOutputPin<MAX11300Device>& ampCvPin = max11300.pins[LENGTH_POT_PIN];
            AnalogInputOutputPin<MAX11300Device>& syncCvPin = max11300.pins[TRIGGER_IN_PIN];
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
        #endif
};

#endif