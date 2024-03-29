#include "ConstraintSpring.h"

void ConstraintSpring::apply() {
    Vector<2> distance = body1.getPosition() - body2.getPosition();
    float length = distance.length();
    Vector<2> direction = distance/length;
    float stretch = restLength - length;
    //if(stretch < 0) { //string
        Vector<2> force = direction * stretch * stiffness;
        body1.applyAcceleration(force * body1.getMassRecip());
        body2.applyAcceleration(-force * body2.getMassRecip());
    //}
}
