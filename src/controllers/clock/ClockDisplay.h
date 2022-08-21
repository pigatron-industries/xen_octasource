#ifndef ClockDisplay_h
#define ClockDisplay_h

#include <eurorack_graphics.h>
#include "Hardware.h"

class ClockDisplay {
    public:
        ClockDisplay() {}
        void init();
        void render();

        void focusClock(uint8_t output);
        void setClock(uint8_t output, bool divide, uint8_t value);

    private:
        FocusManager<OLEDDisplay> focusManager;

        VerticalContainer<OLEDDisplay, 3> page;
        TextComponent<OLEDDisplay> title = TextComponent<OLEDDisplay>(OLEDDisplay::WIDTH, "TEST", 2);

        HorizontalContainer<OLEDDisplay, 4> clockRow1;
        HorizontalContainer<OLEDDisplay, 4> clockRow2;
        FieldComponent<OLEDDisplay> clockFields[8] = {
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, ""),
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, ""),
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, ""),
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, ""),
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, ""),
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, ""),
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, ""),
            FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH/4, 0, "")
        };
};

#endif
