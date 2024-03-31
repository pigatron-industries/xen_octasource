#ifndef Circles_h
#define Circles_h

#include <eurorack.h>
#include "ParametricSystem.h"
#include "math.h"

#define MAX_CIRCLES 5

class CircleState {
    public:
        CircleState() {}
        CircleState(float radius, float frequency) : radius(radius), frequency(frequency) {}

        float radius = 1;
        float frequency = 1;

        float angleIncrement = 0;
        float angle = 0;

        Vector<2> pos;
};


class FourierCircles : public ParametricSystemN<2> {
    public:
        FourierCircles() {}
        void init(float sampleRate, int numCircles = 5);
        void setFrequency(float frequency) { this->frequency = frequency; calcCoefficients(); }
        void setCircleRadiusFrequency(int index, float radius, float frequency);

        Array<CircleState, MAX_CIRCLES>& getState() { return circles; }

        void process();
        
    
    public:
        Array<CircleState, MAX_CIRCLES> circles;
        float frequency = 1;
    
        void calcCoefficients();
        void calcCoefficients(int index);
        void system();
        void incrementAngles();
};


inline void FourierCircles::init(float sampleRate, int numCircles) {
    ParametricSystemN<2>::init(sampleRate);
    circles.clear();
    float radius = 3;
    float frequency = 1;
    for(int i = 0; i < numCircles; i++) {
        circles.add(CircleState(radius, frequency));
        radius *= 0.5;
        frequency *= 2;
    }
    calcCoefficients();
}


inline void FourierCircles::setCircleRadiusFrequency(int index, float radius, float frequency) {
    circles[index].radius = radius;
    circles[index].frequency = frequency;
    calcCoefficients(index);
}


inline void FourierCircles::process() {
    system();
}


inline void FourierCircles::calcCoefficients() {
    for (int i = 0; i < circles.size(); i++) {
        calcCoefficients(i);
    }
}


inline void FourierCircles::calcCoefficients(int index) {
    CircleState& circle = circles[index];
    circle.angleIncrement = sampleTime * frequency * circle.frequency * 2 * M_PI;
}


inline void FourierCircles::system() {
    Vector<2> centre = {0, 0};
    for (int i = 0; i < circles.size(); i++) {
        CircleState& circle = circles[i];
        circle.pos[X] = centre[X] + circle.radius * cosf(circle.angle);
        circle.pos[Y] = centre[Y] + circle.radius * sinf(circle.angle);
        circle.angle += circle.angleIncrement;
        if (circle.angle > 2 * M_PI) {
            circle.angle -= 2 * M_PI;
        }
        centre = circle.pos;
    }
}


#endif