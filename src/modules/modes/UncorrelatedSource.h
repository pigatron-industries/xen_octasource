#ifndef UncorrelatedSource_h
#define UncorrelatedSource_h

#include <inttypes.h>

#include "AbstractSource.h"


class UncorrelatedSource : public AbstractSource {

public:
    void init();
    void setFrequencyHz(float frequencyHz);

};

#endif
