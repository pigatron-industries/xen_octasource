#ifndef InterpolationUtil_h
#define InterpolationUtil_h

#include <eurorack.h>

inline float interpolate(float a, float b, float interpolation) {
    return a + (b - a) * interpolation;
}


template<int N>
class ArrayInterpolator {
    public:
        ArrayInterpolator() {}
        void init(std::initializer_list<float> list1, std::initializer_list<float> list2);
        Array<float, N>& interpolate(float interpolation);

    protected:
        Array<float, N> values1;
        Array<float, N> values2;
        Array<float, N> interpolated;

};


template<int N>
void ArrayInterpolator<N>::init(std::initializer_list<float> list1, std::initializer_list<float> list2) {
    values1.clear();
    for(auto& item : list1) {
        values1.add(item);
    }
    values2.clear();
    for(auto& item : list2) {
        values2.add(item);
    }
}


template<int N>
Array<float, N>& ArrayInterpolator<N>::interpolate(float interpolation) {
    for(int i = 0; i < N; i++) {
        interpolated[i] = ::interpolate(values1[i], values2[i], interpolation);
    }
    return interpolated;
}

#endif