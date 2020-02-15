#include "../helper.h"
#include "modified_dataframe.h" 
#include <gtest/gtest.h>

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

/*******************************************************************************
 *  Rower::
 *  A Rower that only wastes time, used to show that it is faster
 */
class ReallyDumbRower : public Rower {
 public:
    int sum;

    ReallyDumbRower() { sum = 0;}

  virtual bool accept(Row& r) {
    int sum = 0;
    for (int x = 0; x < 10000000; x++) {
        sum += 1;
    }
    return true;
  }
 
  /** Once traversal of the data frame is complete the rowers that were
      split off will be joined.  There will be one join per split. The
      original object will be the last to be called join on. The join method
      is reponsible for cleaning up memory. */
  virtual void join_delete(Rower* other) {
      ReallyDumbRower* r = dynamic_cast<ReallyDumbRower*> (other);
      Sys s;
      s.p(this->sum + r->sum);
  }
};


void really_dumb_testpmap() {
    Schema s("II");

  ModifiedDataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }
  GT_EQUALS(df.get_int((size_t)0,1), 1);
  ReallyDumbRower rower = ReallyDumbRower();
  df.pmap(rower);
}
TEST(PmapTest, really_dumb_testpmap){ ASSERT_EXIT_ZERO(really_dumb_testpmap); }

void really_dumb_testmap() {
    Schema s("II");

  ModifiedDataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }
  GT_EQUALS(df.get_int((size_t)0,1), 1);
  ReallyDumbRower rower = ReallyDumbRower();
  df.map(rower);
}

TEST(mapTest, really_dumb_testmap){ ASSERT_EXIT_ZERO(really_dumb_testmap); }


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
