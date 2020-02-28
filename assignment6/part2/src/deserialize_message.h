#pragma once

#include "serial.h"
#include "message.h"
#include "string.h"
#include "deserialize.h"


/**
 * class to deserialize messages
 **/
class MessageDeserializer : public Deserialize {
    public:

        /**
         * returns the Message* reinterperated as this.
         * */
        virtual Message* deserialize(char* s) {
            Sys sys;
            int x = 15;
            if(strcmp(sys.substring(s, 0, x), "{MESSAGE|kind_=") == 0) {
                int y = sys.parseUntilSeperator(s, x);
                char* c = sys.substring(s, x, y);
                if(strcmp(c, "Ack") == 0) {
                    return new Ack(s);
                }
                else if(strcmp(c, "Status") == 0) {
                    return new Status(s);
                }
                else if(strcmp(c, "Register") == 0) {
                    return new Register(s);
                }
                else if(strcmp(c, "Dir") == 0) {
                    return new Dir(s);
                }
            }
        }

};