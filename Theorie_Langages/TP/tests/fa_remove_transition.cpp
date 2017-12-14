#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_remove_transition, conds)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));

  //Tests
  //from = 0 AND alpha <0 AND to = 0
  //from = 0 AND alpha > 26 AND to = 0
  //from = 0 AND alpha ok AND to = 0
  //from = 0 AND alpha <0 AND to > state_count
  //from = 0 AND alpha > 26 AND to > state_count
  //from = 0 AND alpha ok AND to > state_count
  //from = 0 AND alpha <0 AND to ok
  //from = 0 AND alpha > 26 AND to ok
  //from = 0 AND alpha ok AND to ok

  //from > state_count AND alpha <0 AND to = 0
  //from > state_count AND alpha >26 AND to = 0
  //from > state_count AND alpha ok AND to = 0
  //from > state_count AND alpha <0 AND to >state_count
  //from > state_count AND alpha >26 AND to > state_count
  //from > state_count AND alpha ok AND to > state_count
  //from > state_count AND alpha <0 AND to ok
  //from > state_count AND alpha >26 AND to ok
  //from > state_count AND alpha ok AND to ok

  //from ok AND alpha <0 AND to = 0
  //from ok AND alpha >26 AND to = 0
  //from ok AND alpha ok AND to = 0
  //from ok AND alpha <0 AND to >state_count
  //from ok AND alpha >26 AND to >state_count
  //from ok AND alpha ok AND to >state_count
  //from ok AND alpha <0 AND to ok
  //from ok AND alpha >26 AND to ok
  //from ok AND alpha ok AND to ok

  //alpha_count = 2
  //state_count = 3

  fa_create(selfFa, 2, 3);
  fa_add_transition(selfFa, 0, 'a', 0);

  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, '_', -1));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, '|', -1));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, 'a', -1));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, '_', 99));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, '|', 99));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, 'a', 99));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, '_', 0));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, '|', 0));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, -1, 'a', 0));

  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, '_', -1));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, '|', -1));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, 'a', -1));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, '_', 99));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, '|', 99));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, 'a', 99));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, '_', 0));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, '|', 0));
  ASSERT_EQ(-1, fa_remove_transition(selfFa, 99, 'a', 0));

  ASSERT_EQ(-2, fa_remove_transition(selfFa, 1, '_', -1));
  ASSERT_EQ(-2, fa_remove_transition(selfFa, 1, '|', -1));
  ASSERT_EQ(-3, fa_remove_transition(selfFa, 1, 'a', -1));
  ASSERT_EQ(-2, fa_remove_transition(selfFa, 1, '_', 99));
  ASSERT_EQ(-2, fa_remove_transition(selfFa, 1, '|', 99));
  ASSERT_EQ(-3, fa_remove_transition(selfFa, 1, 'a', 99));
  ASSERT_EQ(-2, fa_remove_transition(selfFa, 1, '_', 0));
  ASSERT_EQ(-2, fa_remove_transition(selfFa, 1, '|', 0));
  ASSERT_EQ(-4, fa_remove_transition(selfFa, 1, 'a', 1));

  ASSERT_EQ(0, fa_remove_transition(selfFa, 0, 'a', 0));
  ASSERT_EQ(-4, fa_remove_transition(selfFa, 0, 'a', 0));

  fa_destroy(selfFa);
}
