#ifndef Config_h
#define Config_h

#include <inttypes.h>
#include "lib/io/PotCalibration.h"

class Config {

    public:
        static Config instance;

        void load(uint8_t potCalibrationSize);
        uint8_t getSelectedMode();
        PotCalibration* getPotCalibrations();

        void saveSelectedMode(uint8_t id);
        void savePotCalibration(PotCalibration* potCalibration, uint8_t potCalibrationSize);
    
    private:
        PotCalibration potCalibration[20];
        uint8_t potCalibrationSize;
        uint8_t selectedMode;

        int selectedModeStartAddress;

};

#endif
