#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
