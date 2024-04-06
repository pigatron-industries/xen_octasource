#include "FourierCircleController.h"

void FourierCircleController::init(float sampleRate) {
    Controller::init(sampleRate);
    ClockedController::init(sampleRate);
    init();
}


float randomf(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

template<int N>
Array<float, N> randomDivisions(float total) {
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



void FourierCircleController::init() {
    Serial.println("Fourier");
    Hardware::hw.display.textLine("FOURIER");
    fourierCircles.init(sampleRate, NUM_CIRCLES);

    Array<float, NUM_CIRCLES> lengths = randomDivisions<NUM_CIRCLES>(4);
    for (int i = 0; i < NUM_CIRCLES; i++) {
        fourierCircles.setCircleRadiusFrequency(i, lengths[i], randomf(0.25, 4));
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
    // if(largeRadiusInput.update() | smallRadiusInput.update()) {
    //     fourierCircles.setRadiusLargeSmall(largeRadiusInput.getValue(), smallRadiusInput.getValue());
    // }
    
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

        CircleState& lastCircle = output[fourierCircles.getNumCircles()-1];
        Hardware::hw.cvOutputPins[0]->analogWrite(lastCircle.pos[X]);
        Hardware::hw.cvOutputPins[1]->analogWrite(lastCircle.pos[Y]);
        Hardware::hw.cvOutputPins[2]->analogWrite(lastCircle.pos.length());
        Hardware::hw.cvOutputPins[3]->analogWrite(angle2d(lastCircle.pos));
        Hardware::hw.cvOutputPins[4]->analogWrite(lastCircle.speed*0.1);
        Hardware::hw.cvOutputPins[5]->analogWrite(0); 

        // Serial.println(lastCircle.speed);

        Hardware::hw.cvOutputPins[6]->analogWrite(output[clockCount].pos[X]);
        Hardware::hw.cvOutputPins[7]->analogWrite(output[clockCount].pos[Y]);
    }
}