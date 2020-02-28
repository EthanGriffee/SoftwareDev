#pragma once

#include "deserialize.h"
#include "deserialize_array.h"
#include "array.h"

/**
 * class to deserialize string arrays
 **/
class DoubleArrayDeserializer : public Deserialize {
    public:

        /**
         * returns the Array* reinterperated as this.
         * */
        virtual DoubleArray* deserialize(char* s) {
            Sys sys;
            int x = 24;
            assert(strcmp(sys.substring(s, 0, x), "{DoubleArray|double_arr=") == 0);
            int y = sys.parseUntilClassSeperator(s, x);
            char* c = sys.substring(s, x, y);
            ArrayDeserializer ad;
            return new DoubleArray(ad.deserialize(c));
        }

};