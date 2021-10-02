#include "Hardware.h"

Hardware Hardware::hw = Hardware();

void Hardware::init() {
    analogReadResolution(12);

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

        for(int i = 0; i < 16; i++) {
            encoderLeds[i]->analogWrite(0);
        }
    #endif

    #if defined(OCTASOURCE_MKI)
        max11300.setDeferredOutput(true);
    #endif

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
    }
}
