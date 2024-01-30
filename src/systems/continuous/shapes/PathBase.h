#ifndef PathBase_h
#define PathBase_h

#include "systems/Vector.h"

template<int N>
class PathBase {
    public:
        PathBase() {}
        Vector<N> getPos() { return pos * scale + offset; }

        void setOffset(Vector<N> offset) { this->offset = offset; }
        void setScale(Vector<N> scale) { this->scale = scale; }
        void setTime(float time) { this->time = time; }

        virtual float process(float dt) = 0;

    protected:
        Vector<N> pos = {0, 0};
        Vector<N> offset = {0, 0};
        Vector<N> scale = {1, 1};

        float time = 0;
        float totalTime = 1;

        float incrementTime(float dt) {
            time += dt;
            if(time >= totalTime) {
                float overtime = time - totalTime;
                time = 0;
                return overtime;
            } else {
                return 0;
            }
        }
};

#endif