#ifndef List_h
#define List_h

#include <stdarg.h>

template<class T, int N>
class List {
    public:
        List() {}

        T& operator[](int i) { return items[i]; }
        const T& operator[](int i) const { return items[i]; }

        T items[N];
};

#endif