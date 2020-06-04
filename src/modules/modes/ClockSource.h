#ifndef ClockSource_h
#define ClockSource_h

#include <inttypes.h>

#include "AbstractSource.h"
#include "../../lib/io/Timer.h"
#include "../../lib/io/GateInput.h"


class ClockSource : public AbstractSource {

public:
    void init();
    void execute(unsigned long timeDiff);
    void trigger();

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float rotationTriggerValue); //Used as rotation trigger
    void setWave(float wave); // Swing control

private:
    uint16_t _pulseCount;
    float _frequency;
    float _swing;

    Timer _triggerTimer;

    float _rotationTriggerValue;
    GateInput _rotationTrigger;
    int _outputRotation;

    float calculateSwingFrequency(float frequency);
    void rotateOutputs();
    uint8_t getRotatedOutputIndex(uint8_t index);

};

#endif
