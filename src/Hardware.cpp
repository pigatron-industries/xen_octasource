#include "Hardware.h"

Hardware Hardware::hw = Hardware();

void Hardware::init() {
    Serial2.begin(SERIAL_BAUD);

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
    }

    max11300.setDeferredOutput(true);
}