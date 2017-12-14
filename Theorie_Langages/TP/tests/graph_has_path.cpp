#include "gtest/gtest.h"

extern "C"
{
    #include "fa.h"
}

TEST(graph_has_path, conds)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  fa_set_state_initial(selfFa, 0);
  fa_set_state_final(selfFa, 2);

  fa_add_transition(selfFa, 1, 'a', 2);
  fa_add_transition(selfFa, 2, 'a', 2);

  struct graph *selfGraph = (struct graph *) malloc(sizeof(struct graph));

  graph_create_from_fa(selfGraph, selfFa, false);


  ASSERT_EQ(false, graph_has_path(selfGraph, -1, 0));
  ASSERT_EQ(false, graph_has_path(selfGraph, 0, -1));
  ASSERT_EQ(true, graph_has_path(selfGraph, 1, 2));

  fa_destroy(selfFa);

}


TEST(graph_has_path, result)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  fa_set_state_initial(selfFa, 0);
  fa_set_state_final(selfFa, 2);

  fa_add_transition(selfFa, 0, 'a', 1);
  fa_add_transition(selfFa, 1, 'a', 2);
  fa_add_transition(selfFa, 2, 'a', 2);

  struct graph *selfGraph = (struct graph *) malloc(sizeof(struct graph));

  graph_create_from_fa(selfGraph, selfFa, false);

  ASSERT_EQ(true, graph_has_path(selfGraph, 0, 1));
  ASSERT_EQ(true, graph_has_path(selfGraph, 1, 2));
  ASSERT_EQ(true, graph_has_path(selfGraph, 0, 2));

  fa_destroy(selfFa);

}
