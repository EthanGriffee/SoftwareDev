#pragma once

#include "array.h"
#include "deserialize.h"
#include "deserialize_string.h"

/**
 * class to deserialize arrays
 **/
class DoubleObjDeserializer : public Deserialize {
    public: 
        /**
         * returns the Array* interpreted from the char*.
         * */
        virtual DoubleObj* deserialize(char* s) {
            Sys sys;
            int x = 13;
            int y;
            Array* returning = new Array();
            assert(strcmp(sys.substring(s, 0, x), "{DoubleObj|d=") == 0);
            y = sys.parseUntilSeperator(s, x);
            char* c = sys.substring(s, x, y);
            return new DoubleObj(atof(c));
        }

};