#include "Hardware.h"

Hardware Hardware::hw = Hardware();

void Hardware::init() {
    Serial2.begin(SERIAL_BAUD);
    rateCvPin.init();
    ratePotPin.init();
    waveCvPin.init();
    wavePotPin.init();
    ampCvPin.init();
    ampPotPin.init();
    triggerInPin.init();

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        cvOutputPins[i].init();
    }
}