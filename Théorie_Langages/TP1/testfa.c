#include <stdio.h>
#include <stdlib.h>

struct fa {
    size_t alpha_count;
    size_t state_count;
    bool *initial_states;
    bool *final_states;
    struct state *states;
    struct state_set **transitions;
};

struct state {
    bool is_initial;
    bool is_final;
};

// dynamic array
struct state_set {
    size_t size;
    size_t capacity;
    size_t *states;
};

// linked list 
struct state_node {
    size_t state;
    struc state_node *next;
};

struct state_set {
    struct state_node *first;
};

int main () 
{




    return 0;
}