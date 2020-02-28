#pragma once

#include "deserialize.h"
#include "deserialize_array.h"
#include "array.h"

/**
 * class to deserialize string arrays
 **/
class StringArrayDeserializer : public Deserialize {
    public:

        /**
         * returns the Array* reinterperated as this.
         * */
        virtual StringArray* deserialize(char* s) {
            Sys sys;
            int x = 21;
            assert(strcmp(sys.substring(s, 0, x), "{StringArray|str_arr=") == 0);
            int y = sys.parseUntilClassSeperator(s, x);
            char* c = sys.substring(s, x, y);
            ArrayDeserializer ad;
            return new StringArray(ad.deserialize(c));
        }

};