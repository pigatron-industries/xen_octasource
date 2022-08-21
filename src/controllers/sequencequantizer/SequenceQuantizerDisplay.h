#ifndef SequenceQuantizerDisplay_h
#define SequenceQuantizerDisplay_h

#include <eurorack_graphics.h>
#include "Hardware.h"

class SequenceQuantizerDisplay {
    public:
        SequenceQuantizerDisplay() {}
        void init();
        void render();

        void setLength(uint8_t length);

    private:
        FocusManager<OLEDDisplay> focusManager;

        VerticalContainer<OLEDDisplay, 2> page;
        TextComponent<OLEDDisplay> title = TextComponent<OLEDDisplay>(OLEDDisplay::WIDTH, "SEQUANTIZER", 2);
        FieldComponent<OLEDDisplay> lengthField = FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH, 40, "LENGTH:");
};

#endif
