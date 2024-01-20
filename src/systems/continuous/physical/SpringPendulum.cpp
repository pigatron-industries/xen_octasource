#include "SpringPendulum.h"

SpringPendulum::SpringPendulum() {
    physics.addBody(&fixedBody);
    physics.addBody(&body);
    physics.addConstraint(&spring);
    physics.addForce(&gravity);
}

void SpringPendulum::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    pos[X] = 0;
    pos[Y] = 0;
    mult[X] = 1;
    mult[Y] = 1;
    offset[X] = 0;
    offset[Y] = 0;
    speedMult = 1;
    setInitialConditions(Vector<2>(0, -3), Vector<2>(0.01, 0.5));
}

void SpringPendulum::setInitialConditions(Vector<2> bodyPosition, Vector<2> bodyVelocity) {
    body.setPosition(bodyPosition);
    body.setVelocity(bodyVelocity);
}

void SpringPendulum::process() {
    physics.update(dt);
    pos[X] = body.getPosition()[X];
    pos[Y] = body.getPosition()[Y];
}
