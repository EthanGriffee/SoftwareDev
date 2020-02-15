#pragma once

#include "../string.h"
#include "../object.h"
#include "../array.h"
#include "../helper.h"
#include "../map.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>

class BoolColumn;
class FloatColumn;
class StringColumn;
class IntColumn;
class RowArray;
class ColumnArray;


/**************************************************************************
 * Column ::
 * Represents one column of a data frame which holds values of a single type.
 * This abstract class defines methods overriden in subclasses. There is
 * one subclass per element type. Columns are mutable, equality is pointer
 * equality. */

class Column : public Object {
 public:
 
  /** Type converters: Return same column under its actual type, or
   *  nullptr if of the wrong type.  */
  virtual IntColumn* as_int() {
      return nullptr;
  }

  virtual BoolColumn*  as_bool(){
      return nullptr;
  }

  virtual FloatColumn* as_float(){
      return nullptr;
  }

  virtual StringColumn* as_string(){
      return nullptr;
  }
 
  /** Type appropriate push_back methods. Calling the wrong method is
    * undefined behavior. **/
  virtual void push_back(int val) {
    return;
  }

  virtual void push_back(bool val) {
    return;
  }

  virtual void push_back(float val) {
    return;
  }

  virtual void push_back(String* val) {
    return;
  }
 
 /** Returns the number of elements in the column. */
  virtual size_t size() {
    return 0;
  }
 
  /** Return the type of this column as a char: 'S', 'B', 'I' and 'F'. */
  char get_type() {
    if (this->as_string()) {
      return 'S';
    }
    else if (this->as_float()) {
      return 'F';
    }
    else if (this->as_int()) {
      return 'I';
    }
    else if (this->as_bool()) {
      return 'B';
    }
  }
};
 
/*************************************************************************
 * IntColumn::
 * Holds int values.
 */
class IntColumn : public Column {
 public:
  IntArray* arr_;

  IntColumn() {
    arr_ = new IntArray();
  }

  IntColumn(int n, ...) {
    va_list valist;
    int num;
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
      arr_->add(va_arg(valist, int));
    }
    va_end(valist);
  }

  int get(size_t idx) {
    return arr_->get(idx);
  }

  IntColumn* as_int() {
    return this;
  }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val) {
    return arr_->set(val, idx);
  }

  virtual void push_back(int val) {
    arr_->add(val);
  }


  size_t size() {
    return arr_->getSize();
  }
};
 
// Other primitive column classes similar...
 
/*************************************************************************
 * StringColumn::
 * Holds string pointers. The strings are external.  Nullptr is a valid
 * value.
 */
class StringColumn : public Column {
 public:
  StringArray* arr_;
  StringColumn() {
    arr_ = new StringArray();
  }

  StringColumn(String* n, ...) {
    va_list valist;
    int num;
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
      arr_->add(va_arg(valist, String*));
    }
    va_end(valist);
  }

  StringColumn* as_string() {
    return this;
  }

  /** Returns the string at idx; undefined on invalid idx.*/
  String* get(size_t idx)  {
    return arr_->get(idx);
  }

  /** Out of bound idx is undefined. */
  void set(size_t idx, String* val) {
    return arr_->set(val, idx);
  }

  virtual void push_back(String* val) {
    arr_->add(val);
  }

  size_t size() {
    return arr_->getSize();
  }
};

/*************************************************************************
 * BoolColumn::
 * Holds bool values.
 */
class BoolColumn : public Column {
 public:
  BoolArray* arr_;
  BoolColumn() {
    arr_ = new BoolArray();
  }

  BoolColumn(bool b, ...) {
    va_list valist;
    int num;
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
      arr_->add(va_arg(valist, bool));
    }
    va_end(valist);
  }

  BoolColumn* as_bool() {
    return this;
  }

  /** Returns the string at idx; undefined on invalid idx.*/
  bool get(size_t idx)  {
    return arr_->get(idx);
  }

  /** Out of bound idx is undefined. */
  void set(size_t idx, bool val) {
    return arr_->set(val, idx);
  }

  virtual void push_back(bool val) {
    arr_->add(val);
  }

  size_t size() {
    return arr_->getSize();
  }
};

