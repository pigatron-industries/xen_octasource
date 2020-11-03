#ifndef MultipliedSource_h
#define MultipliedSource_h

#include <inttypes.h>

#include "AbstractSource.h"


class MultipliedSource : public AbstractSource {

public:
    void init();
    void setMode(uint8_t mode);
    void setFrequencyHz(float frequencyHz);

};

#endif
