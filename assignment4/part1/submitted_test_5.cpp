#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")


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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
