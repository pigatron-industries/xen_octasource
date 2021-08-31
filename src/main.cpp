#include <Arduino.h>

#include "hwconfig.h"
#include "Config.h"

#include "MainController.h"
#include "controllers/PhasedController.h"
#include "controllers/MultipliedController.h"

MainController mainController = MainController(SAMPLE_RATE);

PhasedController phasedController = PhasedController();
MultipliedController multipliedController = MultipliedController();

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();
    Hardware::hw.init();
    mainController.registerController(phasedController);
    mainController.registerController(multipliedController);
    mainController.init();
}

void loop() {
    mainController.update();
}
