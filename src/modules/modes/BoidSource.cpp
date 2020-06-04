#include "BoidSource.h"

#include <Arduino.h>
#include <math.h>

void BoidSource::init() {
    _distance = 0.5;
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        _boids[i].position.x = (float(random(100))-50)/100;
        _boids[i].position.y = (float(random(100))-50)/100;
        _boids[i].velocity.x = 0;
        _boids[i].velocity.y = 0;
    }
}

void BoidSource::setFrequencyHz(float frequencyHz) {
    _speed = frequencyHz;
}

void BoidSource::setAmplitude(float amplitude) {

}

void BoidSource::setWave(float wave) {
    // _goal.x = wave;
    // _goal.y = (float(random(100))-50)/100;
    _distance = wave/4;
}

void BoidSource::setPosition(float position) {

}

void BoidSource::setTriggerValue(float value) {
    if(value > 3) {
        _trigger = true;
    } else {
        _trigger = false;
    }
}

void BoidSource::trigger() {
}

void BoidSource::execute(unsigned long timeDiff) {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        Vector newVelocity = {0, 0};
        Vector v = {0, 0};
        v = ruleTowardsCentre(i);
        newVelocity.x += v.x;
        newVelocity.y += v.y;
        v = ruleKeepDistance(i);
        newVelocity.x += v.x;
        newVelocity.y += v.y;
        v = ruleMatchVelocity(i);
        newVelocity.x += v.x;
        newVelocity.y += v.y;
        v = ruleBoundingPosition(i);
        newVelocity.x += v.x;
        newVelocity.y += v.y;
        // v = ruleGoalSeek(i);
        // newVelocity.x += v.x;
        // newVelocity.y += v.y;
        _boids[i].velocity.x += newVelocity.x;
        _boids[i].velocity.y += newVelocity.y;
        ruleVelocityLimit(i);
        _boids[i].position.x += _boids[i].velocity.x * (float(timeDiff)/100000) * _speed;
        _boids[i].position.y += _boids[i].velocity.y * (float(timeDiff)/100000) * _speed;
        _outputs[i] = _boids[i].position.x;
    }

    _outputs[0] = _boids[0].position.x;
    _outputs[1] = _boids[0].position.y;
    _outputs[2] = _boids[1].position.x;
    _outputs[3] = _boids[1].position.y;
    _outputs[4] = _boids[2].position.x;
    _outputs[5] = _boids[2].position.y;
    _outputs[6] = _boids[3].position.x;
    _outputs[7] = _boids[3].position.y;
}


float getDistance(Vector v1, Vector v2) {
    return sqrt(abs(v1.x-v2.x) + abs(v1.y-v2.y));
}

float getSize(Vector v) {
    return sqrt(abs(v.x) + abs(v.y));
}


Vector BoidSource::ruleTowardsCentre(int j) {
    Vector centre = {0, 0};
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        if(i != j) {
            centre.x += _boids[i].position.x;
            centre.y += _boids[i].position.y;
        }
    }
    centre.x /= OSCILLATOR_COUNT-1;
    centre.y /= OSCILLATOR_COUNT-1;

    if(!_trigger) {
        return {
            (centre.x - _boids[j].position.x) / 100,
            (centre.y - _boids[j].position.y) / 100
        };
    } else {
        return {
            -(centre.x - _boids[j].position.x) / 100,
            -(centre.y - _boids[j].position.y) / 100
        };
    }
}

Vector BoidSource::ruleKeepDistance(int j) {
    Vector repel = {0, 0};
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        if(i != j) {
            if(getDistance(_boids[i].position, _boids[j].position) < _distance) {
                repel.x -= _boids[i].position.x - _boids[j].position.x;
                repel.y -= _boids[i].position.y - _boids[j].position.y;
            }
        }
    }
    return repel;
}

Vector BoidSource::ruleMatchVelocity(int j) {
    Vector velocity = {0, 0};
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        if(i != j) {
            velocity.x += _boids[i].velocity.x;
            velocity.y += _boids[i].velocity.y;
        }
    }
    velocity.x /= OSCILLATOR_COUNT-1;
    velocity.y /= OSCILLATOR_COUNT-1;
    return {
        (velocity.x - _boids[j].velocity.x) / 10,
        (velocity.y - _boids[j].velocity.y) / 10
    };
}

Vector BoidSource::ruleBoundingPosition(int j) {
    Vector v;
    if(_boids[j].position.x < -5) {
        v.x = 0.1;
    } else if(_boids[j].position.x > 5) {
        v.x = -0.1;
    }
    if(_boids[j].position.y < -5) {
        v.y = 0.1;
    } else if(_boids[j].position.y > 5) {
        v.y = -0.1;
    }
    return v;
}

Vector BoidSource::ruleGoalSeek(int j) {
    return {
        (_goal.x - _boids[j].position.x) / 100,
        (_goal.y - _boids[j].position.y) / 100,
    };
}

void BoidSource::ruleVelocityLimit(int j) {
    float velocityLimit = 1;
    float velocitySize = getSize(_boids[j].velocity);
    if(velocitySize > velocityLimit) {
        _boids[j].velocity.x = (_boids[j].velocity.x / velocitySize) * velocityLimit;
        _boids[j].velocity.y = (_boids[j].velocity.y / velocitySize) * velocityLimit;
    }
}
