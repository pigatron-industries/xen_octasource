#ifndef Trail_h
#define Trail_h

#include <inttypes.h>
#include <eurorack.h>

class Pixel {
    public:
        Pixel() {}
        Pixel(uint8_t x, uint8_t y) { this->x = x; this->y = y; }
        uint8_t x;
        uint8_t y;
};

template<int N>
class PixelTrail {
    public:
        PixelTrail() {}

        Pixel push(Pixel pixel) {
            Pixel lastPixel = pixels[index];
            pixels[index] = pixel;
            index++;
            if(index >= N) {
                index = 0;
            }
            return lastPixel;
        }

        Pixel getPrev() {
            return pixels[index];
        }

    private:
        Array<Pixel, N> pixels;
        uint8_t index = 0;
};

#endif
