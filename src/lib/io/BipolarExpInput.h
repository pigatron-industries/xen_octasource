#ifndef BipolarExpInput_h
#define BipolarExpInput_h

#include <eurorack.h>

#define RATE_EXP_START_FREQ 0.1
#define RATE_EXP_MULT 4

/**
 * Has a linear response from -1 to 1 volts, exponential response outside of this range in both positive and negative directions.
 * Not 1V/oct
 */
template<class T = NativeDevice>
class BipolarExpInput : public AbstractInput<T> {
    public:
        BipolarExpInput(AnalogInputPin<T>& input) : 
            AbstractInput<T>(input) {}

        float getValue() { 
            float voltage = this->getStableVoltage();
            if(voltage <= 1 && voltage >= -1) {
                return RATE_EXP_START_FREQ * voltage;
            } else if(voltage > 1) {
                return RATE_EXP_START_FREQ * pow(RATE_EXP_MULT, voltage-1);
            } else {
                return -RATE_EXP_START_FREQ * pow(RATE_EXP_MULT, -1-voltage);
            }
        }
        
};

#endif