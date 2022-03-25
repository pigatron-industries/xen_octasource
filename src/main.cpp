#include <Arduino.h>
#include "hwconfig.h"
#include "MainController.h"

MainController mainController = MainController(SAMPLE_RATE);

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();

    mainController.init();
}

void loop() {
    mainController.update();
}
