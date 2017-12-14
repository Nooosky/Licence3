#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}


TEST(fa, create)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));

  EXPECT_EQ(-1, fa_create(selfFa, 0, 0));
  EXPECT_EQ(-1, fa_create(selfFa, 1, 0));
  EXPECT_EQ(-2, fa_create(selfFa, -1, 0));

  EXPECT_EQ(0, fa_create(selfFa, 0, 1));
  EXPECT_EQ(0, fa_create(selfFa, 1, 1));

  fa_destroy(selfFa);
}
