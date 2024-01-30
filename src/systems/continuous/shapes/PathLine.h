#ifndef PathLine_h
#define PathLine_h

#include "PathBase.h"

template <int N>
class PathLine : public PathBase<N> {
    public:
        PathLine(Vector<N> start, Vector<N> end) {
            this->totalTime = 1;
            this->start = start;
            this->end = end;
        }

        float process(float dt);

    protected:
        Vector<N> start;
        Vector<N> end;
        
};

template <int N>
float PathLine<N>::process(float dt) {
    Vector<N> delta = (end - start) * this->time;
    this->pos = start + delta;
    return this->incrementTime(dt);
}

#endif