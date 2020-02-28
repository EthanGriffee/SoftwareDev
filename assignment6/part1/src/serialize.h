#pragma once

#include "object.h"

/**
 * Interface for serializeing and desserializing data
 * */
class Serialize {

    public:

        /**
         * returns a char* representation of the Object.
         * */
        virtual char* serialize() {}

        /**
         * returns the char* reinterperated as this.
         * */
        virtual Object* deserialize(char* s) {}
};