#include <gtest/gtest.h>
#include "dataframe.h" 

#define GT_TRUE(a)   ASSERT_EQ((a),true)
#define GT_FALSE(a)  ASSERT_EQ((a),false)
#define GT_EQUALS(a, b)   ASSERT_EQ(a, b)
#define CS4500_ASSERT_EXIT_ZERO(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(0), ".*");
#define CS4500_ASSERT_EXIT_ONE(a)  \
  ASSERT_EXIT(a(), ::testing::ExitedWithCode(1), ".*");
 
// tests column as int
void column_as_int_test() {
    StringColumn* c = new StringColumn();
    ASSERT_EQ(c->as_int(), nullptr);
    IntColumn* i = new StringColumn();
    ASSERT_EQ(i->as_int(), i);
}