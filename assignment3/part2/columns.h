#pragma once

#include "object.h"
#include "string.h"
#include <cstdarg>

union Data {
   int i;
   float f;
   bool b;
   String* s;
}; 

enum types {
    STRING,
    BOOLEAN,
    FLOAT,
    INT,
    BASIC
};


/**
 * A Column is an Object that is meant to store data in a specific order.
 * A Column has a name that can be changed.
 */
class Column : public Object {
    public:
        /**
         * Creates a column.
         */
        Column() { }

        /**
         * If there is a name associated with this column, deletes it.
         */
        ~Column() { }

        /**
         * Returns a new string with the name of the column, or null if the 
         * column is not named.
         */
        String* getName() { }

        /**
         * Returns the length of the column.
         */
        size_t length() { }

        /**
         * Sets the name of the column to name.
         */
        void setName(String* name) { }

        /**
         * Determines if other is a column and it has the same name as this.
         */
        virtual bool equals(Object* other) { }

        /**
         * Returns BASIC.
         */
        virtual types colType() { }

        /**
         * Returns an error as a non-typed column has no data
         */
        virtual Data get() { }
};

/**
 * An int column is a column that holds ints.
 */
class IntColumn : public Column {
    public:

        /**
         * Creates an IntColumn with the ints specified.
         */
        IntColumn(int...) : Column() { }


        ~IntColumn() { }

        /**
         * Returns the int at the specified position, or exits
         * with error code 1 if the i > the column length.
         */
        int get(size_t i) { }

        /**
         * Determines if other is a IntColumn and it has the same name and ints in
         * the same order as this.
         */
        virtual bool equals(Object* other) { }

        /**
         * Returns INT.
         */
        virtual types colType() { }

        /**
         * Adds i to the bottom of the column.
         */
        void push(int i);

};


/**
 * A StringColumn is a Column that holds Strings.
 */
class StringColumn : public Column {
    public:

        /**
         * Creates a StringColumn with the Strings specified.
         */
        StringColumn(String*...) : Column() { }

        /**
         * Does not delete strings in this column
         */
        ~StringColumn() { }

        /**
         * returns the String at the specified position, or exits
         * with error code 1 if the i > the column length.
         */
        String* get(size_t i) { }

        /**
         * determines if other is a StringColumn and it has the same name and 
         * Strings in the same order as this.
         */
        virtual bool equals(Object* other) { }

        /**
         * returns STRING.
         */
        virtual types colType() { }

        /**
         * Adds s to the bottom of the column.
         */
        void push(String* s);

};

/**
 * A BooleanColumn is a Column that holds booleans.
 */
class BooleanColumn : public Column {
    public:

        /**
         * Creates a BooleanColumn with the booleans specified.
         */
        BooleanColumn(bool...) : Column() { }

        ~BooleanColumn() { }


        /**
         * returns the boolean at the specified position, or exits
         * with error code 1 if the i > the column length.
         */
        bool get(size_t i) { }

        /**
         * determines if other is a BooleanColumn and it has the same name and 
         * booleans in the same order as this.
         */
        virtual bool equals(Object* other) { }

        /**
         * returns BOOLEAN.
         */
        virtual types colType() { }

        /**
         * Adds b to the bottom of the column.
         */
        void push(bool b);

};

/**
 * A FloatColumn is a Column that holds Floats.
 */
class FloatColumn : public Column {
    public:
        /**
         * Creates a FloatColumn with the floats specified.
         */
        FloatColumn(float...) : Column() { }

        ~FloatColumn() {}

        /**
         * returns the float at the specified position, or exits
         * with error code 1 if the i > the column length.
         */
        float get(size_t i) { }

        /**
         * determines if other is a FloatColumn and it has the same name and 
         * floats in the same order as this.
         */
        virtual bool equals(Object* other) { }

        /**
         * returns FLOAT.
         */
        virtual types colType() { }

        /**
         * Adds f to the bottom of the column.
         */
        void push(float f);

};