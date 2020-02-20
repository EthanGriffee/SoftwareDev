#include "modified_dataframe.h"

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
        sum = sum + r->sum;
  }

  size_t getSum() {
    return sum;
  }
};


void really_dumb_testpmap() {
    Sys sys;
    Schema s("II");

  ModifiedDataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }
  sys.t_true(df.get_int((size_t)0,1) == 1);
  ReallyDumbRower rower = ReallyDumbRower();
  df.pmap(rower);
  sys.p(rower.getSum());
}

void really_dumb_testmap() {
    Sys sys;
  Schema s("II");

  ModifiedDataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }
  sys.t_true(df.get_int((size_t)0,1) == 1);
  ReallyDumbRower rower = ReallyDumbRower();
  df.map(rower);
  sys.p(rower.getSum());
}


int main(int argc, char **argv) {
    really_dumb_testmap();
}
