#ifndef PotCalibration_h
#define PotCalibration_h

#include <inttypes.h>


class PotCalibration {

public:
    PotCalibration();
    PotCalibration(uint8_t pin, float realMin, float realMax, float virtualMin, float virtualMax);
    float getCalibratedValue(float realValue);

private:
  uint8_t _pin;
  float _realMin;
  float _realMax;
  float _virtualMin;
  float _virtualMax;

};

#endif
