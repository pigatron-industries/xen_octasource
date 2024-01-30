#include "Shape2D.h"


void Shape2D::addSegment(PathBase<2>* segment) {
    pathsegments.add(segment);
}


float Shape2D::process(float dt) {
    PathBase<2>* currentSegment = pathsegments.get(currentSegmentIndex);
    float overtime = currentSegment->process(dt);
    pos = currentSegment->getPos();

    if(overtime > 0) {
        return incrementSegment(overtime);
    } else {
        return 0;
    }
}


float Shape2D::incrementSegment(float overtime) {
    currentSegmentIndex++;
    if(currentSegmentIndex >= pathsegments.size()) {
        currentSegmentIndex = 0;
        return overtime;
    } else {
        PathBase<2>* nextSegment = pathsegments.get(currentSegmentIndex);
        nextSegment->setTime(overtime);
        return 0;
    }
}
