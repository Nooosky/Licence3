#include <stdlib.h>
#include <stdio.h>

#include "fa.h"

int main() {

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

    // afficher l'utomate
    fa_pretty_print(self, NULL);

    //destruction of a automaton
    fa_destroy(self);

    return 0;
}
