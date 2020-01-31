#pragma once

#include <stdlib.h>

class Object {
    public:
        size_t  hash_;

        Object() { 
        }

        // returns true if it refers to the same memory address
        virtual bool equals(Object *other){
            return this == other;
        }

        // returns a hash of the object
        virtual size_t hash() {
            return reinterpret_cast<size_t>(this);
        }

        virtual ~Object() {

        }
};


// Wrapper for a Float
class FloatObj : public Object {
    public:
        float f;

        // sets the value of f to input_f
        FloatObj(float input_f) {
            f = input_f;

        }

        // returns if other is a float that has the same f
        bool equals(Object *other) {
            float epsilon = .0001;
            FloatObj * f2 = dynamic_cast<FloatObj*> (other);
            if (f2 && (f2->getFloat() - f < epsilon)  && (f2->getFloat() - f > -epsilon)){
                return true;
            }
            return false;
        }

        // returns f
        float getFloat() {
            return f;
        }
};

// Wrapper for a Boolean
class BoolObj : public Object {
    public:
        bool b;

        // sets the value of b to input_b
        BoolObj(bool input_b) {
            b = input_b;
        }

        // returns if other is a boolean that has the same b
        bool equals(Object *other){
            BoolObj * b2 = dynamic_cast<BoolObj*> (other);
            if (b2 && b2->getBool() == b ){
                return true;
            }
            return false;
        }

        // returns b
        bool getBool() {
            return b;
        }
};

// Wrapper for a Integer
class IntObj : public Object{
    public:
        int i;

        // sets the value of i to input_i
        IntObj(int input_i) {
            i = input_i;
        }

        // returns if other is a integer that has the same i
        bool equals(Object *other){
            IntObj * i2 = dynamic_cast<IntObj*> (other);
            if (i2 && i2->getInt() == i ){
                return true;
            }
            return false;
            
        }

        // returns i
        int getInt() {
            return i;
        }
};
