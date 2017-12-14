#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_remove_state, conds)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  //Tests
  //state < 0
  //state > state_count
  //state ok

  ASSERT_EQ(-1, fa_remove_state(selfFa, -1));
  ASSERT_EQ(-1, fa_remove_state(selfFa, 99));
  ASSERT_EQ(0, fa_remove_state(selfFa, 0));

  fa_destroy(selfFa);
}


TEST(fa_remove_state, result)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 4);
  fa_set_state_initial(selfFa, 1);
  fa_set_state_final(selfFa, 2);

  fa_add_transition(selfFa, 0, 'a', 0);

  fa_remove_state(selfFa, 0);

  ASSERT_EQ(3, selfFa->state_count);

  //Test if the transition is well deleted
  ASSERT_EQ(-4, fa_remove_transition(selfFa, 0, 'a', 0));

  fa_destroy(selfFa);
}
