#include "dataframe.h" 

void test() {
  Schema s("II");

  DataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }
  exit(0);
}

int main(int argc, char **argv) {
    test();
}
