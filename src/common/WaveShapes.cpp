#include "WaveShapes.h"

Sine WaveShapes::sine;
Triangle WaveShapes::triangle;
Saw WaveShapes::saw;
Pulse WaveShapes::pulse;

WaveShape* WaveShapes::waveShapes[4] = {&sine, &triangle, &saw, &pulse};
