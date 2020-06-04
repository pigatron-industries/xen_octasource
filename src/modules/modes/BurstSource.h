#ifndef BurstSource_h
#define BurstSource_h

#include <inttypes.h>

#include "AbstractSource.h"


class BurstSource : public AbstractSource {

public:
    void init();
    void trigger();

};

#endif
