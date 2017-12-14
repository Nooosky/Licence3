#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}


TEST(fa_create, conds)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));

  EXPECT_EQ(-1, fa_create(selfFa, 0, 0));
  EXPECT_EQ(-1, fa_create(selfFa, 1, 0));
  EXPECT_EQ(-2, fa_create(selfFa, -1, 0));

  EXPECT_EQ(0, fa_create(selfFa, 0, 1));
  EXPECT_EQ(0, fa_create(selfFa, 1, 1));

  fa_destroy(selfFa);
}

TEST(fa_create, result)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  ASSERT_EQ(2, selfFa->alpha_count);
  ASSERT_EQ(3, selfFa->state_count);
  

  fa_destroy(selfFa);
}
