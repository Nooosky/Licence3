#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_destroy, good_return)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  ASSERT_EQ(0, fa_destroy(selfFa));
  //fa_destroy(selfFa);
}
