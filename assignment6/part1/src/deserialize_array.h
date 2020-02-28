#pragma once

#include "array.h"
#include "deserialize.h"
#include "deserialize_string.h"

/**
 * class to deserialize arrays
 **/
class ArrayDeserializer : public Deserialize {
    public: 
        /**
         * returns the Array* interpreted from the char*.
         * */
        virtual Array* deserialize(char* s) {
            Sys sys;
            int x = 13;
            int y;
            Array* returning = new Array();
            assert(strcmp(sys.substring(s, 0, x), "{Array|array=") == 0);
            while(s[x] == '{') {
                y = sys.parseUntilClassSeperator(s, x);
                char* c = sys.substring(s, x, y);
                StringDeserializer sd;
                // placeholder as we are only doing this on string arrays
                returning->add(sd.deserialize(c));
                x += y;
            }
            return returning;
        }

};