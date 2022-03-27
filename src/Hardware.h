#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <hardware/max11300/MAX11300.h>
#include <eurorack_max11300.h>
#include <eurorack_is32fl3738.h>
#include <eurorack_dac8164.h>
#include "lib/io/AnalogInputPinSum.h"
#include "display/Display.h"
#include "Colour.h"
#include "hwconfig.h"

#define MEMPOOL_SIZE 48*1024

class Hardware {
    public:
        static Hardware hw;
        void init();

        void clearOutputLeds();
        void updateOutputLeds();
        void updateOutputLeds(Colour negative, Colour positive);

        // Memory pool
        static float memPoolBuffer[MEMPOOL_SIZE];
        MemPool<float> memPool = MemPool<float>(Hardware::memPoolBuffer, MEMPOOL_SIZE);

        // Direct connections
        RotaryEncoderButton encoder = RotaryEncoderButton(ENCODER_PIN1, ENCODER_PIN2, ENCODER_BTN_PIN);

        #if defined(OCTASOURCE_MKII)
            #define AnalogInputPinT AnalogInputPin<NativeDevice>
            #define AnalogInputSumPinT AnalogInputSumPin<NativeDevice>
            #define AnalogOutputDeviceT DAC8164Device
            #define DigitalOutputDeviceT NativeDevice

            AnalogInput(wavePotPin, A10)
            AnalogInput(ratePotPin, A11)
            AnalogInput(ampPotPin, A13)
            AnalogInput(phasePotPin, A12)
            AnalogInput(waveCvPin, A8)
            AnalogInput(rateCvPin, A6)
            AnalogInput(ampCvPin, A3)
            AnalogInput(phaseCvPin, A7)
            AnalogInput(syncCvPin, A2)
            AnalogInput(modeCvPin, A9)
            DigitalOutput(gateOutPin, GATE_OUTPUT_PIN);

            AnalogInputSumPin<> waveSumPin = AnalogInputSumPin<>(wavePotPin, waveCvPin);
            AnalogInputSumPin<> rateSumPin = AnalogInputSumPin<>(ratePotPin, rateCvPin);
            AnalogInputSumPin<> ampSumPin = AnalogInputSumPin<>(ampPotPin, ampCvPin);
            AnalogInputSumPin<> phaseSumPin = AnalogInputSumPin<>(phasePotPin, phaseCvPin);

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

            IS32FL3738Device is32fl3738 = IS32FL3738Device(Wire, SDB_PIN);
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
            AnalogOutputPin<IS32FL3738Device>* outputRedLeds[8] = {
                &is32fl3738.pins[0],
                &is32fl3738.pins[1],
                &is32fl3738.pins[3],
                &is32fl3738.pins[6],
                &is32fl3738.pins[7],
                &is32fl3738.pins[5],
                &is32fl3738.pins[4],
                &is32fl3738.pins[2],
            };
            AnalogOutputPin<IS32FL3738Device>* outputBlueLeds[8] = {
                &is32fl3738.pins[8],
                &is32fl3738.pins[9],
                &is32fl3738.pins[11],
                &is32fl3738.pins[14],
                &is32fl3738.pins[15],
                &is32fl3738.pins[13],
                &is32fl3738.pins[12],
                &is32fl3738.pins[10]
            };
            AnalogOutputPin<IS32FL3738Device>* outputGreenLeds[8] = {
                &is32fl3738.pins[32],
                &is32fl3738.pins[33],
                &is32fl3738.pins[35],
                &is32fl3738.pins[38],
                &is32fl3738.pins[39],
                &is32fl3738.pins[37],
                &is32fl3738.pins[36],
                &is32fl3738.pins[34]
            };

            Display display;

        #endif

        #if defined(OCTASOURCE_MKI)
            #define AnalogInputPinT AnalogInputPin<MAX11300Device>
            #define AnalogInputSumPinT AnalogInputSumPin<MAX11300Device>
            #define AnalogOutputDeviceT MAX11300Device
            #define DigitalOutputDeviceT MAX11300Device

            MAX11300Device max11300 = MAX11300Device(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);
            // AnalogInputPinSum<MAX11300Device> test = AnalogInputPinSum<MAX11300Device>(max11300.pins[RATE_CV_PIN], max11300.pins[RATE_POT_PIN]);
            AnalogInputOutputPin<MAX11300Device>& rateCvPin = max11300.pins[RATE_CV_PIN];
            AnalogInputOutputPin<MAX11300Device>& ratePotPin = max11300.pins[RATE_POT_PIN];
            AnalogInputOutputPin<MAX11300Device>& waveCvPin = max11300.pins[WAVE_CV_PIN];
            AnalogInputOutputPin<MAX11300Device>& wavePotPin = max11300.pins[WAVE_POT_PIN];
            AnalogInputOutputPin<MAX11300Device>& ampCvPin = max11300.pins[LENGTH_CV_PIN];
            AnalogInputOutputPin<MAX11300Device>& ampPotPin = max11300.pins[LENGTH_POT_PIN];
            AnalogInputOutputPin<MAX11300Device>& syncCvPin = max11300.pins[TRIGGER_IN_PIN];
            AnalogInputOutputPin<MAX11300Device>& gateOutPin = max11300.pins[OUTPUT_GATE_PIN];

            AnalogInputSumPinT waveSumPin = AnalogInputSumPinT(wavePotPin, waveCvPin);
            AnalogInputSumPinT rateSumPin = AnalogInputSumPinT(ratePotPin, rateCvPin);
            AnalogInputSumPinT ampSumPin = AnalogInputSumPinT(ampPotPin, ampCvPin);

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