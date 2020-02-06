#pragma once

#include "object.h"
#include "string.h"
#include <cstdarg>

/**
 * 
 */
class Column : public Object {
    public:

        Column() { }
        /**
         * returns the name of the column, or null if the column is not named
         */
        String* getName() { }

        /**
         * returns the length of the column
         */
        size_t length() { }

        /**
         * sets the name of the column to name
         */
        void setName(String* name) { }
};

class IntColumn : public Column {
    public:

        IntColumn(int...) : Column() { }

        /**
         * returns the int at the specified position, or exits
         * with error code 1 if the i > the column length
         */
        int get(size_t i) { }
};



class StringColumn : public Column {
    public:

        StringColumn(String*...) : Column() { }

        /**
         * returns the String at the specified position, or exits
         * with error code 1 if the i > the column length
         */
        String* get(size_t i) { }

};


class BooleanColumn : public Column {
    public:

        BooleanColumn(bool...) : Column() { }


        /**
         * returns the boolean at the specified position, or exits
         * with error code 1 if the i > the column length
         */
        bool get(size_t i) { }

};

class FloatColumn : public Column {
    public:

        FloatColumn(float...) : Column() { }

        /**
         * returns the float at the specified position, or exits
         * with error code 1 if the i > the column length
         */
        float get(size_t i) { }

};