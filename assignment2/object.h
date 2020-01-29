#pragma once

#include <stdlib.h>

class Object {
    public:
        size_t  hash_;

        Object() { 
        }

        // returns true if it refers to the same memory address
        bool equals(Object *other){
            return this == other;
        }

        // returns a hash of the object
        size_t hash() {
            return reinterpret_cast<size_t>(this);
        }

        virtual ~Object() {

        }
};