/*************************************************************************
 * FloatColumn::
 * Holds float values.
 */
class FloatColumn : public Column {
 public:
  FloatArray* arr_;
  FloatColumn() {
    arr_ = new FloatArray();
  }

  FloatColumn(bool b, ...) {
    va_list valist;
    int num;
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
      arr_->add(va_arg(valist, bool));
    }
    va_end(valist);
  }

  FloatColumn* as_float() {
    return this;
  }

  /** Returns the string at idx; undefined on invalid idx.*/
  bool get(size_t idx)  {
    return arr_->get(idx);
  }

  /** Out of bound idx is undefined. */
  void set(size_t idx, bool val) {
    return arr_->set(val, idx);
  }

  virtual void push_back(float val) {
    arr_->add(val);
  }

  size_t size() {
    return arr_->getSize();
  }
};


/**
 * Incomplete implementation of Column Array. No methods overriden from
 * Array. Created for testing purposes, so we can design tests. 
 **/
class ColumnArray : public Object {
  public:
      Array* col_arr;

      /**
       * Default constructor which will set the initial max-capacity to the array to 10. 
       **/
      ColumnArray() {
          col_arr = new Array();
      }

      /**
       * Initalized this array with the characteristics of the passed in array.
       * @arg arr Array containing values to be used in initialization. 
       **/
      ColumnArray(ColumnArray* arr) {
          col_arr = arr->col_arr;
      }

      /**
       * Destructor which will free the memory of the underlying array as well. 
       **/
      ~ColumnArray() {
          delete col_arr;
      }

      /**
       * Will return the Column pointer at the provided index. if the index is invalid, 
       * then the method will return NULL.
       * @arg index Location to get the value in the array at. 
       **/
      Column* get(size_t index) {
          return static_cast <Column*> (col_arr->get(index));
      }


      /**
       * Clears the array and reinitializes the underlying array to 10 spots with no elements. 
       * Reinitializes the size to 0. 
       **/
      void clear() {
          col_arr->clear();
      }

      /**
       * Resizing the underlying array. And then copying over the elements to a new array with
       * the updated size. 
       * Default is doubling the array size when the max capacity of the 
       * underlying array less the number of elements is 2. 
       **/
      void resize() {
          col_arr->resize();
      }

      /**
       * Returns the first index of the of given Column pointer. 
       * If the pointer is not a Column, return -1. 
       * If the Column pointer is not found then -1 is returned.
       * @arg to_find Column to find the index of. 
       **/
      int indexOf(Object* to_find) {
          return col_arr->indexOf(to_find);
      }

      /**
       * Adds the element provided to the end of the list, unless the given element is NULL, 
       * then it will not be added. The size is incremented by 1. If resizing the array is necessary, 
       * then that should be done.
       * @arg to_add Object to be added to the array. 
       **/
      void add(Column* to_add) {
          return col_arr->add(to_add);
      }

  /**
   * Adds the provided array to the end of the list, unless the given array is NULL, 
   * then it will not be added. 
   * Assuming a valid move, the size of this array is incremented by the size of the 
   * added array. If resizing the array is necessary, then that should be done.
   * @arg to_add Array of Column that all need to be added to this array. 
   **/
    void addAll(ColumnArray* to_add) {
        return col_arr->addAll(to_add->col_arr);
    }

  /**
   * Adds the provided Column at the given index, unless the given object is NULL, 
   * then it will not be added. Otherwise, all elements previously at the index and
   * to the right will be shifted accordingly. 
   * If the index is invalid, then nothing will be added/shifted. 
   * The size of this array is incremented by 1. 
   * If resizing the array is necessary, then that should be done.
   * If the object provided is not a Column, then do nothing.  
   * @arg to_add Object to be added to the array
   * @arg index Location to add the Object at
   **/
    void add(Column* to_add, size_t index) {
        return col_arr->add(to_add, index);
    }

