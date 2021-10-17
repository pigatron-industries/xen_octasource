#include <Arduino.h>

#include "hwconfig.h"
#include "Config.h"

#include "MainController.h"
#include "controllers/PhasedController.h"
#include "controllers/FrequencyController.h"
#include "controllers/FilterController.h"
#include "controllers/AttractorController.h"
#include "controllers/ClockController.h"

MainController mainController = MainController(SAMPLE_RATE);

PhasedController phasedController = PhasedController();
FrequencyController frequencyController = FrequencyController();
FilterController filterController = FilterController();
ClockController clockController = ClockController();
AttractorController attractorController = AttractorController();

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();
    Hardware::hw.init();

    mainController.registerController(phasedController);
    mainController.registerController(frequencyController);
    mainController.registerController(filterController);
    mainController.registerController(attractorController);
    mainController.registerController(clockController);
    mainController.init();
}

void loop() {
    mainController.update();
}