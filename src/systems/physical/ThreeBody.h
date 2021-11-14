#ifndef ThreeBody_h
#define ThreeBody_h

#include "../ContinuousSystem.h"
#include <eurorack.h>

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

        enum EdgeMode {
            NONE,
            BOUNCE,
            WRAP
        };

        void init(float sampleRate);
        void setBodies(const Array<Body, BODIES>& bodies);
        void setParam(int param, float value);
        void setLimit(float limit) { this->limit = limit; };
        void setDriftCorrection(bool driftCorrection) { this->driftCorrection = driftCorrection; };
        void setEdgeMode(EdgeMode edgeMode) { this->edgeMode = edgeMode; };

        Array<Body, BODIES>& getBodies() { return bodies; }

        void process();

    private:
        Array<Body, BODIES> bodies;
        float g = 1;
        float limit = 5;
        bool driftCorrection;
        EdgeMode edgeMode;

        void calculateAcceleration(int i);
        Vector<2> calculateCentreOfMass(const Array<Body, BODIES>& bodies);
        Vector<2> calculateMomentum(const Array<Body, BODIES>& bodies);
        void limitBodies();
        void doDriftCorrection();
        void setOutputs();
    
};

#endif
