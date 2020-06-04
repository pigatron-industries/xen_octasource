#include "GateInput.h"


GateInput::GateInput() {
}

bool GateInput::update(float value) {
    if(value >= GATE_VOLTAGE && _prevValue < GATE_VOLTAGE) {
        _risingEdge = true;
        _fallingEdge = false;
        _prevValue = value;
        return true;
    } else if(value < GATE_VOLTAGE && _prevValue > GATE_VOLTAGE) {
        _risingEdge = false;
        _fallingEdge = true;
        _prevValue = value;
        return true;
    } else {
        _risingEdge = false;
        _fallingEdge = false;
        _prevValue = value;
        return false;
    }
}

bool GateInput::risingEdge() {
    return _risingEdge;
}

bool GateInput::fallingEdge() {
    return _fallingEdge;
}
