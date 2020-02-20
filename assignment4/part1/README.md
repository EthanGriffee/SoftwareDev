Intro: 
    The Dataframe is a structure used to store data in columnar 
    format. The Dataframe is an object that can be created using
    a Schema or another Dataframe. A Schema knows the names of 
    all rows and columns and the column types of the columns.
    Each row has a schema that it is expected to confrim to.
    A String column represents a list of Strings, a Bool Column
    represents a list of columns, ect. The dataframe keeps track 
    of the rows and column.


Design Choices:
    Both the rows and columns have an array that contains the
    values associated with the given row and column. When a 
    row is changed the column is also changed and vice versa. 
    We decided to have the schema to have two string arrays,
    one for column names and one for row names. We also had
    the schema contain a map which keeps track of column names
    to column type. This was decided because column names were
    known to be unique. We did not really change our 
    implementation to deal with behavior that was deemed as 
    undefined in the API.


Use Cases:
    Fielder and Rower are used to iterate through the fields or 
    rows. An example of when a Rower would be used is if you want 
    to not include any row that contains a false value. Then, 
    a Rower class would be created with an accept method that 
    only returns true when all columns in the row do not contain
    a boolean that is false. A dataframe would be used to store
    data that can be used by Rowers.