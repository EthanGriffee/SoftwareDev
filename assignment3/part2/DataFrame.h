#pragma once

#include "object.h"
#include "string.h"
#include "helper.h"
#include "columns.h"
#include <cstdarg>


/**
 * A Data Frame is a collection of columns with names rows
 */
class DataFrame : public Object {
    
    public:
        /**
         * Creates a dataframe with a length of the shortest column.
         * The columns entered are now owned by this.
         */
        DataFrame(Column*...) {

        }

        /**
         * Deletes all columns and names in this.
         */
        ~DataFrame() {

        }

        /**
         * Names the row indicated by i, name. If i > the length, exits with
         * code 1. The String entered is now owned by this.
         */
        void addRowName(String* name, size_t i) {

        }

        /**
         * Prints the DataFrame by printing a blank space, followed by the 
         * names of all columns, then on a new line for each row, the row name is 
         * printed followed by the contents of the row. 
         */
        void print() {

        }

        /**
         * Returns the data specified by row, col
         * If the index is out of bounds, exits with
         * error code 1.
         */
        Data get(size_t row, size_t col) {

        }

        /**
         * Returns the data matching the row_name and col_name
         * If there is no row_name or col_name matching the ones
         * specified, exits with error code 1
         */
        Data get(String* row_name, String* col_name) {

        }

        /**
         * Returns the float specified by row, col. If the index is out of bounds 
         * or the column specified is not a FloatColumn, exits with
         * error code 1.
         */
        float getFloat(size_t row, size_t col) {

        }

        /**
         * Returns the data matching the row_name and col_name
         * If there is no row_name or col_name matching the ones
         * specified or the column specified is not a FloatColumn, 
         * exits with error code 1
         */
        float getFloat(String* row_name, String* col_name) {

        }

        /**
         * Returns the bool specified by row, col. If the index is out of bounds 
         * or the column specified is not a BooleanColumn, exits with
         * error code 1.
         */
        bool getBoolean(size_t row, size_t col) {

        }

        /**
         * Returns the bool matching the row_name and col_name
         * If there is no row_name or col_name matching the ones
         * specified or the column specified is not a BooleanColumn, 
         * exits with error code 1
         */
        bool getBoolean(String* row_name, String* col_name) {

        }

        /**
         * Returns the string specified by row, col. If the index is out of bounds 
         * or the column specified is not a StringColumn, exits with
         * error code 1.
         */
        String* getString(size_t row, size_t col) {

        }

        /**
         * Returns the string matching the row_name and col_name
         * If there is no row_name or col_name matching the ones
         * specified or the column specified is not a StringColumn, 
         * exits with error code 1
         */
        String* getString(String* row_name, String* col_name) {

        }

        /**
         * Returns the int specified by row, col. If the index is out of bounds 
         * or the column specified is not a IntColumn, exits with
         * error code 1.
         */
        int getInt(size_t row, size_t col) {

        }

        /**
         * Returns the int matching the row_name and col_name
         * If there is no row_name or col_name matching the ones
         * specified or the column specified is not a IntColumn, 
         * exits with error code 1
         */
        int getInt(String* row_name, String* col_name) {

        }

        /**
         * Returns the number of rows in the DataFrame
         */
        size_t nrow() {

        }

        /**
         * Returns the number of columns in the DataFrame
         */
        size_t ncol() {

        }

        /**
         * Returns if other is a dataframe with the same columns, and row names 
         * as this
         */
        bool equals(Object* other) {

        }

        /**
         * Returns the column type at index i or exits with error code 1 if i > 
         * the number of columns
         */
        String* getColType(size_t i) {

        }

        /**
         * Returns the column type of the column with the name given, or exits
         * with error code 1 if no column has that name. 
         */
        String* getColType(String* name) {
            
        }

        /**
         * Returns a new dataframe that has rows that are equal in both this 
         * and other
         */
        DataFrame* dataUnion(DataFrame* other) { 

        }

        /**
         * Adds col to the dataframe
         */
        void addCol(Column* col) {
            
        }


};