Welcome to our code, lets break it down:

command line arguments:

    required :
        -f  str     // path to SoR file to be read

        One and only one of:
            // prints the type of a column: BOOL, INT, FLOAT, STRING, MISSING
            -print_col_type uint 

            // the first argument is the column, the second is the offset, and returns the field stored there 
            -print_col_idx uint uint  

            // is there a missing in the specified column offset, Returns True or False
            -is_missing_idx uint uint 

    optional :
        -from uint  // starting position in the file (in bytes) The first and last lines are thrown out if from =/= 0
        -len uint   // number of bytes to read
    
    with new lines counting as one bite 

How the code works:

    The code parses through the first 500 lines, remembering and stores the schema and field as a tupple in an array of arrays.
    It then uses the longest row as the base schema. When determining if 




first u put in ur arguments
then we read like 500 lines (or less!!)
during that we do everything

A NEW LINE COUNTS AS A BYTE

USE TRUE AND FALSE FOR BOOLEAN OUTPUTS

unless we have an input row > 500
then we parse that too
the end