  /**
   * Adds all the elements of the provided array at the given index, 
   * unless the given array is NULL, then it will not be added. Otherwise, 
   * all elements previously at the index and
   * to the right will be shifted accordingly by the size of the procided array, 
   * If the index is invalid, then nothing will be added/shifted.
   * Assuming a valid move, the size of this array is incremented by the size of the 
   * added array.  If resizing the array is necessary, then that should be done.
   * @arg to_add Array of Objects to be added to the array
   * @arg index Location to add the objects to the array at
   **/
    void addAll(ColumnArray* to_add, size_t index) {
      col_arr->addAll(to_add->col_arr, index);
    }

  /**
   * Returns the subarray starting from the provided index to the end of the array. 
   * If the index is invalid, then the method returns NULL
   * @arg index Starting place for the subarray
   **/
    ColumnArray* subArray(size_t index) {
      ColumnArray* returning = new ColumnArray();
      if (index > getSize()) {
          return NULL;
      }
      while(index < getSize()) {
          returning->add(get(index));
          index += 1;
      }
      return returning;
    }

  /**
   * Returns the subarray starting from the provided index to the ending index
   * The starting index must always be greater than the ending index. If either index is invalid, 
   * then NULL is returned. The set is [start, end)
   * @arg startIndex starting place for the subarray
   * @arg endIndex location of the last object to be put in the subarray
   **/
    ColumnArray* subArray(size_t startIndex, size_t endIndex) {
      ColumnArray* returning = new ColumnArray();
      if (endIndex > getSize() || startIndex > endIndex) {
          return NULL;
      }
      while(startIndex < endIndex) {
          returning->add(get(startIndex));
          startIndex += 1;
      }
      return returning;
    }

  /**
   * Removes the first instance of the given Object in this array. If nothing 
   * is found, then no action will occur. The size reduces by 1 if the 
   * element is found.
   * If the object to be removed is not a Column, do nothing. 
   * @arg to_remove Column to be removed from the array
   **/
    void remove(Object* to_remove) {
        col_arr->remove(to_remove);
    }

  /**
   * Removes all instances of the given Object in this array. If nothing 
   * is found, then no action will occur. The size reduces the number of found
   * elements there are.
   * If the object to remove is not a Column, do nothing. 
   * @arg to_remove Column that all instances in the array will be removed of
   **/
    void removeAll(Object* to_remove) {
        col_arr->removeAll(to_remove);
    }

  /**
   * Returns number of elements in the array. 
   **/
    size_t getSize() {
        return col_arr->getSize();
    }

  /**
   * Overriding the Column equals method. 
   * Returns if all the elements in this array and the given object are equal and 
   * in the same other. 
   * If the given object is NULL or not an array, then false will be returned.
   * @arg other Object to check if this array is equal to
   **/
  bool equals(Object* other) {
      ColumnArray* o = dynamic_cast<ColumnArray*> (other);
      return o->col_arr->equals(this->col_arr);
  }

  /**
   * Overriding the Object hash_me() method. 
   * Hashes the array based on user specifications. Default implementation is
   * to hash all internal elements and sum them up. 
   **/
  size_t hash_me_() {
      return col_arr->hash() + 1;
  }

};
 
 
/*************************************************************************
 * Schema::
 * A schema is a description of the contents of a data frame, the schema
 * knows the number of columns and number of rows, the type of each column,
 * optionally columns and rows can be named by strings.
 * The valid types are represented by the chars 'S', 'B', 'I' and 'F'.
 */
class Schema : public Object {
 public:
  StringArray* row_names_;
  StringArray* col_names_;
  Map* name_to_type_;

 
  /** Copying constructor */
  Schema(Schema& from) {
    row_names_ =  from.row_names_;
    col_names_ =  from.col_names_;
    name_to_type_ = from.name_to_type_;
  }
 
  /** Create an empty schema **/
  Schema() {
    row_names_ = new StringArray();
    col_names_ = new StringArray();
    name_to_type_ = new Map();
  }
 
  /** Create a schema from a string of types. A string that contains
    * characters other than those identifying the four type results in
    * undefined behavior. The argument is external, a nullptr argument is
    * undefined. **/
  Schema(const char* types) {
    row_names_ = new StringArray();
    col_names_ = new StringArray();
    name_to_type_ = new Map();
    int x = 0;
    char curr_type;
    while (types[x] != '\0') {
      char* str_name = new char[33];
      sprintf(str_name, "%d", x); 
      curr_type = char(types[x]);
      add_column(curr_type, new String(str_name));
      x += 1;
    }
  }
 
