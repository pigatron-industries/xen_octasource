#ifndef ClockSource_h
#define ClockSource_h

#include <inttypes.h>

#include "AbstractSource.h"
#include "../../lib/io/Timer.h"


class ClockSource : public AbstractSource {

public:
    void init();
    void execute(unsigned long timeDiff);
    void trigger();


    void setFrequencyHz(float frequencyHz);
    void setWave(float wave); // Swing control

private:
    uint16_t _pulseCount;
    float _frequency;
    float _swing;

    Timer _triggerTimer;

    float calculateSwingFrequency(float frequency);

};

#endif
