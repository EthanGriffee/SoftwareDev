#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*")

void test() {
  Schema s("IS");
  s.add_column('F', new String("Grade"));
  s.add_column('B', new String("Attendance"));
  s.add_row(new String("Divit"));
  s.add_row(new String("Ethan"));

  DataFrame df(s);
  Row r(df.get_schema());
  r.set(0,1);
  r.set(1, new String("Math"));
  r.set(2, float(96.69));
  r.set(3, true);
  df.add_row(r);

  Row r2(df.get_schema());
  r2.set(0,2);
  r2.set(1, new String("Software Dev"));
  r2.set(2, float(95));
  r2.set(3, false);
  df.add_row(r2);

  DataFrame df2(df);

  Schema s2 = df2.get_schema();

  GT_EQUALS(df.get_int(0,0), 1);
  GT_TRUE(df.get_string(1,0)->equals(new String("Math")));
  GT_TRUE(df.get_bool(3,0));
  GT_TRUE(s.length() == 2);
  GT_TRUE(s.width() == 4);
  GT_EQUALS(s2.col_idx("Grade"), 2);
  GT_TRUE(s2.col_name(3)->equals(new String("Attendance")));
  GT_EQUALS(s2.col_type(1), 'S');
  GT_TRUE(s2.length() == 0);
  GT_TRUE(s2.width() == 4);
  exit(0);
}

TEST(a4, t1){ ASSERT_EXIT_ZERO(test); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
