#ifndef PhasedSource_h
#define PhasedSource_h

#include <inttypes.h>

#include "AbstractSource.h"


class PhasedSource : public AbstractSource {

public:
    void init();
    void trigger();

};

#endif
