#pragma once

#include "object.h"
#include "string.h"
#include "helper.h"
#include "columns.h"
#include <cstdarg>



union Data {
   int i;
   float f;
   bool b;
   String* s;
};  

class DataFrame : public Object {
    
    public:
        DataFrame() {

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
         * Returns the number of rows in the DataFrame
         */
        size_t nrow() {

        }

        /**
         * Returns the number of columns in the DataFrame
         */
        size_t ncol() {

        }


};