  /** Add a column of the given type and name (can be nullptr), name
    * is external. Names are expectd to be unique, duplicates result
    * in undefined behavior. */
  void add_column(char typ, String* name) {
    name_to_type_->set(name, typ);
    col_names_->add(name);
  }
 
  /** Add a row with a name (possibly nullptr), name is external.  Names are
   *  expectd to be unique, duplicates result in undefined behavior. */
  void add_row(String* name) {
    row_names_->add(name);
  }
 
  /** Return name of row at idx; nullptr indicates no name. An idx >= width
    * is undefined. */
  String* row_name(size_t idx) {
    return row_names_->get(idx);
  }
 
  /** Return name of column at idx; nullptr indicates no name given.
    *  An idx >= width is undefined.*/
  String* col_name(size_t idx) {
    return col_names_->get(idx);
  }
 
  /** Return type of column at idx. An idx >= width is undefined. */
  char col_type(size_t idx) {
    return name_to_type_->get(col_name(idx));
  }
 
  /** Given a column name return its index, or -1. */
  int col_idx(const char* name) {
    String* checking = new String(name);
    int i =  col_names_->indexOf(checking);
    delete checking;
    return i;
  }
 
  /** Given a row name return its index, or -1. */
  int row_idx(const char* name) {
    String* checking = new String(name);
    int i =  row_names_->indexOf(checking);
    delete checking;
    return i;
  }
 
  /** The number of columns */
  size_t width() {
    return col_names_->getSize();
  }
 
  /** The number of rows */
  size_t length() {
    return row_names_->getSize();
  }
};
 
/*****************************************************************************
 * Fielder::
 * A field vistor invoked by Row.
 */
class Fielder : public Object {
public:

  /** Called before visiting a row, the argument is the row offset in the
    dataframe. */
  virtual void start(size_t r) {

  }
 
  /** Called for fields of the argument's type with the value of the field. */
  virtual void accept(bool b) {

  }

  virtual void accept(float f) {

  }

  virtual void accept(int i) {

  }

  virtual void accept(String* s) {

  }

  virtual void accept_(BoolObj* b) {
    accept(b->getBool());
  }

  virtual void accept_(FloatObj* f) {
    accept(f->getFloat());
  }

  virtual void accept_(IntObj* i) {
    accept(i->getInt());
  }

  virtual void accept_(Object* obj) {
    perror("calling accept on an Object that is not a Bool, Float, Int, or String");
    exit(1);
  }

  virtual void accept_(String* s) {
    accept(s);
  }
 
  /** Called when all fields have been seen. */
  virtual void done() {

  }
};
/*************************************************************************
 * PrintFielder::
 *
 * 
 */
 class PrintFielder : public Fielder {
  public:
    RowArray* row_arr_;
    size_t row;
    Sys system;

    PrintFielder(RowArray* row_arrs) {
      row_arr_ = row_arrs;
      row = 0;
    }

    virtual void start(size_t r) {
      row = r;
    }
  
    /** Called for fields of the argument's type with the value of the field. */
    virtual void accept(bool b) {
      system.p(b);
    }

    virtual void accept(float f) {
      system.p(f);
    }

    virtual void accept(int i) {
      system.p(i);
    }

    virtual void accept(String* s) {
      system.p(s);
    }
};

/*************************************************************************
 * Row::
 *
 * This class represents a single row of data constructed according to a
 * dataframe's schema. The purpose of this class is to make it easier to add
 * read/write complete rows. Internally a dataframe hold data in columns.
 * Rows have pointer equality.
 */
class Row : public Object {
 public:
  Schema* scm;
  size_t row_idx_;
  Array* row_;
 
  /** Build a row following a schema. */
  Row(Schema& scm) {
    this->scm = &scm;
    row_idx_ = 0;
    row_ = new Array();
  }

 
  /** Setters: set the given column with the given value. Setting a column with
    * a value of the wrong type is undefined. */
  void set(size_t col, int val) {
    if (col_type(col) == 'I') {
      row_->set(new IntObj(val), col);
    }
  }

