#include "ShapeRenderer.h"


void ShapeRenderer::addShape(PathBase<2>* shape) {
    shapes.add(shape);
}

void ShapeRenderer::process() {
    PathBase<2>* currentshape = shapes.get(currentShapeIndex);
    float overtime = currentshape->process(dt);
    pos = currentshape->getPos();

    if(overtime > 0) {
        incrementShape(overtime);
    }
}

void ShapeRenderer::incrementShape(float overtime) {
    currentShapeIndex++;
    if(currentShapeIndex >= shapes.size()) {
        currentShapeIndex = 0;
    } 
    
    PathBase<2>* nextShape = shapes.get(currentShapeIndex);
    nextShape->setTime(overtime);
}
