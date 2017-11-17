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
    fa_remove_transition(selfFa, 4, 'a', 4);
    fa_remove_transition(selfFa, 2, 'a', 3);

    //count transition
    printf("number transitions : %zu\n", fa_count_transitions(selfFa));

    //count state
    printf("number states : %zu\n", selfFa->state_count);

    // remove states
    printf("supprime un etat\n");
    fa_remove_state(selfFa, 2);

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

    // print automaton in file
    printf("dessine l'automate dans un .txt\n");
    fa_pretty_print(selfFa, file);

    // print automaton in file .dot
    printf("dessine l'automate dans un .dot\n");
    fa_dot_print(selfFa, file);



    struct graph *selfGraph = (struct graph *) malloc(sizeof(struct graph));

    //create graph with an automaton
    printf("cree un graph a partir d'un automate\n");
    graph_create_from_fa(selfGraph, selfFa, false);

    // if there is path between two states
    printf("if there is path between two states : %s\n", graph_has_path(selfGraph, 1, 4) ? "true" : "false");

    // if language of graph is empty
    printf("if language of graph is empty : %s\n", fa_is_language_empty(selfFa) ? "true" : "false");

    // remove non accessible and non co accessible state
    printf("remove non accessible and non co accessible state\n");
    fa_remove_non_accessible_states(selfFa);
    fa_remove_non_co_accessible_states(selfFa);

    //destruction of a automaton
    printf("detruie l'automate\n");
    fa_destroy(selfFa);

    //destruction of a graph
    printf("detruie le graph\n");
    graph_destroy(selfGraph);

    return 0;
}
