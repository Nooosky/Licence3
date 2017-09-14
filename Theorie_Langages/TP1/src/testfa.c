#include "fa.h"


int main() {
    
    //Creation of a automaton
    struct fa *self = (struct fa *) malloc(sizeof(struct fa));
    fa_create(&self, 3, 3);

    //destruction of a automaton
    fa_destroy(&self);


    return 0;
}
