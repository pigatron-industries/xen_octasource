#ifndef GateInput_h
#define GateInput_h

#include <inttypes.h>

#define GATE_VOLTAGE 3


class GateInput {

public:
    GateInput();
    bool update(float value);
    bool risingEdge();
    bool fallingEdge();

private:
    float _prevValue = 0;
    bool _risingEdge = false;
    bool _fallingEdge = false;

};

#endif
