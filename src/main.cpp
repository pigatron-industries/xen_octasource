#include <Arduino.h>

#include "hwconfig.h"
#include "Config.h"

#include "MainController.h"
#include "modules/OctaSource.h"


OctaSource octasource  = OctaSource();
MainController mainController = MainController(octasource);


void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();
    Config::instance.load(CALIBRATED_POT_SIZE);
    mainController.init();
}

void loop() {

    mainController.run();
}
