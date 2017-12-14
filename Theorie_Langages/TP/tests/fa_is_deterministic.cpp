#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_is_deterministic, are_deterministic)
{
  //tests on 5 deterministics automatons
  struct fa *selfDet1 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfDet1, 2, 3);
  fa_set_state_final(selfDet1, 0);
  fa_set_state_initial(selfDet1, 0);

  fa_add_transition(selfDet1, 0, 'a', 0);
  fa_add_transition(selfDet1, 0, 'b', 1);
  fa_add_transition(selfDet1, 1, 'a', 2);
  fa_add_transition(selfDet1, 1, 'b', 0);
  fa_add_transition(selfDet1, 2, 'a', 1);
  fa_add_transition(selfDet1, 2, 'b', 2);

  ASSERT_EQ(true, fa_is_deterministic(selfDet1));
  fa_destroy(selfDet1);

  struct fa *selfDet2 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfDet2, 3, 12);
  fa_set_state_final(selfDet2, 11);
  fa_set_state_initial(selfDet2, 0);

  fa_add_transition(selfDet2, 0, 'a', 2);
  fa_add_transition(selfDet2, 0, 'b', 1);
  fa_add_transition(selfDet2, 0, 'c', 5);
  fa_add_transition(selfDet2, 1, 'a', 3);
  fa_add_transition(selfDet2, 1, 'b', 2);
  fa_add_transition(selfDet2, 1, 'c', 6);
  fa_add_transition(selfDet2, 2, 'a', 4);
  fa_add_transition(selfDet2, 2, 'b', 3);
  fa_add_transition(selfDet2, 2, 'c', 7);
  fa_add_transition(selfDet2, 3, 'a', 5);
  fa_add_transition(selfDet2, 3, 'b', 4);
  fa_add_transition(selfDet2, 3, 'c', 8);
  fa_add_transition(selfDet2, 4, 'a', 6);
  fa_add_transition(selfDet2, 4, 'b', 5);
  fa_add_transition(selfDet2, 4, 'c', 9);
  fa_add_transition(selfDet2, 5, 'a', 7);
  fa_add_transition(selfDet2, 5, 'b', 6);
  fa_add_transition(selfDet2, 5, 'c', 10);
  fa_add_transition(selfDet2, 6, 'a', 8);
  fa_add_transition(selfDet2, 6, 'b', 7);
  fa_add_transition(selfDet2, 6, 'c', 11);
  fa_add_transition(selfDet2, 7, 'a', 9);
  fa_add_transition(selfDet2, 7, 'b', 8);
  fa_add_transition(selfDet2, 7, 'c', 11);
  fa_add_transition(selfDet2, 8, 'a', 10);
  fa_add_transition(selfDet2, 8, 'b', 9);
  fa_add_transition(selfDet2, 8, 'c', 11);
  fa_add_transition(selfDet2, 9, 'a', 11);
  fa_add_transition(selfDet2, 9, 'b', 10);
  fa_add_transition(selfDet2, 9, 'c', 11);
  fa_add_transition(selfDet2, 10, 'a', 11);
  fa_add_transition(selfDet2, 10, 'b', 11);
  fa_add_transition(selfDet2, 10, 'c', 11);
  fa_add_transition(selfDet2, 11, 'a', 11);
  fa_add_transition(selfDet2, 11, 'b', 11);
  fa_add_transition(selfDet2, 11, 'c', 11);

  ASSERT_EQ(true, fa_is_deterministic(selfDet2));
  fa_destroy(selfDet2);

  struct fa *selfDet3 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfDet3, 2, 1);
  fa_set_state_final(selfDet3, 0);
  fa_set_state_initial(selfDet3, 0);

  fa_add_transition(selfDet3, 0, 'a', 0);
  fa_add_transition(selfDet3, 0, 'b', 0);

  ASSERT_EQ(true, fa_is_deterministic(selfDet3));
  fa_destroy(selfDet3);


  struct fa *selfDet4 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfDet4, 3, 5);
  fa_set_state_final(selfDet4, 4);
  fa_set_state_initial(selfDet4, 1);

  fa_add_transition(selfDet4, 0, 'a', 0);
  fa_add_transition(selfDet4, 0, 'b', 0);
  fa_add_transition(selfDet4, 0, 'c', 0);
  fa_add_transition(selfDet4, 1, 'a', 2);
  fa_add_transition(selfDet4, 1, 'b', 0);
  fa_add_transition(selfDet4, 1, 'c', 0);
  fa_add_transition(selfDet4, 2, 'a', 0);
  fa_add_transition(selfDet4, 2, 'b', 3);
  fa_add_transition(selfDet4, 2, 'c', 0);
  fa_add_transition(selfDet4, 3, 'a', 0);
  fa_add_transition(selfDet4, 3, 'b', 0);
  fa_add_transition(selfDet4, 3, 'c', 4);
  fa_add_transition(selfDet4, 4, 'a', 2);
  fa_add_transition(selfDet4, 4, 'b', 0);
  fa_add_transition(selfDet4, 4, 'c', 4);

  ASSERT_EQ(true, fa_is_deterministic(selfDet4));
  fa_destroy(selfDet4);


  struct fa *selfDet5 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfDet5, 2, 3);
  fa_set_state_final(selfDet5, 2);
  fa_set_state_initial(selfDet5, 0);

  fa_add_transition(selfDet5, 0, 'a', 1);
  fa_add_transition(selfDet5, 0, 'b', 1);
  fa_add_transition(selfDet5, 1, 'a', 1);
  fa_add_transition(selfDet5, 1, 'b', 2);
  fa_add_transition(selfDet5, 2, 'a', 1);
  fa_add_transition(selfDet5, 2, 'b', 0);


  ASSERT_EQ(true, fa_is_deterministic(selfDet5));
  fa_destroy(selfDet5);

}

