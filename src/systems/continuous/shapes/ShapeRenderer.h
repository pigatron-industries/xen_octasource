#ifndef ShapeRenderer_h
#define ShapeRenderer_h

#include "../ContinuousSystem.h"
#include "Shape2D.h"
#include "PathBase.h"

#define MAX_SHAPES 10

class ShapeRenderer : public ContinuousSystemN<2> {
    public:
        void addShape(PathBase<2>* shape);
        void process();

    protected:
        Array<PathBase<2>*, MAX_SHAPES> shapes;
        int currentShapeIndex = 0;

        void incrementShape(float overtime);
};

#endif