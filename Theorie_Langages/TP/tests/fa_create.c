#include "gtest/gtest.h"
#include "fa.h"

TEST(fa, create)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 0, 0);


}
