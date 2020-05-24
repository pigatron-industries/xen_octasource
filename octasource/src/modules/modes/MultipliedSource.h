#ifndef MultipliedSource_h
#define MultipliedSource_h

#include <inttypes.h>

#include "AbstractSource.h"


class MultipliedSource : public AbstractSource {

public:
    void init();
    long setMode(long movement);
    void setFrequencyHz(float frequencyHz);

};

#endif
