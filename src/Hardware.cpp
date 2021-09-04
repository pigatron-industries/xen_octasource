#include "Hardware.h"

Hardware Hardware::hw = Hardware();

void Hardware::init() {
    Serial2.begin(SERIAL_BAUD);
    pinMode(ENCODER_BTN_PIN, INPUT_PULLUP);

    rateCvPin.setPinType(PinType::ANALOG_INPUT);
    ratePotPin.setPinType(PinType::ANALOG_INPUT);
    waveCvPin.setPinType(PinType::ANALOG_INPUT);
    wavePotPin.setPinType(PinType::ANALOG_INPUT);
    ampCvPin.setPinType(PinType::ANALOG_INPUT);
    ampPotPin.setPinType(PinType::ANALOG_INPUT);
    triggerInPin.setPinType(PinType::ANALOG_INPUT);

    for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
        cvOutputPins[i]->setPinType(PinType::ANALOG_OUTPUT);
    }
}