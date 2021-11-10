#ifndef ThreeBody_h
#define ThreeBody_h

#include "../ContinuousSystem.h"

class Body {
    public:
        Vector<2> position;
        Vector<2> velocity;
        Vector<2> acceleration;
};

class ThreeBody : public ContinuousSystemN<6> {
    public:
        void init(float sampleRate);
        void setParam(int param, float value);
        void process();

    private:
};

#endif
