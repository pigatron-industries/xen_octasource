#include "ConstraintGravity.h"

void ConstraintGravity::apply() {
    Vector<2> distance = body1.getPosition() - body2.getPosition();
    float length = distance.length();
    float lengthCubedRecip = 1 / (length * length * length);
    // if(length <= minLength) {
    //     length = minLength;
    // }
    Vector<2> acceleration1 = distance * (G * body2.getMass() * lengthCubedRecip);
    Vector<2> acceleration2 = -distance * (G * body1.getMass() * lengthCubedRecip);
    body1.applyAcceleration(acceleration1);
    body2.applyAcceleration(acceleration2);
}
