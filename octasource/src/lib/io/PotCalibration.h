#ifndef PotCalibration_h
#define PotCalibration_h

#include <inttypes.h>


class PotCalibration {

public:
    PotCalibration();
    PotCalibration(uint8_t pin, float virtualMin, float virtualMax);
    PotCalibration(uint8_t pin, float realMin, float realMax, float virtualMin, float virtualMax);
    float getCalibratedValue(float realValue);

    uint8_t getPin() {
        return _pin;
    }

    void setRealMin(float realMin) {
        _realMin = realMin;
    }

    void setRealMax(float realMax) {
        _realMax = realMax;
    }

private:
    uint8_t _pin;
    float _realMin;
    float _realMax;
    float _virtualMin;
    float _virtualMax;

};

#endif
