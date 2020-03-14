#include "PotCalibration.h"

#include <Arduino.h>

PotCalibration::PotCalibration() :
    PotCalibration(0, 0, 0, 0, 0) {
}

PotCalibration::PotCalibration(uint8_t pin, float realMin, float realMax, float virtualMin, float virtualMax) :
    _pin(pin),
    _realMin(realMin),
    _realMax(realMax),
    _virtualMin(virtualMin),
    _virtualMax(virtualMax) {
}

float PotCalibration::getCalibratedValue(float realValue) {
    float realRange = _realMax - _realMin;
    float virtualRange = _virtualMax - _virtualMin;
    float virtualValue = (((realValue - _realMin) * virtualRange) / realRange) + _virtualMin;
    return virtualValue;
}
