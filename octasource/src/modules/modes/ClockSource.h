#ifndef ClockSource_h
#define ClockSource_h

#include <inttypes.h>

#include "AbstractSource.h"
#include "../../lib/io/Timer.h"

class ClockSource : public AbstractSource {

public:
    void init();
    void execute(unsigned long timeDiff);

    void setFrequencyHz(float frequencyHz);
    void setWave(float wave); // Swing control

private:
    uint8_t _pulseCount;
};

#endif
