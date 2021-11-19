#ifndef ThreeBody_h
#define ThreeBody_h

#include "../ContinuousSystem.h"
#include <eurorack.h>

#define BODIES 3
#define G 1

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
            WRAP,
            ANTIGRAV
        };

        void init(float sampleRate);
        void setBodies(const Array<Body, BODIES>& bodies);
        void setParam(int param, float value);
        void setLimit(float limit) { this->limit = limit; };
        void setDriftCorrection(bool driftCorrection) { this->driftCorrection = driftCorrection; };
        void setEdgeMode(EdgeMode edgeMode) { this->edgeMode = edgeMode; };

        Array<Body, BODIES>& getBodies() { return bodies; }

        void process();

        Vector<2> calculateMomentum() { return calculateMomentum(bodies); }

        static Array<Body, BODIES> initEqualInlineSystem(int mult, Vector<2> velocity);

    private:
        Array<Body, BODIES> bodies;
        float limit = 5;
        float damp = 0.25;
        float minDist = 0.01;
        bool driftCorrection;
        EdgeMode edgeMode;

        void calculateAcceleration(int i);
        Vector<2> calculateCentreOfMass(const Array<Body, BODIES>& bodies);
        Vector<2> calculateMomentum(const Array<Body, BODIES>& bodies);
        void limitBodies();
        void doDriftCorrection();
        void applyAntiGrav(int body);
        void applyAntiGrav(int body, int dimension, int direction);
        void setOutputs();
    
};

#endif
