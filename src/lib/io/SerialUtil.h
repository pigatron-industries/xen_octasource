#ifndef SerialUtil_h
#define SerialUtil_h

#include <Arduino.h>

inline byte getByte() {
    while(!Serial2.available()){}
    return Serial2.read();
}

inline void writeFloat(HardwareSerial& serial, float floatData) {
    union {
        byte asBytes[4];
        float asFloat;
    } data;
    data.asFloat = floatData;
    serial.write(data.asBytes[0]);
    serial.write(data.asBytes[1]);
    serial.write(data.asBytes[2]);
    serial.write(data.asBytes[3]);
}

inline float readFloat(HardwareSerial& serial) {
    union {
        byte asBytes[4];
        float asFloat;
    } data;
    data.asBytes[0] = getByte();
    data.asBytes[1] = getByte();
    data.asBytes[2] = getByte();
    data.asBytes[3] = getByte();
    return data.asFloat;
}

#endif
