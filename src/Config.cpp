#include "Config.h"
#include <EEPROM.h>
#include <Arduino.h>

Config Config::instance;

void Config::load(uint8_t potCalibrationSize) {
    int address = 0;
    float realMin, realMax;
    for(uint8_t i = 0; i < potCalibrationSize; i++) {
        EEPROM.get(address, realMin);
        address += sizeof(float);
        EEPROM.get(address, realMax);
        address += sizeof(float);
        potCalibration[i].setRealMin(realMin);
        potCalibration[i].setRealMax(realMax);
    }

    selectedModeStartAddress = address;
    EEPROM.get(address, selectedMode);
}

uint8_t Config::getSelectedMode() {
    return selectedMode;
}

PotCalibration* Config::getPotCalibrations() {
    return potCalibration;
}

void Config::saveSelectedMode(uint8_t id) {
    selectedMode = id;
    EEPROM.put(selectedModeStartAddress, selectedMode);
}

void Config::savePotCalibration(PotCalibration* potCalibration, uint8_t potCalibrationSize) {
    int address = 0;
    for(uint8_t i = 0; i < potCalibrationSize; i++) {
        EEPROM.put(address, potCalibration[i].getRealMin());
        address += sizeof(float);
        EEPROM.put(address, potCalibration[i].getRealMax());
        address += sizeof(float);
    }
}
