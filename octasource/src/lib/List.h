#ifndef List_h
#define List_h

#include <inttypes.h>
#include <cstring>

#define LIST_MAX_LENGTH 16

class List {

public:
    int8_t length;
    int8_t data[LIST_MAX_LENGTH];

    List() {
        length = 0;
    }

    void append(int8_t item) {
        if (length < LIST_MAX_LENGTH) {
            data[length++] = item;
        }
    }

    void remove(int8_t index) {
        if (index >= length) {
            return;
        }

        memmove(&data[index], &data[index+1], length - index - 1);
        length--;
    }

    uint8_t get(int8_t index) {
        return data[index];
    }

    int8_t find(int8_t item) {
        for(uint8_t i = 0; i < length; i++) {
            if(data[i] == item) {
                return i;
            }
        }

        return -1;
    }

};

#endif
