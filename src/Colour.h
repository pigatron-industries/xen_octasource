#ifndef Colour_h
#define Colour_h

class Colour {
    public:
        Colour(float red, float green, float blue) {
            this->red = red;
            this->blue = blue;
            this->green = green;
        }

        float red;
        float green;
        float blue;
};

#endif
