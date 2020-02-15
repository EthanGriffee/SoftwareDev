#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

/*******************************************************************************
 *  Rower::
 *  A Rower that only displays rows where all bool values are true
 */
class OnlyTrueRower : public Rower {
 public:
  /** This method is called once per row. The row object is on loan and
      should not be retained as it is likely going to be reused in the next
      call. The return value is used in filters to indicate that a row
      should be kept. */
  virtual bool accept(Row& r) {
    for (int x = 0; x < r.width(); x++) {
      if (r.col_type(x) == 'B' && !r.get_bool(x)) {
        return  false;
      }
    }
    return true;
  }
 
  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  virtual void join_delete(Rower* other) {
    delete other;
  }
};

 
// tests column as int
void column_as_int_test() {
    StringColumn* c = new StringColumn();
    GT_TRUE(c->as_int() == nullptr);
    IntColumn* i = new IntColumn();
    GT_TRUE(i->as_int() == i);
    exit(0);
}

TEST(ColumnTest, column_as_int_test){ ASSERT_EXIT_ZERO(column_as_int_test); }


// tests column as int
void column_as_string_test() {
    StringColumn* c = new StringColumn();
    GT_TRUE(c->as_int() == nullptr);
    IntColumn* i = new IntColumn();
    GT_TRUE(i->as_int() == i);
    exit(0);
}

TEST(ColumnTest, column_as_string_test){ ASSERT_EXIT_ZERO(column_as_string_test); }

// column_type testing
void column_type_test() {
    StringColumn* c = new StringColumn();
    IntColumn* i = new IntColumn();
    BoolColumn* b = new BoolColumn();
    FloatColumn* f = new FloatColumn();
    Column* f2 = static_cast<Column*>(f);
    GT_TRUE(c->get_type() == 'S');
    GT_TRUE(i->get_type() == 'I');
    GT_TRUE(b->get_type() == 'B');
    GT_TRUE(f->get_type() == 'F');
    GT_TRUE(f2->get_type() == 'F');

    exit(0);
}

TEST(ColumnTest, column_type_test){ ASSERT_EXIT_ZERO(column_type_test); }


// column_type testing
void column_methods_test() {
    BoolColumn* b = new BoolColumn();
    Column* b2 = static_cast<Column*>(b);
    b2->push_back(true);
    b2->push_back(false);
    GT_TRUE(b->get(0));
    GT_FALSE(b->get(1));
    b->set(0, false);
    GT_FALSE(b->get(0));
    GT_TRUE(b->size() == 2);
    exit(0);
}

TEST(ColumnTest, column_methods_test){ ASSERT_EXIT_ZERO(column_methods_test); }



void copying_dataframe_test() {
  Schema s("II");
  DataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }

  DataFrame df2(df);
  GT_TRUE(df2.nrows() == 0);
  GT_TRUE(df2.ncols() == 2);
  exit(0);
}

TEST(DataFrameTest, copying_dataframe_test){ ASSERT_EXIT_ZERO(copying_dataframe_test); }

void get_dataframe_test() {
  Schema s("IBS");
  DataFrame df(s);
  Row  r(df.get_schema());
  r.set(0,1);
  r.set(1, true);
  r.set(2, new String("Hello"));
  df.add_row(r);
  r.set(0,2);
  r.set(1, false);
  r.set(2, new String("World"));
  df.add_row(r);
  r.set(0,3);
  r.set(1, false);
  r.set(2, new String("Welcome"));
  df.add_row(r);


  GT_TRUE(df.nrows() == 3);
  GT_TRUE(df.ncols() == 3);
  GT_TRUE(df.get_bool(1,0));
  GT_TRUE(df.get_string(2,1)->equals(new String("World")));
  GT_TRUE(df.get_int(0,2) == 3);
  exit(0);
}

TEST(DataFrameTest, get_dataframe_test){ ASSERT_EXIT_ZERO(get_dataframe_test); }

void fill_row_dataframe_test() {
  Schema s("IBS");
  DataFrame df(s);
  Row  r(df.get_schema());
  r.set(0,1);
  r.set(1, true);
  r.set(2, new String("Hello"));
  df.add_row(r);
  r.set(0,2);
  r.set(1, false);
  r.set(2, new String("World"));
  df.add_row(r);
  r.set(0,3);
  r.set(1, false);
  r.set(2, new String("Welcome"));
  df.add_row(r);

  df.fill_row(1, r);
  GT_TRUE(r.get_int(0) == 2);
  GT_TRUE(r.get_bool(1) == false);
  GT_TRUE(r.get_string(2)->equals(new String("World")));
  GT_TRUE(r.width() == 3);
  exit(0);
}

TEST(DataFrameTest, fill_row_dataframe_test){ ASSERT_EXIT_ZERO(fill_row_dataframe_test); }


void schema_test() {
  Schema s("IFBS");
  s.add_column('I', new String("My Column"));
  s.add_row(new String("ROW ONE"));



  GT_TRUE(s.length() == 1);
  GT_TRUE(s.width() == 5);
  GT_TRUE(s.row_name(0)->equals(new String("ROW ONE")));
  GT_TRUE(s.col_name(4)->equals(new String("My Column")));
  GT_TRUE(s.col_type(3) == 'S');
  GT_TRUE(s.col_type(2) == 'B');
  GT_TRUE(s.col_type(1) == 'F');
  GT_TRUE(s.col_type(0) == 'I');
  GT_TRUE(s.col_idx("My Column") == 4);
  GT_TRUE(s.col_idx("My ") == -1);
  GT_TRUE(s.row_idx("ROW ONE") == 0);
  GT_TRUE(s.row_idx("ROW ") == -1);
  exit(0);
}

TEST(SchemaTest, schema_test){ ASSERT_EXIT_ZERO(schema_test); }

void row_test() {
  Schema s("IFBS");
  Row r(s);

  r.set(0,12);
  r.set(1, float(12.01));
  r.set(2, true);
  r.set(3, new String("You did it buddy"));
  GT_TRUE(r.get_int(0) == 12);
  GT_TRUE(r.get_float(1) >= 12.01 - .001 && r.get_float(1) <= 12.01 + .001);
  GT_TRUE(r.get_bool(2) == true);
  GT_TRUE(r.get_string(3)->equals(new String("You did it buddy")));
  GT_TRUE(r.width() == 4);
  exit(0);
}

TEST(RowTest, row_test){ ASSERT_EXIT_ZERO(row_test); }

void rower_filter_dataframe_test() {
  Schema s("IBB");
  DataFrame df(s);
  Row  r(df.get_schema());
  r.set(0,1);
  r.set(1, false);
  r.set(2, true);
  df.add_row(r);
  r.set(0, 0);
  r.set(1, true);
  r.set(2, true);
  df.add_row(r);
  r.set(0, 2);
  r.set(0, true);
  r.set(1, false);
  df.add_row(r);

  OnlyTrueRower rower;
  DataFrame* df2 = df.filter(rower);

  GT_TRUE(df2->get_int(0, 0) == df.get_int(0, 1));
  GT_TRUE(df2->nrows() == 1);
  df2->add_row(r);
  GT_TRUE(df2->get_int(0, 1) == 2);
  exit(0);
}

TEST(DataFrameTest, rower_filter_dataframe_test){ ASSERT_EXIT_ZERO(rower_filter_dataframe_test); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}