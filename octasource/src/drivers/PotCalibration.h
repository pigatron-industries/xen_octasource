#ifndef PotCalibration_h
#define PotCalibration_h

#include <inttypes.h>


class PotCalibration {

public:
    PotCalibration(float realMin, float realMax);
    float getCalibratedValue(float realValue);

private:
  float _realMin;
  float _realMax;

};

#endif
