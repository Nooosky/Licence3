#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_count_transitions, result)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  //Tests
  //0 transitions
  //1 transition
  //2x la meme transition


  ASSERT_EQ(0, fa_count_transitions(selfFa));

  fa_add_transition(selfFa, 0, 'a', 0);
  ASSERT_EQ(1, fa_count_transitions(selfFa));

  fa_add_transition(selfFa, 0, 'a', 0);
  ASSERT_EQ(1, fa_count_transitions(selfFa));

  fa_add_transition(selfFa, 0, 'a', 1);
  ASSERT_EQ(2, fa_count_transitions(selfFa));

  fa_destroy(selfFa);
}
