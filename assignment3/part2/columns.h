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
         * Returns an empty string.
         */
        virtual String* colType() { }

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
         * Returns "Int".
         */
        virtual String* colType() { }
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
         * returns "String".
         */
        virtual String* colType() { }

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
         * returns "Boolean".
         */
        virtual String* colType() { }

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
         * returns "Float".
         */
        virtual String* colType() { }

};