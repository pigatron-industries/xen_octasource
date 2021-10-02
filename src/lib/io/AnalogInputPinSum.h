#ifndef CompoundAnalogInputPin_h
#define CompoundAnalogInputPin_h

class NativeDevice;

template<class T = NativeDevice>
class AnalogInputPinSum : public AnalogInputPin<T> {
    public:
        AnalogInputPinSum(AnalogInputPin<T>& pin1, AnalogInputPin<T>& pin2) : 
            pin1(pin1), pin2(pin2) {

        }

        inline float analogRead() {
            return pin1.analogRead() + pin2.analogRead();
        }
    
        AnalogInputPin<T>& pin1;
        AnalogInputPin<T>& pin2;
};

#endif
