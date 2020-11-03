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
        calibrationRealMin[i] = realMin;
        calibrationRealMax[i] = realMax;
    }

    selectedModeStartAddress = address;
    EEPROM.get(address, selectedMode);
    EEPROM.get(address+sizeof(uint8_t), selectedSubMode);
}

uint8_t Config::getSelectedMode() {
    return selectedMode;
}

uint8_t Config::getSelectedSubMode() {
    return selectedSubMode;
}

void Config::saveSelectedMode(uint8_t mode, uint8_t submode) {
    selectedMode = mode;
    selectedSubMode = submode;
    EEPROM.put(selectedModeStartAddress, selectedMode);
    EEPROM.put(selectedModeStartAddress+sizeof(uint8_t), selectedSubMode);
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
