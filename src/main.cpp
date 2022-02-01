#include <Arduino.h>
#include "hwconfig.h"
#include "MainController.h"

MainController mainController = MainController(SAMPLE_RATE);

void setup() {
    delay(100);
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();
    Hardware::hw.init();

    mainController.init();

    ARM_DEMCR |= ARM_DEMCR_TRCENA;
    ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
}

void loop() {
    mainController.update();
}
