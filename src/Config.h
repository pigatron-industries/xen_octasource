#ifndef Config_h
#define Config_h

#include <inttypes.h>
#include "lib/io/PotCalibration.h"

class Config {

    public:
        static Config instance;

        void load(uint8_t potCalibrationSize);
        uint8_t getSelectedMode();
        uint8_t getSelectedSubMode();
        float* getCalibrationRealMin() { return calibrationRealMin; }
        float* getCalibrationRealMax() { return calibrationRealMax; }

        void saveSelectedMode(uint8_t mode, uint8_t submode);
        void savePotCalibration(PotCalibration* potCalibration, uint8_t potCalibrationSize);
    
    private:
        float calibrationRealMin[10];
        float calibrationRealMax[10];
        uint8_t potCalibrationSize;
        uint8_t selectedMode;
        uint8_t selectedSubMode;

        int selectedModeStartAddress;

};

#endif
