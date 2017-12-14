#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_remove_non_accessible_states, state_no_transition)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  fa_set_state_initial(selfFa, 0);
  fa_set_state_final(selfFa, 2);

  fa_add_transition(selfFa, 0, 'a', 1);
  fa_add_transition(selfFa, 1, 'a', 0);

  fa_remove_non_accessible_states(selfFa);
  ASSERT_EQ(2, selfFa->state_count);

  fa_destroy(selfFa);
}

TEST(fa_remove_non_accessible_states, state_w_transition)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  fa_set_state_initial(selfFa, 0);
  fa_set_state_final(selfFa, 2);

  fa_add_transition(selfFa, 0, 'a', 1);
  fa_add_transition(selfFa, 1, 'a', 0);
  fa_add_transition(selfFa, 2, 'a', 0);

  fa_remove_non_accessible_states(selfFa);
  ASSERT_EQ(2, selfFa->state_count);

  fa_destroy(selfFa);
}

TEST(fa_remove_non_accessible_states, state_accessible)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  fa_set_state_initial(selfFa, 0);
  fa_set_state_final(selfFa, 2);

  fa_add_transition(selfFa, 0, 'a', 1);
  fa_add_transition(selfFa, 1, 'a', 0);
  fa_add_transition(selfFa, 1, 'b', 2);
  fa_add_transition(selfFa, 2, 'a', 0);

  fa_remove_non_accessible_states(selfFa);
  ASSERT_EQ(3, selfFa->state_count);

  fa_destroy(selfFa);
}