  void set(size_t col, float val) {
    if (col_type(col) == 'F') {
      row_->set(new FloatObj(val), col);
    }
  }

  void set(size_t col, bool val) {
    if (col_type(col) == 'B') {
      row_->set(new BoolObj(val), col);
    }
  }

  /** The string is external. */
  void set(size_t col, String* val) {
    if (col_type(col) == 'S') {
      row_->set(val, col);
    }
  }
 
  /** Set/get the index of this row (ie. its position in the dataframe. This is
   *  only used for informational purposes, unused otherwise */
  void set_idx(size_t idx) {
    row_idx_ = idx;
  }

  size_t get_idx() {
    return row_idx_;
  }
 
  /** Getters: get the value at the given column. If the column is not
    * of the requested type, the result is undefined. */
  int get_int(size_t col) {
    IntObj* intobj = dynamic_cast<IntObj*> (row_->get(col));
    if (intobj) {
      return intobj->getInt();
    }
    else {
      perror("calling get_int on a col_indx that is not a int column");
      exit(1);
    }
  }

  bool get_bool(size_t col) {
    BoolObj* boolobj = dynamic_cast<BoolObj*> (row_->get(col));
    if (boolobj) {
      return boolobj->getBool();
    }
    else {
      perror("calling get_bool on a col_indx that is not a bool column");
      exit(1);
    }
  }

  float get_float(size_t col) {
    FloatObj* floatobj = dynamic_cast<FloatObj*> (row_->get(col));
    if (floatobj) {
      return floatobj->getFloat();
    }
    else {
      perror("calling get on a get_float that is not a float column");
      exit(1);
    }
  }

  String* get_string(size_t col) {
    String* str = dynamic_cast<String*> (row_->get(col));
    if (str) {
      return str;
    }
    else {
      perror("calling get_string on a col_indx that is not a String column");
      exit(1);
    }
  }
 
  /** Number of fields in the row. */
  size_t width() {
    return row_->getSize();
  }
 
   /** Type of the field at the given position. An idx >= width is  undefined. */
  char col_type(size_t idx) {
    return  scm->col_type(idx);
  }
 
  /** Given a Fielder, visit every field of this row. The first argument is
    * index of the row in the dataframe.
    * Calling this method before the row's fields have been set is undefined. */
  void visit(size_t idx, Fielder& f) {
    f.start(row_idx_);
    for (int x = 0; x < width(); x++) {
      f.accept_(row_->get(x));
    }
    f.done();
  }
 
};

/**
 * Incomplete implementation of Row Array. No methods overriden from
 * Array. Created for testing purposes, so we can design tests. 
 **/
class RowArray : public Object {
  public:
      Array* str_arr;

      /**
       * Default constructor which will set the initial max-capacity to the array to 10. 
       **/
      RowArray() {
          str_arr = new Array();
      }

      /**
       * Initalized this array with the characteristics of the passed in array.
       * @arg arr Array containing values to be used in initialization. 
       **/
      RowArray(RowArray* arr) {
          str_arr = arr->str_arr;
      }

      /**
       * Destructor which will free the memory of the underlying array as well. 
       **/
      ~RowArray() {
          delete str_arr;
      }

      /**
       * Will return the Row pointer at the provided index. if the index is invalid, 
       * then the method will return NULL.
       * @arg index Location to get the value in the array at. 
       **/
      Row* get(size_t index) {
          return static_cast <Row*> (str_arr->get(index));
      }


      /**
       * Clears the array and reinitializes the underlying array to 10 spots with no elements. 
       * Reinitializes the size to 0. 
       **/
      void clear() {
          str_arr->clear();
      }

      /**
       * Resizing the underlying array. And then copying over the elements to a new array with
       * the updated size. 
       * Default is doubling the array size when the max capacity of the 
       * underlying array less the number of elements is 2. 
       **/
      void resize() {
          str_arr->resize();
      }

      /**
       * Returns the first index of the of given Row pointer. 
       * If the pointer is not a Row, return -1. 
       * If the Row pointer is not found then -1 is returned.
       * @arg to_find Row to find the index of. 
       **/
      int indexOf(Object* to_find) {
          return str_arr->indexOf(to_find);
      }

