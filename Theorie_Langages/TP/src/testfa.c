#include <stdlib.h>
#include <stdio.h>

#include "fa.h"

int main() {

    FILE *file = NULL;
    struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));

    //Creation of a automaton
    fa_create(selfFa, 2, 5);

    //make states initials
    fa_set_state_initial(selfFa, 0);
    fa_set_state_initial(selfFa, 1);

    //make states finals
    fa_set_state_final(selfFa, 1);
    fa_set_state_final(selfFa, 4);

    // add transitions to automaton
    fa_add_transition(selfFa, 0, 'a', 1);
    fa_add_transition(selfFa, 0, 'a', 2);
    fa_add_transition(selfFa, 0, 'a', 3);
    fa_add_transition(selfFa, 1, 'b', 3);
    fa_add_transition(selfFa, 2, 'a', 3);
    fa_add_transition(selfFa, 2, 'b', 4);
    fa_add_transition(selfFa, 3, 'a', 3);
    fa_add_transition(selfFa, 3, 'b', 4);
    fa_add_transition(selfFa, 4, 'a', 4);

    // remove transitions to automaton
    fa_remove_transition(selfFa, 4, 'a', 4);
    fa_remove_transition(selfFa, 2, 'a', 3);

    //count transition
    printf("number transitions : %d\n", (int)fa_count_transitions(selfFa));

    // remove states
    fa_remove_state(selfFa, 2);

    //count state
    printf("number states : %d\n", (int)selfFa->state_count);

    //if automaton is deterministic
    printf("is deterministic : %s\n", fa_is_deterministic(selfFa) ? "true" : "false");

    //if automaton is complete
    printf("is complete : %s\n", fa_is_complete(selfFa) ? "true" : "false");

    //make automaton complete
    fa_make_complete(selfFa);

    //if automaton is complete
    printf("is complete : %s\n", fa_is_complete(selfFa) ? "true" : "false");

    // print automaton in file
    fa_pretty_print(selfFa, file);

    // print automaton in file .dot
    fa_dot_print(selfFa, file);


    struct graph *selfGraph = (struct graph *) malloc(sizeof(struct graph));

    //create graph with an automaton
    graph_create_from_fa(selfGraph, selfFa, false);

    //destruction of a automaton
    fa_destroy(selfFa);

    //destruction of a graph
    graph_destroy(selfGraph);

    return 0;
}
