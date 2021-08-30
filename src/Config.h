#ifndef Config_h
#define Config_h

#include <inttypes.h>

class PotCalibration {
    public:
        int min;
        int max;
};

class Mode {
    public:
        uint8_t controllerIndex;
        uint8_t controllerMode;
};

class Config {

    public:
        static Config data;
        PotCalibration calibration[4];
        Mode mode;

        static void load();
        static void saveMode();
        static void saveCalibration();
    
};

#endif
