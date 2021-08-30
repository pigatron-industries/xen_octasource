#include "Config.h"
#include <EEPROM.h>
#include <Arduino.h>

Config Config::data;

void Config::load() {
    int address = 0;
    EEPROM.get(address, data);
}

void Config::saveCalibration() {
    int address = 0;
    EEPROM.put(address, data.calibration);
}

void Config::saveMode() {
    int address = sizeof(calibration);
    EEPROM.put(address, data.mode);
}
