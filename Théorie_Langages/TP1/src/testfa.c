#include <stdio.h>
#include <stdbool.h>


struct state {          //state structure
    bool is_initial;
    bool is_final;
};

struct fa{
    size_t alpha_count;     //size of the alphabet
    size_t state_count;     //number of states of the automaton

    struct state *states;   //stores the states of the automaton

    struct state_set **transitions;
};


//linked list
struct state_node {
    size_t state;
    struct state_node *next;    //next node
};


struct state_set {
    struct state_node *first;   //first node
};

int main() {
    
    //Creation of a automaton
    struct fa self = (struct fa) {.state_count = 3, .alpha_count = 3};
    fa_create(&self, 3, 3);

    printf("Hello, World!\n");
    return 0;
}
