#include <Arduino.h>

#include "hwconfig.h"
#include "Config.h"

#include "MainController.h"
#include "controllers/PhasedController.h"
#include "controllers/FrequencyController.h"
#include "controllers/FilterController.h"
#include "controllers/ClockController.h"
#include "controllers/EnvelopeController.h"
#include "controllers/DelayController.h"
#include "controllers/BouncingBallController.h"
#include "controllers/AttractorController.h"
#include "controllers/DoublePendulumController.h"
#include "controllers/ThreeBodyController.h"
#include "controllers/VoltageReferenceController.h"

MainController mainController = MainController(SAMPLE_RATE);

PhasedController phasedController = PhasedController();
FrequencyController frequencyController = FrequencyController();
FilterController filterController = FilterController();
ClockController clockController = ClockController();
EnvelopeController envelopeController = EnvelopeController();
BouncingBallController bouncingBallController = BouncingBallController();
AttractorController attractorController = AttractorController();
DoublePendulumController doublePendulumController = DoublePendulumController();
ThreeBodyController threeBodyController = ThreeBodyController();
DelayController delayController = DelayController();
VoltageReferenceController voltageReferenceController = VoltageReferenceController();

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
    mainController.registerController(bouncingBallController);
    mainController.registerController(attractorController);
    mainController.registerController(doublePendulumController);
    mainController.registerController(threeBodyController);
    mainController.registerController(delayController);
    mainController.registerController(voltageReferenceController);
    mainController.init();

    ARM_DEMCR |= ARM_DEMCR_TRCENA;
    ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
}

void loop() {
    mainController.update();
}
