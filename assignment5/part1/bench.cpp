#include "modified_dataframe.h"
#include "parser.h"
#include "array.h"
#include "string.h"

/*******************************************************************************
 *  Rower::
 *  A Rower that only wastes time, used to show that it is faster
 */
class ReallyDumbRower : public Rower {
 public:
    size_t sum;

    ReallyDumbRower() { sum = 0;}

  virtual bool accept(Row& r) {
    for (int x = 0; x < 10000; x++) {
        sum += 1;
    }
    return true;
  }

  virtual ReallyDumbRower* clone() {
      return new ReallyDumbRower();
  }
 
  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  virtual void join_delete(Rower* other) {
      ReallyDumbRower* r = dynamic_cast<ReallyDumbRower*> (other);
      if (other)
        sum = sum + r->getSum();
      else {
        exit(1);
      }
  }

  size_t getSum() {
    return sum;
  }
};


/*******************************************************************************
 *  Rower::
 *  Adds all Strings to an arraylist of strings
 */
class FieldsToArraysRower : public Rower {
 public:
    StringArray* str_array;
    FloatArray* float_array;
    BoolArray* bool_array;
    IntArray* int_array;

    FieldsToArraysRower() {
      str_array = new StringArray();
      float_array = new FloatArray();
      bool_array = new BoolArray();
      int_array = new IntArray();
    }

  virtual bool accept(Row& r) {
    for (int x = 0; x < r.width(); x++) {
      if (r.col_type(x) == 'S') {
        str_array->add(r.get_string(x));
      }
      else if (r.col_type(x) == 'F') {
        float_array->add(r.get_float(x));
      }
      else if (r.col_type(x) == 'B') {
        bool_array->add(r.get_bool(x));
      }
      else if (r.col_type(x) == 'I') {
        float_array->add(r.get_int(x));
      }
    }
    return true;
  }

  virtual FieldsToArraysRower* clone() {
      return new FieldsToArraysRower();
  }
 
  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  virtual void join_delete(Rower* other) {
      FieldsToArraysRower* r = dynamic_cast<FieldsToArraysRower*> (other);
      if (other) {
        str_array->addAll(r->getStringArray());
        float_array->addAll(r->getFloatArray());
        bool_array->addAll(r->getBoolArray());
        int_array->addAll(r->getIntArray());
      }
      else {
        exit(1);
      }
  }

  StringArray* getStringArray() {
    return str_array;
  }

  FloatArray* getFloatArray() {
    return float_array;
  }

  BoolArray* getBoolArray() {
    return bool_array;
  }

  IntArray* getIntArray() {
    return int_array;
  }
};





ModifiedDataFrame* create_dataframe_from_file(size_t factor) {
  Schema s;
  ModifiedDataFrame* df = new  ModifiedDataFrame(s);
  FILE* file = fopen("datafile.txt", "r");
  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  SorParser parser{file, 0, file_size / factor, file_size};
  parser.guessSchema();
  parser.parseFile();
  ColumnSet* set = parser.getColumnSet();
  for (int x = 0; x < set->getLength(); x++) {
    char* str_name = new char[33];
    sprintf(str_name, "%d", x); 
    df->add_column(set->getColumn(x), new String(str_name));
  }
  return df;
}

void really_dumb_testpmap() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(1);
  ReallyDumbRower rower = ReallyDumbRower();
  df->pmap(rower);
  sys.p(rower.getSum());
}

void really_dumb_testmap() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(1);
  ReallyDumbRower rower = ReallyDumbRower();
  df->map(rower);
  sys.p(rower.getSum());
}

void really_dumb_testpmap_half_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(2);
  ReallyDumbRower rower = ReallyDumbRower();
  df->pmap(rower);
  sys.p(rower.getSum());
}

void really_dumb_testmap_half_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(2);
  ReallyDumbRower rower = ReallyDumbRower();
  df->map(rower);
  sys.p(rower.getSum());
}

void really_dumb_testpmap_tenth_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(10);
  ReallyDumbRower rower = ReallyDumbRower();
  df->pmap(rower);
  sys.p(rower.getSum());
}

void really_dumb_testmap_tenth_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(10);
  ReallyDumbRower rower = ReallyDumbRower();
  df->map(rower);
  sys.p(rower.getSum());
}




void df_to_string_array_testpmap() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(1);
  FieldsToArraysRower rower = FieldsToArraysRower();
  df->pmap(rower);
  sys.p(rower.getStringArray()->getSize());
}

void df_to_string_array_testmap() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(1);
  FieldsToArraysRower rower = FieldsToArraysRower();
  df->map(rower);
  sys.p(rower.getStringArray()->getSize());
}

void df_to_string_array_testpmap_half_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(2);
  FieldsToArraysRower rower = FieldsToArraysRower();
  df->pmap(rower);
  sys.p(rower.getStringArray()->getSize());
}

void df_to_string_array_testmap_half_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(2);
  FieldsToArraysRower rower = FieldsToArraysRower();
  df->map(rower);
  sys.p(rower.getStringArray()->getSize());
}

void df_to_string_array_testpmap_tenth_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(10);
  FieldsToArraysRower rower = FieldsToArraysRower();
  df->pmap(rower);
  sys.p(rower.getStringArray()->getSize());
}

void df_to_string_array_testmap_tenth_rows() {
  Sys sys;
  ModifiedDataFrame* df;
  df = create_dataframe_from_file(10);
  FieldsToArraysRower rower = FieldsToArraysRower();
  df->map(rower);
  sys.p(rower.getStringArray()->getSize());
}


int main(int argc, char **argv) {
    df_to_string_array_testmap_tenth_rows();
}