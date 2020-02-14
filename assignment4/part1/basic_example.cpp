#include "../helper.h"
#include "dataframe.h" 

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
        Sys s;
        s.p(r.get_bool(x));
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
  }
};


void test() {
  Sys st;
  Schema s("II");

  DataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }
  st.t_true(df.get_int((size_t)0,1) ==  1);
  st.p(df.nrows());
  st.OK("fkkd");
}

void schema_test() {
  Schema s("IFBS");
  s.add_column('I', new String("My Column"));
  s.add_row(new String("ROW ONE"));
  Sys st;


  st.t_true(s.length() == 1);
  st.OK("1");
  st.t_true(s.width() == 5);
  st.OK("2");
  st.t_true(s.row_name(0)->equals(new String("ROW ONE")));
  st.OK("3");
  st.t_true(s.col_name(4)->equals(new String("My Column")));
  st.OK("4");
  st.t_true(s.col_type(3) == 'S');
  st.OK("5");
  st.t_true(s.col_idx("My Column") == 4);
  st.OK("6");
  st.t_true(s.col_idx("My ") == -1);
  st.OK("7");
  st.t_true(s.row_idx("ROW ONE") == 0);
  st.OK("8");
  st.t_true(s.row_idx("ROW ") == -1);
}

void row_test() {
  Schema s("IFBS");
  Row r(s);
  Sys st;

  r.set(0,12);
  r.set(1, float(12.01));
  r.set(2, true);
  r.set(3, new String("You did it buddy"));
  st.t_true(r.get_int(0) == 12);
  st.OK("1");
  st.t_true(r.get_float(1) >= 12.01 - .001 && r.get_float(1) <= 12.01 + .001);
  st.OK("2");
  st.t_true(r.get_bool(2) == true);
  st.OK("3");
  st.t_true(r.get_string(3)->equals(new String("You did it buddy")));
  st.OK("4");
  st.t_true(r.width() == 4);
  st.OK("5");
}

// column_type testing
void column_methods_test() {
    Sys st;
    BoolColumn* b = new BoolColumn();
    Column* b2 = static_cast<Column*>(b);
    b2->push_back(true);
    b2->push_back(false);
    st.t_true(b->get(0));
    st.OK("1");
    st.t_false(b->get(1));
    st.OK("2");
    b->set(0, false);
    st.t_false(b->get(0));
    st.OK("3");
    st.t_true(b->size() == 2);
    st.OK("4");
}


void rower_filter_dataframe_test() {
  Sys st;
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
  st.t_true(df2->get_int(0, 0) == df.get_int(0, 1));
  st.p(df2->nrows());
  st.t_true(df2->nrows() == 1);
  df2->add_row(r);
  st.t_true(df2->get_int(0, 1) == 2);
}


void copying_dataframe_test() {
  Sys st;
  Schema s("II");
  DataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }

  DataFrame df2(df);
  st.t_true(df2.nrows() == 0);
  st.t_true(df2.ncols() == 2);
}


int main(int argc, char **argv) {
    rower_filter_dataframe_test();
}
