#ifndef ThreeBodyDisplay_h
#define ThreeBodyDisplay_h

#include <eurorack_graphics.h>
#include "Hardware.h"

class ThreeBodyDisplay {
    public:
        ThreeBodyDisplay() {}
        void init();
        void render();

        void focusType();
        void focusOutput();
        void setType(char* type);
        void setOutput(char* outputType);

    private:
        FocusManager<OLEDDisplay> focusManager;

        VerticalContainer<OLEDDisplay, 3> page;
        TextComponent<OLEDDisplay> title = TextComponent<OLEDDisplay>(OLEDDisplay::WIDTH, "THREE BODY", 2);
        FieldComponent<OLEDDisplay> typeField = FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH, 0, "");
        FieldComponent<OLEDDisplay> outputField = FieldComponent<OLEDDisplay>(OLEDDisplay::WIDTH, 0, "");

};

#endif