      /**
       * Adds the element provided to the end of the list, unless the given element is NULL, 
       * then it will not be added. The size is incremented by 1. If resizing the array is necessary, 
       * then that should be done.
       * @arg to_add Object to be added to the array. 
       **/
      void add(Row* to_add) {
          return str_arr->add(to_add);
      }

  /**
   * Adds the provided array to the end of the list, unless the given array is NULL, 
   * then it will not be added. 
   * Assuming a valid move, the size of this array is incremented by the size of the 
   * added array. If resizing the array is necessary, then that should be done.
   * @arg to_add Array of Row that all need to be added to this array. 
   **/
    void addAll(RowArray* to_add) {
        return str_arr->addAll(to_add->str_arr);
    }

  /**
   * Adds the provided Row at the given index, unless the given object is NULL, 
   * then it will not be added. Otherwise, all elements previously at the index and
   * to the right will be shifted accordingly. 
   * If the index is invalid, then nothing will be added/shifted. 
   * The size of this array is incremented by 1. 
   * If resizing the array is necessary, then that should be done.
   * If the object provided is not a Row, then do nothing.  
   * @arg to_add Object to be added to the array
   * @arg index Location to add the Object at
   **/
    void add(Row* to_add, size_t index) {
        return str_arr->add(to_add, index);
    }

  /**
   * Adds all the elements of the provided array at the given index, 
   * unless the given array is NULL, then it will not be added. Otherwise, 
   * all elements previously at the index and
   * to the right will be shifted accordingly by the size of the procided array, 
   * If the index is invalid, then nothing will be added/shifted.
   * Assuming a valid move, the size of this array is incremented by the size of the 
   * added array.  If resizing the array is necessary, then that should be done.
   * @arg to_add Array of Objects to be added to the array
   * @arg index Location to add the objects to the array at
   **/
    void addAll(RowArray* to_add, size_t index) {
      str_arr->addAll(to_add->str_arr, index);
    }

  /**
   * Returns the subarray starting from the provided index to the end of the array. 
   * If the index is invalid, then the method returns NULL
   * @arg index Starting place for the subarray
   **/
    RowArray* subArray(size_t index) {
      RowArray* returning = new RowArray();
      if (index > getSize()) {
          return NULL;
      }
      while(index < getSize()) {
          returning->add(get(index));
          index += 1;
      }
      return returning;
    }

  /**
   * Returns the subarray starting from the provided index to the ending index
   * The starting index must always be greater than the ending index. If either index is invalid, 
   * then NULL is returned. The set is [start, end)
   * @arg startIndex starting place for the subarray
   * @arg endIndex location of the last object to be put in the subarray
   **/
    RowArray* subArray(size_t startIndex, size_t endIndex) {
      RowArray* returning = new RowArray();
      if (endIndex > getSize() || startIndex > endIndex) {
          return NULL;
      }
      while(startIndex < endIndex) {
          returning->add(get(startIndex));
          startIndex += 1;
      }
      return returning;
    }

  /**
   * Removes the first instance of the given Object in this array. If nothing 
   * is found, then no action will occur. The size reduces by 1 if the 
   * element is found.
   * If the object to be removed is not a Row, do nothing. 
   * @arg to_remove Row to be removed from the array
   **/
    void remove(Object* to_remove) {
        str_arr->remove(to_remove);
    }

  /**
   * Removes all instances of the given Object in this array. If nothing 
   * is found, then no action will occur. The size reduces the number of found
   * elements there are.
   * If the object to remove is not a Row, do nothing. 
   * @arg to_remove Row that all instances in the array will be removed of
   **/
    void removeAll(Object* to_remove) {
        str_arr->removeAll(to_remove);
    }

  /**
   * Returns number of elements in the array. 
   **/
    size_t getSize() {
        return str_arr->getSize();
    }

  /**
   * Overriding the Row equals method. 
   * Returns if all the elements in this array and the given object are equal and 
   * in the same other. 
   * If the given object is NULL or not an array, then false will be returned.
   * @arg other Object to check if this array is equal to
   **/
  bool equals(Object* other) {
      RowArray* o = dynamic_cast<RowArray*> (other);
      return o->str_arr->equals(this->str_arr);
  }

