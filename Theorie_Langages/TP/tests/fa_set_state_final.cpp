#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_set_state_final, conds)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  //Tests
  //state < -1
  //state > state_count
  //state ok

  ASSERT_EQ(-1, fa_set_state_final(selfFa, -9));
  ASSERT_EQ(-1, fa_set_state_final(selfFa, 99));
  ASSERT_EQ(0, fa_set_state_final(selfFa, 1));

  fa_destroy(selfFa);
}

TEST(fa_set_state_final, result)
{

    struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
    fa_create(selfFa, 2, 2);
    fa_set_state_final(selfFa, 1);

    ASSERT_EQ(1, selfFa->states[1].is_final);

    fa_destroy(selfFa);
}
