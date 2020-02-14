#include "../helper.h"
#include "dataframe.h" 

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
  st.OK("fkkd");
}



int main(int argc, char **argv) {
    test();
}
