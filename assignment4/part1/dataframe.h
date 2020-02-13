#pragma once

#include "../string.h"
#include "../object.h"
#include "array.h"
#include "../map.h"
#include <stdarg.h>

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
    IntArray* arr_ = new IntArray();
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
    return arr_->add(val, idx);
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
    StringArray* arr_ = new StringArray();
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
    return arr_->add(val, idx);
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
    BoolArray* arr_ = new BoolArray();
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
    return arr_->add(val, idx);
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
    FloatArray* arr_ = new FloatArray();
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
    return arr_->add(val, idx);
  }

  size_t size() {
    return arr_->getSize();
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

  }
 
  /** Create an empty schema **/
  Schema() {
    StringArray* row_names_ = new StringArray();
    StringArray* col_names_ = new StringArray();
    Map* name_to_type_ = new Map();
  }
 
  /** Create a schema from a string of types. A string that contains
    * characters other than those identifying the four type results in
    * undefined behavior. The argument is external, a nullptr argument is
    * undefined. **/
  Schema(const char* types) { }
 
  /** Add a column of the given type and name (can be nullptr), name
    * is external. Names are expectd to be unique, duplicates result
    * in undefined behavior. */
  void add_column(char typ, String* name) {
    const char* type = &typ;
    name_to_type_->set(name, new String(type, 1));
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
    col_names_->get(idx);
  }
 
  /** Return type of column at idx. An idx >= width is undefined. */
  char col_type(size_t idx) {
    return name_to_type_->get(col_names_->get(idx))->at(0);
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
    accept(b->getBool);
  }

  virtual void accept_(FloatObj* f) {
    accept(f->getFloat);
  }

  virtual void accept_(IntObj* i) {
    accept(i->getInt);
  }

  virtual void accept_(Object* obj) {
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
 * Row::
 *
 * This class represents a single row of data constructed according to a
 * dataframe's schema. The purpose of this class is to make it easier to add
 * read/write complete rows. Internally a dataframe hold data in columns.
 * Rows have pointer equality.
 */
class Row : public Object {
 public:
  Schema scm;
  size_t row_idx_;
  Array* row_;
 
  /** Build a row following a schema. */
  Row(Schema& scm) {
    this->scm = scm;
    row_idx_ = 0;
  }
 
  /** Setters: set the given column with the given value. Setting a column with
    * a value of the wrong type is undefined. */
  void set(size_t col, int val) {
    if (col_type(col) == 'I') {
      row_->add(new IntObj(val));
    }
  }

  void set(size_t col, float val) {
    if (col_type(col) == 'F') {
      row_->add(new FloatObj(val));
    }
  }

  void set(size_t col, bool val) {
    if (col_type(col) == 'B') {
      row_->add(new BoolObj(val));
    }
  }

  /** The string is external. */
  void set(size_t col, String* val) {
    if (col_type(col) == 'S') {
      row_->add(val);
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
      exit(1);
    }
  }

  bool get_bool(size_t col) {
    BoolObj* boolobj = dynamic_cast<BoolObj*> (row_->get(col));
    if (boolobj) {
      return boolobj->getBool();
    }
    else {
      exit(1);
    }
  }

  float get_float(size_t col) {
    FloatObj* floatobj = dynamic_cast<FloatObj*> (row_->get(col));
    if (floatobj) {
      return floatobj->getFloat();
    }
    else {
      exit(1);
    }
  }

  String* get_string(size_t col) {
    String* str = dynamic_cast<String*> (row_->get(col));
    if (str) {
      return str;
    }
    else {
      exit(1);
    }
  }
 
  /** Number of fields in the row. */
  size_t width() {
    return row_->getSize();
  }
 
   /** Type of the field at the given position. An idx >= width is  undefined. */
  char col_type(size_t idx) {
    scm.col_type(idx);
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

  }
 
  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  void join_delete(Rower* other) {

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
  Schema scm;
  ColumnArray* columns_;
  RowArray* row_arr_;
 
  /** Create a data frame with the same columns as the given df but with no rows or rownmaes */
  DataFrame(DataFrame& df) {

  }
 
  /** Create a data frame from a schema and columns. All columns are created
    * empty. */
  DataFrame(Schema& schema) {
    scm = schema;
    Array* columns_ = new Array();
    for (int i = 0; i < scm.width(); i++) {
      switch(scm.col_type(i)) {
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
    return scm;
  }
 
  /** Adds a column this dataframe, updates the schema, the new column
    * is external, and appears as the last column of the dataframe, the
    * name is optional and external. A nullptr colum is undefined. */
  void add_column(Column* col, String* name) {
    scm.add_column(col->get_type, name);
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
    return scm.col_idx(c);
  }
 
  /** Return the offset of the given row name or -1 if no such row. */
  int get_row(String& row) {
    const char* c = row.c_str();
    return scm.col_idx(c);
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

  }
 
  /** Add a row at the end of this dataframe. The row is expected to have
   *  the right schema and be filled with values, otherwise undedined.  */
  void add_row(Row& row) {

  }
 
  /** The number of rows in the dataframe. */
  size_t nrows() {
    return row_arr_->getSize();
  }
 
  /** The number of columns in the dataframe.*/
  size_t ncols() {
    return columns_->getSize();
  }
 
  /** Visit rows in order */
  void map(Rower& r) {
    for (int i = 0; i < nrows(); i++) {
      r.accept(&(row_arr_->get(i)));
    }
  }
 
  /** Create a new dataframe, constructed from rows for which the given Rower
    * returned true from its accept method. */
  DataFrame* filter(Rower& r) {

  }
 
  /** Print the dataframe in SoR format to standard output. */
  void print() {

  }
};