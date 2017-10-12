#include <stdlib.h>
#include <stdio.h>

#include "fa.h"

int main() {

    FILE *file = NULL;
    struct fa *self = (struct fa *) malloc(sizeof(struct fa));

    //Creation of a automaton
    fa_create(self, 2, 5);

    //make states initials
    fa_set_state_initial(self, 0);
    fa_set_state_initial(self, 1);

    //make states finals
    fa_set_state_final(self, 1);
    fa_set_state_final(self, 4);

    // add transitions to automaton
    fa_add_transition(self, 0, 'a', 1);
    fa_add_transition(self, 0, 'a', 2);
    fa_add_transition(self, 0, 'a', 3);
    fa_add_transition(self, 1, 'b', 3);
    fa_add_transition(self, 2, 'a', 3);
    fa_add_transition(self, 2, 'b', 4);
    fa_add_transition(self, 3, 'a', 3);
    fa_add_transition(self, 3, 'b', 4);
    fa_add_transition(self, 4, 'a', 4);

    // remove transitions to automaton
    fa_remove_transition(self, 4, 'a', 4);
    fa_remove_transition(self, 2, 'a', 3);

    //count transition
    printf("number transitions : %d\n", (int)fa_count_transitions(self));

    // remove states
    fa_remove_state(self, 2);

    //count state
    printf("number states : %d\n", self->state_count);

    //if automaton is deterministic
    printf("is deterministic : %s\n", fa_is_deterministic(self) ? "true" : "false");

    //if automaton is complete
    printf("is complete : %s\n", fa_is_complete(self) ? "true" : "false");

    //make automaton complete
    fa_make_complete(self);

    //if automaton is complete
    printf("is complete : %s\n", fa_is_complete(self) ? "true" : "false");

    // print automaton in file
    fa_pretty_print(self, file);

    // print automaton in file .dot
    fa_dot_print(self, file);

    //destruction of a automaton
    fa_destroy(self);

    return 0;
}
