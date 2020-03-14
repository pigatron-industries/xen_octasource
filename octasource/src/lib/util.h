#ifndef util_h
#define util_h

// getsize of array at compile time
template<size_t SIZE, class T> inline size_t array_size(T (&arr)[SIZE]) {
    return SIZE;
}

#endif
