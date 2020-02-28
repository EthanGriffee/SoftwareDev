#pragma once
#include "object.h"


/**
 * Interface for serializeing and desserializing data
 * */
class Deserialize {

    public:

        /**
         * returns the char* reinterperated as this.
         * */
        virtual Object* deserialize(char* s) {}
};