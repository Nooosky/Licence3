#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_is_complete, result)
{
  //Tests
  //deterministic automata
  //non deterministic but complete
  //non complete

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

  ASSERT_EQ(true, fa_is_complete(selfDet1));
  fa_destroy(selfDet1);

  struct fa *selfComp1 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfComp1, 2, 3);
  fa_set_state_final(selfComp1, 0);
  fa_set_state_initial(selfComp1, 0);

  fa_add_transition(selfComp1, 0, 'a', 0);
  fa_add_transition(selfComp1, 0, 'a', 1);
  fa_add_transition(selfComp1, 0, 'b', 1);
  fa_add_transition(selfComp1, 1, 'a', 2);
  fa_add_transition(selfComp1, 1, 'b', 0);
  fa_add_transition(selfComp1, 1, 'b', 1);
  fa_add_transition(selfComp1, 2, 'a', 1);
  fa_add_transition(selfComp1, 2, 'b', 2);

  ASSERT_EQ(true, fa_is_complete(selfComp1));
  fa_destroy(selfComp1);


  struct fa *selfNComp1 = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfNComp1, 2, 3);
  fa_set_state_final(selfNComp1, 0);
  fa_set_state_initial(selfNComp1, 0);

  fa_add_transition(selfNComp1, 0, 'a', 0);
  fa_add_transition(selfNComp1, 0, 'a', 1);
  fa_add_transition(selfNComp1, 0, 'b', 1);
  fa_add_transition(selfNComp1, 1, 'b', 0);
  fa_add_transition(selfNComp1, 1, 'b', 1);
  fa_add_transition(selfNComp1, 2, 'a', 1);
  fa_add_transition(selfNComp1, 2, 'b', 2);

  ASSERT_EQ(false, fa_is_complete(selfNComp1));
  fa_destroy(selfNComp1);

}
