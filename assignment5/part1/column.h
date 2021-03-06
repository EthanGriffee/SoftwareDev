// Lang::CwC
#pragma once

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "object.h"

class BoolColumn;
class FloatColumn;
class StringColumn;
class IntColumn;

/**
 * Enum for the different types of SoR columns this code supports.
 */
enum class ColumnType { STRING, INTEGER, FLOAT, BOOL, UNKNOWN };

/**
 * Converts the given ColumnType to a string.
 * @param type the column type
 * @return A string representing this column type. Do not free or modify this string.
 */
const char* columnTypeToString(ColumnType type) {
    switch (type) {
        case ColumnType::STRING:
            return "STRING";
        case ColumnType::INTEGER:
            return "INTEGER";
        case ColumnType::FLOAT:
            return "FLOAT";
        case ColumnType::BOOL:
            return "BOOL";
        default:
            return "UNKNOWN";
    }
}

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

  virtual void appendMissing() {
      return;
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
    else {
      exit(1);
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
 * Creates the right subclass of Column based on the given type.
 * @param type The type of column to create
 * @return The newly created column. Caller must free.
 */
Column* makeColumnFromType(ColumnType type) {
    switch (type) {
        case ColumnType::STRING:
            return new StringColumn();
        case ColumnType::INTEGER:
            return new IntColumn();
        case ColumnType::FLOAT:
            return new FloatColumn();
        case ColumnType::BOOL:
            return new BoolColumn();
        default:
            assert(false);
    }
}

/**
 * Represents a fixed-size set of columns of potentially different types.
 */
class ColumnSet : public Object {
   public:
    /** The array of columns */
    Column** _columns;
    /** The number of columns we have */
    size_t _length;
    /**
     * Creates a new ColumnSet that can hold the given number of columns.
     * Caller must also call initializeColumn for each column to fully initialize this class.
     * @param num_columns The max number of columns that can be held
     */
    ColumnSet(size_t num_columns) : Object() {
        _columns = new Column*[num_columns];
        _length = num_columns;
        for (size_t i = 0; i < num_columns; i++) {
            _columns[i] = nullptr;
        }
    }
    /**
     * Destructor for ColumnSet
     */
    virtual ~ColumnSet() {
        for (size_t i = 0; i < _length; i++) {
            if (_columns[i] != nullptr) {
                delete _columns[i];
            }
        }
        delete[] _columns;
    }

    /**
     * Gets the number of columns that can be held in this ColumnSet.
     * @return The number of columns
     */
    virtual size_t getLength() { return _length; }

    /**
     * Initializes the given column to the given type. Can only be called exactly once per index.
     * @param which The index for the column to initialize
     * @param type The type of column to create
     */
    virtual void initializeColumn(size_t which, ColumnType type) {
        assert(which < _length);
        assert(_columns[which] == nullptr);
        Column* col = makeColumnFromType(type);
        _columns[which] = col;
    }

    /**
     * Gets the column with the given index. initializeColumn must have been called for this index
     * first.
     * @param which The column index to retrieve
     * @return The column with the given index
     */
    virtual Column* getColumn(size_t which) {
        assert(which < _length);
        assert(_columns[which] != nullptr);
        return _columns[which];
    }
};
