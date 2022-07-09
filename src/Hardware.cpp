#include "Hardware.h"
#include "lib/io/AnalogPinCalibration.h"

Hardware Hardware::hw = Hardware();

float Hardware::memPoolBuffer[MEMPOOL_SIZE];

void Hardware::init() {
    NativeDevice::instance.init();

    Wire.setSDA(SDA_PIN);
    Wire.setSCL(SCL_PIN);
    Wire.setClock(I2C_SPEED);
    Wire.begin();

    #if defined(OCTASOURCE_MKII)
        is32fl3738.init();
        dac8164a.init();
        dac8164b.init();
        dac8164a.setDeferredOutput(true);
        dac8164b.setDeferredOutput(true);
        display.init();

        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            cvOutputPins[i]->loadCalibration();
        }
        for(int i = 0; i < 16; i++) {
            encoderLeds[i]->analogWrite(0);
        }
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            outputRedLeds[i]->analogWrite(0);
        }
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            outputBlueLeds[i]->analogWrite(0);
        }
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            outputGreenLeds[i]->analogWrite(0);
        }
    #endif

    #if defined(OCTASOURCE_MKI)
        max11300.init();
        max11300.setDeferredOutput(true);
    #endif

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
    }
}

void Hardware::clearOutputLeds() {
    #if defined(OCTASOURCE_MKII)
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            Hardware::hw.outputRedLeds[i]->analogWrite(0);
            Hardware::hw.outputGreenLeds[i]->analogWrite(0);
            Hardware::hw.outputBlueLeds[i]->analogWrite(0);
        }
    #endif
}

void Hardware::updateOutputLeds() {
    #if defined(OCTASOURCE_MKII)
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            float value = Hardware::hw.cvOutputPins[i]->getAnalogValue();
            if(value > 0) {
                Hardware::hw.outputRedLeds[i]->analogWrite(0);
                Hardware::hw.outputGreenLeds[i]->analogWrite(value*0.1);
            } else {
                Hardware::hw.outputGreenLeds[i]->analogWrite(0);
                Hardware::hw.outputRedLeds[i]->analogWrite(-value*0.1);
            }
        }
    #endif
}

void Hardware::updateOutputLeds(Colour negative, Colour positive) {
    #if defined(OCTASOURCE_MKII)
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            float value = Hardware::hw.cvOutputPins[i]->getAnalogValue();
            if(value > 0) {
                Hardware::hw.outputRedLeds[i]->analogWrite(value * positive.red * 0.1);
                Hardware::hw.outputGreenLeds[i]->analogWrite(value * positive.green * 0.1);
                Hardware::hw.outputBlueLeds[i]->analogWrite(value * positive.blue * 0.1);
            } else {
                Hardware::hw.outputRedLeds[i]->analogWrite(value * negative.red * 0.1);
                Hardware::hw.outputGreenLeds[i]->analogWrite(value * negative.green * 0.1);
                Hardware::hw.outputBlueLeds[i]->analogWrite(value * negative.blue * 0.1);
            }
        }
    #endif
}