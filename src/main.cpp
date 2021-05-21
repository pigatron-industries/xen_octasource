#include <Arduino.h>

#include "hwconfig.h"
#include "Config.h"

#include "MainController.h"
#include "drivers/CvInputOutput.h"
#include "modules/OctaSource.h"


// hardware
CvInputOutput cvInputOutput = CvInputOutput(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);

OctaSource octasource  = OctaSource();
MainController mainController = MainController(cvInputOutput, octasource);


void setup() {
    Serial.begin(SERIAL_BAUD);
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
