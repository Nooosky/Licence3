#include <stdlib.h>
#include <stdio.h>

#include "fa.h"

int main() {

    struct fa *self = (struct fa *) malloc(sizeof(struct fa));

    
    //Creation of a automaton
    fa_create(&self, 3, 3);

    //destruction of a automaton
    fa_destroy(&self);


    return 0;
}
