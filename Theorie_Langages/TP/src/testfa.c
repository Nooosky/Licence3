#include <stdlib.h>
#include <stdio.h>

#include "fa.h"

int main() {

    FILE *file = NULL;
    struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));

    //Creation of a automaton
    printf("creation de l'automate\n");
    fa_create(selfFa, 2, 5);

    //make states initials
    printf("definie les etats initiaux\n");
    fa_set_state_initial(selfFa, 0);
    fa_set_state_initial(selfFa, 1);

    //make states finals
    printf("definie les etats finaux\n");
    fa_set_state_final(selfFa, 1);
    fa_set_state_final(selfFa, 4);

    // add transitions to automaton
    printf("ajout des transitions\n");
    fa_add_transition(selfFa, 0, 'a', 1);
    fa_add_transition(selfFa, 0, 'a', 2);
    fa_add_transition(selfFa, 0, 'a', 3);
    fa_add_transition(selfFa, 1, 'b', 3);
    fa_add_transition(selfFa, 2, 'a', 3);
    fa_add_transition(selfFa, 2, 'b', 4);
    fa_add_transition(selfFa, 3, 'a', 3);
    fa_add_transition(selfFa, 3, 'b', 4);
    fa_add_transition(selfFa, 4, 'a', 4);

    //count transition
    printf("number transitions : %zu\n", fa_count_transitions(selfFa));

    // remove transitions to automaton
    printf("supprime des transitions\n");
    fa_remove_transition(selfFa, 0, 'a', 2);

    //count transition
    printf("number transitions : %zu\n", fa_count_transitions(selfFa));

    //count state
    printf("number states : %zu\n", selfFa->state_count);

    // remove states
    printf("supprime un etat\n");
    fa_remove_state(selfFa, 1);

    //count state
    printf("number states : %zu\n", selfFa->state_count);


    //if automaton is deterministic
    printf("if automaton is deterministic : %s\n", fa_is_deterministic(selfFa) ? "true" : "false");

    //if automaton is complete
    printf("if automaton is complete : %s\n", fa_is_complete(selfFa) ? "true" : "false");

    //make automaton complete
    printf("complete un automate\n");
    fa_make_complete(selfFa);

    //if automaton is complete
    printf("if automaton is complete : %s\n", fa_is_complete(selfFa) ? "true" : "false");


    struct graph *selfGraph = (struct graph *) malloc(sizeof(struct graph));

    //create graph with an automaton
    printf("cree un graph a partir d'un automate\n");
    graph_create_from_fa(selfGraph, selfFa, false);
    for (size_t i = 0; i < selfGraph->node_count; ++i)
    {
      printf("%zu: ", selfGraph->nodes[i].number);
      for(size_t j = 0; j < selfGraph->nodes[i].nb_adjacent; ++j)
      {
        printf("%zu,", selfGraph->nodes[i].adjacent_nodes[j].number);
      }
      printf("\n");
    }

    //tel state who are visited with depth first search
    bool tabBool[selfGraph->node_count];
    for (size_t i = 0; i < selfGraph->node_count; ++i)
      tabBool[i] = false;
    graph_depth_first_search(selfGraph, 0, &tabBool);
    for (size_t i = 0; i < selfGraph->node_count; ++i)
      printf("%zu: %s, ", i, tabBool[i] ? "true" : "false");
    printf("\n");

    // if there is path between two states
    printf("if there is path between two states : %s\n", graph_has_path(selfGraph, 1, 4) ? "true" : "false");

    // if language of graph is empty
    printf("if language of graph is empty : %s\n", fa_is_language_empty(selfFa) ? "true" : "false");

    // remove non accessible and non co accessible state
    printf("remove non accessible and non co accessible state\n");
    fa_remove_non_accessible_states(selfFa);
    fa_remove_non_co_accessible_states(selfFa);

    printf("remove non accessible and non co accessible state\n");
    struct fa *selfFa1 = (struct fa *) malloc(sizeof(struct fa));
    struct fa *selfFa2 = (struct fa *) malloc(sizeof(struct fa));
    struct fa *selfFa3 = (struct fa *) malloc(sizeof(struct fa));
    fa_create(selfFa2, 2, 3);
    fa_set_state_initial(selfFa2, 0);
    fa_set_state_final(selfFa2, 2);
    fa_add_transition(selfFa2, 0, 'a', 1);
    fa_add_transition(selfFa2, 1, 'a', 0);
    fa_add_transition(selfFa2, 1, 'b', 2);
    fa_add_transition(selfFa2, 2, 'b', 2);

    fa_create(selfFa3, 2, 3);
    fa_set_state_initial(selfFa3, 0);
    fa_set_state_initial(selfFa3, 1);
    fa_set_state_final(selfFa3, 2);
    fa_add_transition(selfFa3, 0, 'a', 1);
    fa_add_transition(selfFa3, 1, 'a', 2);
    fa_add_transition(selfFa3, 1, 'b', 2);
    fa_add_transition(selfFa3, 2, 'b', 1);

    printf("product of two automatons\n");
    fa_create_product(selfFa1, selfFa2, selfFa3);


    // print automaton in file
    printf("dessine l'automate dans un .txt\n");
    fa_pretty_print(selfFa1, file, "txt/automaton.txt");

    // print automaton in file .dot
    printf("dessine l'automate dans un .dot\n");
    fa_dot_print(selfFa1, file);

    //destruction of a automaton
    printf("detruie l'automate\n");
    fa_destroy(selfFa);

    //destruction of a graph
    printf("detruie le graph\n");
    graph_destroy(selfGraph);

    return 0;
}
