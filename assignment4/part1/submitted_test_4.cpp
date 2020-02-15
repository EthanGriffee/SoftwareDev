#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")



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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
