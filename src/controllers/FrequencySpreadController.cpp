#include "FrequencySpreadController.h"

void FrequencySpreadController::init(float sampleRate) {
    Controller::init(sampleRate);
    for(int i = 0; i < OUTPUT_CV_COUNT-1; i++) {
        oscillators[i].init(sampleRate);
        oscillators[i].setFrequency(1);
    }
    init();
}

void FrequencySpreadController::init() {
    Serial.println("Freq Spread");
    Hardware::hw.display.textLine("FREQ SPREAD");
    for(int i = 0; i < OUTPUT_CV_COUNT-1; i++) {
        oscillators[i].setPhase(random(0, 999)/1000.0);
    }
    setRate(rateCvInput.getValue(), spreadCvInput.getValue());
}

void FrequencySpreadController::update() {
    updateRate();
    updateAmp();
    updateWave();
    Hardware::hw.updateOutputLeds();
}

void FrequencySpreadController::updateRate() {
    if(rateCvInput.update() | spreadCvInput.update()) {
        float frequency = rateCvInput.getValue();
        float spread = spreadCvInput.getValue();
        setRate(frequency, spread);
    }
}

void FrequencySpreadController::setRate(float baseFrequency, float spread) {
    oscillators[0].setFrequency(baseFrequency);

    // oscillators[1].setFrequency(baseFrequency * (1 + 0.01991221*spread));
    // oscillators[2].setFrequency(baseFrequency * (1 + 0.06216538*spread));
    // oscillators[3].setFrequency(baseFrequency * (1 + 0.10745242*spread));
    // oscillators[4].setFrequency(baseFrequency * (1 - 0.01952356*spread));
    // oscillators[5].setFrequency(baseFrequency * (1 - 0.06288439*spread));
    // oscillators[6].setFrequency(baseFrequency * (1 - 0.10745242*spread));

    oscillators[1].setFrequency(baseFrequency * powf(2, 1*0.04*spread));
    oscillators[2].setFrequency(baseFrequency * powf(2, 3*0.04*spread));
    oscillators[3].setFrequency(baseFrequency * powf(2, 5*0.04*spread));
    oscillators[4].setFrequency(baseFrequency * powf(2, -1*0.04*spread));
    oscillators[5].setFrequency(baseFrequency * powf(2, -3*0.04*spread));
    oscillators[6].setFrequency(baseFrequency * powf(2, -5*0.04*spread));

    // oscillators[1].setFrequency(baseFrequency * powf(2, 1*spread));
    // oscillators[2].setFrequency(baseFrequency * powf(2, 2*spread));
    // oscillators[3].setFrequency(baseFrequency * powf(2, 3*spread));
    // oscillators[4].setFrequency(baseFrequency * powf(2, -1*spread));
    // oscillators[5].setFrequency(baseFrequency * powf(2, -2*spread));
    // oscillators[6].setFrequency(baseFrequency * powf(2, -3*spread));
}

void FrequencySpreadController::updateAmp() {
    if(ampCvInput.update()) {
        ampValue = ampCvInput.getValue();
    }
}

void FrequencySpreadController::updateWave() {
    if(waveCvInput.update()) {
        float waveValue = waveCvInput.getValue();
        for(int i = 0; i < OUTPUT_CV_COUNT-1; i++) {
            if(waveValue < 1) {
                waveSelector.select(0);
            } else if (waveValue < 2) {
                waveSelector.select(1);
            } else if (waveValue < 3) {
                waveSelector.select(2);
            } else {
                waveSelector.select(3);
            }
        }
        Hardware::hw.display.drawWaveShape(&waveSelector, 0, 17, 32, 16, 2);
    }
}



void FrequencySpreadController::process() {

    Hardware::hw.cvOutputPins[0]->analogWrite(oscillators[0].process() * ampValue);
    Hardware::hw.cvOutputPins[1]->analogWrite(oscillators[1].process() * ampValue);
    Hardware::hw.cvOutputPins[2]->analogWrite(oscillators[2].process() * ampValue);
    Hardware::hw.cvOutputPins[3]->analogWrite(oscillators[3].process() * ampValue);
    Hardware::hw.cvOutputPins[7]->analogWrite(oscillators[4].process() * ampValue);
    Hardware::hw.cvOutputPins[6]->analogWrite(oscillators[5].process() * ampValue);
    Hardware::hw.cvOutputPins[5]->analogWrite(oscillators[6].process() * ampValue);

    float sum = Hardware::hw.cvOutputPins[0]->getAnalogValue() + 
                Hardware::hw.cvOutputPins[1]->getAnalogValue() +
                Hardware::hw.cvOutputPins[2]->getAnalogValue() +
                Hardware::hw.cvOutputPins[3]->getAnalogValue() +
                Hardware::hw.cvOutputPins[7]->getAnalogValue() +
                Hardware::hw.cvOutputPins[6]->getAnalogValue() +
                Hardware::hw.cvOutputPins[5]->getAnalogValue();

    Hardware::hw.cvOutputPins[4]->analogWrite(sum*0.5);
}
