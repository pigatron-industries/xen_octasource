#ifndef Shape2D_h
#define Shape2D_h

#include <eurorack.h>

#include "PathBase.h"
#include "PathLine.h"

#define MAX_SEGMENTS 10


class Shape2D : public PathBase<2> {

    public:
        float getTotalTime() { return totalTime; }

        void addSegment(PathBase<2>* segment);

        float process(float dt);

    private:
        Array<PathBase<2>*, MAX_SEGMENTS> pathsegments;
        int currentSegmentIndex = 0;

        float incrementSegment(float overtime);

        //example:
        PathLine<2> path1 = PathLine<2>({ 1,  1}, {-1,  1});
        PathLine<2> path2 = PathLine<2>({-1,  1}, {-1, -1});
        PathLine<2> path3 = PathLine<2>({-1, -1}, { 1, -1});
        PathLine<2> path4 = PathLine<2>({ 1, -1}, { 1,  1});
};

#endif