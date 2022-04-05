#include "SpringPendulum.h"

void SpringPendulum::init(float sampleRate) {
    ContinuousSystemN::init(sampleRate);
    pos[X] = 0;
    pos[Y] = 0;
    mult[X] = 1;
    mult[Y] = 1;
    offset[X] = 0;
    offset[Y] = 0;
    speedMult = 1;

    //body.mass = 1;

    //Vector<2> forceGravity = Vector<2>(0, -g * body.mass);
}

void SpringPendulum::process() {

    // float springLength = body.position.length();
    // float stretch = spring.restLength - springLength;
    // Vector<2> forceSpring = (body.position/springLength) * stretch * -spring.stiffness;



    pos[X] = 0;
    pos[Y] = 0;
}