TEST(fa_is_deterministic, not_deterministics)
{
  //tests on 5 non-deterministics automatons
  struct fa *selfNDet1 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfNDet1, 2, 3);
  fa_set_state_final(selfNDet1, 0);
  fa_set_state_initial(selfNDet1, 0);

  fa_add_transition(selfNDet1, 0, 'a', 0);
  fa_add_transition(selfNDet1, 0, 'b', 1);
  fa_add_transition(selfNDet1, 1, 'a', 2);
  fa_add_transition(selfNDet1, 1, 'b', 0);
  fa_add_transition(selfNDet1, 2, 'a', 1);

  ASSERT_EQ(false, fa_is_deterministic(selfNDet1));
  fa_destroy(selfNDet1);

  struct fa *selfNDet2 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfNDet2, 2, 3);
  fa_set_state_final(selfNDet2, 0);

  fa_add_transition(selfNDet2, 0, 'a', 0);
  fa_add_transition(selfNDet2, 0, 'b', 1);
  fa_add_transition(selfNDet2, 1, 'a', 2);
  fa_add_transition(selfNDet2, 1, 'b', 0);
  fa_add_transition(selfNDet2, 2, 'a', 1);
  fa_add_transition(selfNDet2, 2, 'b', 2);

  ASSERT_EQ(false, fa_is_deterministic(selfNDet2));
  fa_destroy(selfNDet2);

  struct fa *selfNDet3 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfNDet3, 2, 3);
  fa_set_state_final(selfNDet3, 0);
  fa_set_state_initial(selfNDet3, 1);
  fa_set_state_initial(selfNDet3, 0);

  fa_add_transition(selfNDet3, 0, 'a', 0);
  fa_add_transition(selfNDet3, 0, 'b', 1);
  fa_add_transition(selfNDet3, 1, 'a', 2);
  fa_add_transition(selfNDet3, 1, 'b', 0);
  fa_add_transition(selfNDet3, 2, 'a', 1);
  fa_add_transition(selfNDet3, 2, 'b', 2);

  ASSERT_EQ(false, fa_is_deterministic(selfNDet3));
  fa_destroy(selfNDet3);

  struct fa *selfNDet4 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfNDet4, 0, 0);

  ASSERT_EQ(false, fa_is_deterministic(selfNDet4));
  //fa_destroy(selfNDet4);

  struct fa *selfNDet5 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfNDet5, 1, 1);
  fa_set_state_final(selfNDet5, 0);

  fa_add_transition(selfNDet5, 0, 'a', 0);

  ASSERT_EQ(false, fa_is_deterministic(selfNDet5));
  fa_destroy(selfNDet5);

}
