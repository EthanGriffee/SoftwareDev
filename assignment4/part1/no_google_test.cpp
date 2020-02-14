#include "../helper.h"
#include "dataframe.h" 

void copying_dataframe_test() {
  Sys sys;
  Schema s("II");
  DataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }

  DataFrame df2(df);
  return;
  sys.t_true(df2.nrows() == 0);
  sys.t_true(df2.ncols() == 2);
}

int main(int argc, char **argv) {
    copying_dataframe_test();
}
