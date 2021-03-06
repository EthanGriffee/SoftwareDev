#pragma once

#include "array.h"
#include "deserialize.h"
#include "deserialize_string.h"
#include "deserialize_double_obj.h"

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
            Object* adding;
            int y;
            Array* returning = new Array();
            assert(strcmp(sys.substring(s, 0, x), "{Array|array=") == 0);
            while(s[x] == '{') {
                y = sys.parseUntilClassSeperator(s, x);
                char* c = sys.substring(s, x, y);
                 // placeholder as we are only doing this on doubles and string objs
                if (strcmp(sys.substring(s, x, 8), "{String|") == 0) {
                    StringDeserializer sd;
                    adding = sd.deserialize(c);
                }
                else if (strcmp(sys.substring(s, x, 11), "{DoubleObj|") == 0) {
                    DoubleObjDeserializer dod;
                    adding = dod.deserialize(c);
                }
                returning->add(adding);
                x += y;
            }
            return returning;
        }

};