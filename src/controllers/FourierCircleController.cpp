#include "FourierCircleController.h"

void FourierCircleController::init(float sampleRate) {
    Controller::init(sampleRate);
    ClockedController::init(sampleRate);
    init();
}


void FourierCircleController::init() {
    Serial.println("Fourier");
    Hardware::hw.display.textLine("FOURIER");
    fourierCircles.init(sampleRate/SAMPLE_RATE_DIVISOR, NUM_CIRCLES);
    randomizeCircles();
}


float randomf(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

template<int N>
Array<float, N> randomDivisions(float total) {
    // Randomly dividion a totla length into N parts in a uniform distribution
    Array<float, N> arr;
    float sum = 0;
    for(int i = 0; i < N; i++) {
        arr[i] = randomf(0, total);
        sum += arr[i];
    }
    float scale = total / sum;
    for(int i = 0; i < N; i++) {
        arr[i] *= scale;
    }
    return arr;
}


void FourierCircleController::randomizeCircles() {
    Array<float, NUM_CIRCLES> lengths = randomDivisions<NUM_CIRCLES>(MAX_OUTPUT);
    for (int i = 0; i < NUM_CIRCLES; i++) {
        fourierCircles.setCircleRadiusFrequency(i, lengths[i], randomf(MIN_CIRCLE_FREQEUENCY, MAX_CIRCLE_FREQUENCY));
    }

    updateParams();
}


void FourierCircleController::update() {
    clock.setFrequency(200);
    updateRate();
    updateParams();
    Hardware::hw.updateOutputLeds();
}

void FourierCircleController::updateRate() {
    if(expRateCvInput.update()) {
        float rateValue = expRateCvInput.getValue();
        fourierCircles.setFrequency(rateValue);
    }
}

void FourierCircleController::updateParams() {
    if(ampInput.update()) {
        ampValue = ampInput.getValue();
    }
    
    // if(pointRadiusInput.update()) {
    //     float pointRadius = pointRadiusInput.getValue();
    //     fourierCircles.setRadiusPoint(pointRadius);
    // }
}


void FourierCircleController::onClock() {
    clockCount = (clockCount + 1) % NUM_CIRCLES;
}

void FourierCircleController::process() {
    ClockedController::process();
    if(clockDivider.tick()) {
        fourierCircles.process();
        Array<CircleState, MAX_CIRCLES>& output = fourierCircles.getState();

        CircleState& circle1 = output[fourierCircles.getNumCircles()-1];
        CircleState& circle2 = output[fourierCircles.getNumCircles()-2];
        CircleState& circle3 = output[fourierCircles.getNumCircles()-3];

        Hardware::hw.cvOutputPins[0]->analogWrite(circle1.pos.length()*ampValue);
        Hardware::hw.cvOutputPins[1]->analogWrite(circle2.pos.length()*ampValue);
        Hardware::hw.cvOutputPins[2]->analogWrite(circle3.pos.length()*ampValue); 
        Hardware::hw.cvOutputPins[3]->analogWrite(angle2d(circle1.pos)*ampValue);
        Hardware::hw.cvOutputPins[4]->analogWrite(circle1.speed*0.05*ampValue);
        Hardware::hw.cvOutputPins[5]->analogWrite(circle2.speed*0.05*ampValue); 

        Hardware::hw.cvOutputPins[6]->analogWrite(output[clockCount].pos[X]*ampValue);
        Hardware::hw.cvOutputPins[7]->analogWrite(output[clockCount].pos[Y]*ampValue);
    }
}