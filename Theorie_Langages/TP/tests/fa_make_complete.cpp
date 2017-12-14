#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(fa_make_complete, result)
{
  //Tests
  //Complete automata
  //deterministic automata
  //non complete automata
    //state_count
    //fa_is_complete

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

    ASSERT_EQ(-1, fa_make_complete(selfDet1));
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

    ASSERT_EQ(-1, fa_make_complete(selfComp1));
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

    ASSERT_EQ(0, fa_make_complete(selfNComp1));
    ASSERT_EQ(4, selfNComp1->state_count);
    ASSERT_EQ(10, fa_count_transitions(selfNComp1));
    ASSERT_EQ(true, fa_is_complete(selfNComp1));

    fa_destroy(selfNComp1);
}
