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
