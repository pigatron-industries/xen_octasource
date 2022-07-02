#ifndef ParameterPage_h
#define ParameterPage_h

#include "../Hardware.h"

class ParameterPage {
    public:
        ParameterPage() {}

        void setLabel(int line, const char* text);
        void setValue(int line, int value);
        void selectLine(int line);
        
    protected: 
        int selectedLine = -1;

        int labelStart = 1;
        int valueStart = 6;
        
};


#endif
