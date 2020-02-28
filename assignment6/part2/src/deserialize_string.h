#pragma once

#include "string.h"
#include "deserialize.h"


/**
 * class to deserialize strings
 **/
class StringDeserializer : public Deserialize {
    public:
        
        /**
         * returns the String* interpreted from the char*.
         * */
        virtual String* deserialize(char* s) {
            Sys sys;
            int x = 14;
            assert(strcmp(sys.substring(s, 0, x), "{String|cstr_=") == 0);
            int y = sys.parseUntilSeperator(s, x);
            return new String(sys.substring(s, x, y));
        }
};