  /**
   * Overriding the Object hash_me() method. 
   * Hashes the array based on user specifications. Default implementation is
   * to hash all internal elements and sum them up. 
   **/
  size_t hash_me_() {
      return str_arr->hash() + 1;
  }

};
 
/*******************************************************************************
 *  Rower::
 *  An interface for iterating through each row of a data frame. The intent
 *  is that this class should subclassed and the accept() method be given
 *  a meaningful implementation. Rowers can be cloned for parallel execution.
 */
class Rower : public Object {
 public:
  /** This method is called once per row. The row object is on loan and
      should not be retained as it is likely going to be reused in the next
      call. The return value is used in filters to indicate that a row
      should be kept. */
  virtual bool accept(Row& r) {
    return true;
  }
 
  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  virtual void join_delete(Rower* other) {
  }
};

/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class DataFrame : public Object {
 public:
  Schema* scm;
  ColumnArray* columns_;
  RowArray* row_arr_;
 
  /** Create a data frame with the same columns as the given df but with no rows or rownmaes */
  DataFrame(DataFrame& df) {
    scm = new Schema();
    Schema scmCoppying = df.get_schema();
    row_arr_ = new RowArray();
    columns_ = new ColumnArray();
    for (int i = 0; i < df.ncols(); i++) {
      char col_type = scmCoppying.col_type(i);
      scm->add_column(col_type, scmCoppying.col_name(i));
      switch(col_type) {
        case 'F':
          columns_->add(new FloatColumn());
          break;
        case 'B':
          columns_->add(new BoolColumn());
          break;
        case 'I':
          columns_->add(new IntColumn());
          break;
        case 'S':
          columns_->add(new StringColumn());
          break;
      }
    }
  }
 
  /** Create a data frame from a schema and columns. All columns are created
    * empty. */
  DataFrame(Schema& schema) {
    scm = &schema;
    columns_ = new ColumnArray();
    row_arr_ = new RowArray();
    for (int i = 0; i < scm->width(); i++) {
      switch(scm->col_type(i)) {
        case 'F':
          columns_->add(new FloatColumn());
          break;
        case 'B':
          columns_->add(new BoolColumn());
          break;
        case 'I':
          columns_->add(new IntColumn());
          break;
        case 'S':
          columns_->add(new StringColumn());
          break;
      }
    }
  }
 
  /** Returns the dataframe's schema. Modifying the schema after a dataframe
    * has been created in undefined. */
  Schema& get_schema() {
    return *scm;
  }
 
  /** Adds a column this dataframe, updates the schema, the new column
    * is external, and appears as the last column of the dataframe, the
    * name is optional and external. A nullptr colum is undefined. */
  void add_column(Column* col, String* name) {
    scm->add_column(col->get_type(), name);
    columns_->add(col);
  }
 
  /** Return the value at the given column and row. Accessing rows or
   *  columns out of bounds, or request the wrong type is undefined.*/
  int get_int(size_t col, size_t row) {
    return columns_->get(col)->as_int()->get(row);
  }

  bool get_bool(size_t col, size_t row) {
    return columns_->get(col)->as_bool()->get(row);
  }

  float get_float(size_t col, size_t row) {
    return columns_->get(col)->as_float()->get(row);

  }

  String*  get_string(size_t col, size_t row) {
    return columns_->get(col)->as_string()->get(row);
  }
 
  /** Return the offset of the given column name or -1 if no such col. */
  int get_col(String& col) {
    const char* c = col.c_str();
    return scm->col_idx(c);
  }
 
  /** Return the offset of the given row name or -1 if no such row. */
  int get_row(String& row) {
    const char* c = row.c_str();
    return scm->col_idx(c);
  }
 
  /** Set the value at the given column and row to the given value.
    * If the column is not  of the right type or the indices are out of
    * bound, the result is undefined. */
  void set(size_t col, size_t row, int val) {
    columns_->get(row)->as_int()->set(col, val);
    row_arr_->get(col)->set(row, val);
  }

  void set(size_t col, size_t row, bool val) {
    columns_->get(row)->as_bool()->set(col, val);
    row_arr_->get(col)->set(row, val);
  }

  void set(size_t col, size_t row, float val) {
    columns_->get(row)->as_float()->set(col, val);
    row_arr_->get(col)->set(row, val);
  }

  void set(size_t col, size_t row, String* val) {
    columns_->get(row)->as_string()->set(col, val);
    row_arr_->get(col)->set(row, val);
  }
 
  /** Set the fields of the given row object with values from the columns at
    * the given offset.  If the row is not form the same schema as the
    * dataframe, results are undefined.
    */
  void fill_row(size_t idx, Row& row) {
    for(size_t i = 0; i < columns_->getSize(); i++) {
      switch(columns_->get(i)->get_type()) {
        case 'F':
          row.set(i, columns_->get(i)->as_float()->get(idx));
          break;
        case 'I':
          row.set(i, columns_->get(i)->as_int()->get(idx));
          break;
        case 'S':
          row.set(i, columns_->get(i)->as_string()->get(idx));
          break;
        case 'B':
          row.set(i, columns_->get(i)->as_bool()->get(idx));
          break;
      }
    }

  }
 
  /** Add a row at the end of this dataframe. The row is expected to have
   *  the right schema and be filled with values, otherwise undedined.  */
  void add_row(Row& row) {
    Row* r = new Row(get_schema());
    r->set_idx(nrows() - 1);
    row_arr_->add(r);
    for(size_t i = 0; i < row.width(); i++) {
      Column* curr_column = columns_->get(i);
      switch(columns_->get(i)->get_type()) {
        case 'F': {
          float f = row.get_float(i);
          curr_column->push_back(f);
          r->set(i, f);
          break;
        }
        case 'I': {
          int in = row.get_int(i);
          curr_column->push_back(in);
          r->set(i, in);
          break;
        }
        case 'B': {
          bool b = row.get_bool(i);
          curr_column->push_back(b);
          r->set(i, b);
          break;
        }
        case 'S': {
          String* s = row.get_string(i);
          curr_column->push_back(s);
          r->set(i, s);
          break;
        }
      }
    }
  }
 
  /** The number of rows in the dataframe. */
  size_t nrows() {
    return row_arr_->getSize();
  }
 
  /** The number of columns in the dataframe.*/
  size_t ncols() {
    return columns_->getSize();
  }
 
  /** Visit rows in order   */
  void map(Rower& r) {
    for (int i = 0; i < nrows(); i++) {
      r.accept(*row_arr_->get(i));
    }
  }
 
  /** Create a new dataframe, constructed from rows for which the given Rower
    * returned true from its accept method. */
  DataFrame* filter(Rower& r) {
    DataFrame* n = new DataFrame(*scm);
    for (int i = 0; i < nrows(); i++) {
      Row row = *row_arr_->get(i);
      if (r.accept(row)) {
        Sys x;
        x.p("fdsfds");
        
        n->add_row(row);
      }
    }
    return n;
  }

  /** Print the dataframe in SoR format to standard output. */
  void print() {
    Sys system;
    PrintFielder pfielder = PrintFielder(row_arr_);
    for (int i = 0; i < ncols(); i++) {
      system.p(scm->col_name(i));
    }
    for (int i = 0; i < nrows(); i++) {
      system.p(scm->row_name(i));
      row_arr_->get(i)->visit(i, pfielder);
    }
  }

    void pmap_helper1_(Rower& r) {
        for (int i = 0; i < nrows() / 2; i++) {
            r.accept(*row_arr_->get(i));
        }
    }

    void pmap_helper2_(Rower& r) {
        for (int i = nrows() / 2; i < nrows(); i++) {
            r.accept(*row_arr_->get(i));
        }
    }

  /** This method clones the Rower and executes the map in parallel. Join is
  * used at the end to merge the results. */
    void pmap(Rower& r) {
        Rower* r2 = static_cast<Rower*>(r.clone());
        std::thread t1(&DataFrame::pmap_helper2_, this, r); // stars foo in a seperate thread
        std::thread t2(&DataFrame::pmap_helper2_, this, r2);  // stars foo in a seperate thread

        t1.join();
        t2.join();
        r.join_delete(r2);
    
    }
};