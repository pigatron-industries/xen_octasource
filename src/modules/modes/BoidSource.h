#ifndef BoidSource_h
#define BoidSource_h

#include <inttypes.h>

#include "AbstractSource.h"


struct Vector {
    float x;
    float y;
};

struct Boid {
    Vector position;
    Vector velocity;
};


class BoidSource : public AbstractSource {

public:
    void init();
    void execute(unsigned long timeDiff);

    void setFrequencyHz(float frequencyHz);
    void setAmplitude(float amplitude);
    void setWave(float wave);
    void setPosition(float position);
    void setTriggerValue(float value);
    void trigger();

private:
    Boid _boids[OSCILLATOR_COUNT];
    float _speed;
    float _distance;
    bool _trigger;
    Vector _goal;

    Vector ruleTowardsCentre(int boidIndex);
    Vector ruleKeepDistance(int boidIndex);
    Vector ruleMatchVelocity(int boidIndex);
    Vector ruleBoundingPosition(int boidIndex);
    Vector ruleGoalSeek(int boidIndex);
    void ruleVelocityLimit(int boidIndex);

};

#endif
