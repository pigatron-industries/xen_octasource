#ifndef ThreeBody_h
#define ThreeBody_h

#include "../ContinuousSystem.h"
#include "../List.h"

#define BODIES 3

class Body {
    public:
        float mass = 1;
        Vector<2> position = Vector<2>(0, 0);
        Vector<2> velocity = Vector<2>(0, 0);
        Vector<2> acceleration = Vector<2>(0, 0);
};

class ThreeBody : public ContinuousSystemN<6> {
    public:
        void init(float sampleRate);
        void setBodies(const List<Body, BODIES>& bodies);
        List<Body, BODIES>& getBodies() { return bodies; }
        void setParam(int param, float value);
        void setLimit(float limit) { this->limit = limit; };
        void process();

    private:
        List<Body, BODIES> bodies;
        float g = 1;
        float limit = 5;

        void calculateAcceleration(int i);
        Vector<2> calculateCentreOfMass(const List<Body, BODIES>& bodies);
        Vector<2> calculateMomentum(const List<Body, BODIES>& bodies);
        void limitBodies();
        void setOutputs();
    
};

#endif
