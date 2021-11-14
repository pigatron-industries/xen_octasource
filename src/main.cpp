#include <Arduino.h>

#include "hwconfig.h"
#include "Config.h"

#include "MainController.h"
#include "controllers/PhasedController.h"
#include "controllers/FrequencyController.h"
#include "controllers/FilterController.h"
#include "controllers/ClockController.h"
#include "controllers/EnvelopeController.h"
#include "controllers/AttractorController.h"
#include "controllers/PhysicalModelController.h"
#include "controllers/ThreeBodyController.h"

MainController mainController = MainController(SAMPLE_RATE);

PhasedController phasedController = PhasedController();
FrequencyController frequencyController = FrequencyController();
FilterController filterController = FilterController();
ClockController clockController = ClockController();
EnvelopeController envelopeController = EnvelopeController();
AttractorController attractorController = AttractorController();
PhysicalModelController physicalModelController = PhysicalModelController();
ThreeBodyController threeBodyController = ThreeBodyController();

void setup() {
    delay(100);
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
    mainController.registerController(clockController);
    mainController.registerController(envelopeController);
    mainController.registerController(attractorController);
    mainController.registerController(physicalModelController);
    mainController.registerController(threeBodyController);
    mainController.init();
}

void loop() {
    mainController.update();
}
