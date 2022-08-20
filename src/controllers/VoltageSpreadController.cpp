#include "VoltageSpreadController.h"

void VoltageSpreadController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void VoltageSpreadController::init() {
    Serial.println("Voltage Spread");
    Hardware::hw.display.textLine("VOLT SPREAD");
}

void VoltageSpreadController::update() {
    if(spreadCvInput.update()) {
        float spread = spreadCvInput.getValue();
        voltageOffsets[0] = 0;
        voltageOffsets[1] = 1*0.4 * spread;
        voltageOffsets[7] = -1*0.4 * spread;
        voltageOffsets[2] = 3*0.4 * spread;
        voltageOffsets[6] = -3*0.4 * spread;
        voltageOffsets[3] = 5*0.4 * spread;
        voltageOffsets[5] = -5*0.4 * spread;
        voltageOffsets[4] = 0;
    }

    Serial.println(Hardware::hw.cvOutputPins[3]->getAnalogValue());
    Hardware::hw.updateOutputLeds();
}


void VoltageSpreadController::process() {
    if(clockDivider.tick()) {
        float value = Hardware::hw.syncCvPin.analogRead();
        //float value = 0;
        for(int i = 0; i < OUTPUT_CV_COUNT; i++) {
            Hardware::hw.cvOutputPins[i]->analogWrite(value + voltageOffsets[i]);
        }
    }
}
