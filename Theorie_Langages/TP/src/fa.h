#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct state {//state structure
    bool is_initial;
    bool is_final;
};

struct fa{
    size_t alpha_count;     //size of the alphabet
    size_t state_count;     //number of states of the automaton

    struct state *states;   //stores the states of the automaton

    struct state_set **transitions;
};

struct state_set {
    size_t size;
    size_t capacity;
    size_t *states;
};

// automaton creation
void fa_create(struct fa *self, size_t alpha_count, size_t state_count);

// automaton deletion
void fa_destroy(struct fa *self);

// make a state initial
void fa_set_state_initial(struct fa *self, size_t state);

// make a state final
void fa_set_state_final(struct fa *self, size_t state);

// add a transition to the automaton
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to);

// print an automaton
void fa_pretty_print(const struct fa *self, FILE *out);

// print an automaton (DOT)
void fa_dot_print(const struct fa *self, FILE *out);

// delete a transition
void fa_remove_transition(const struct fa *self, size_t from, char alpha, size_t to);

// delete a state
void fa_remove_state(const struct fa *self, size_t state);

// count transitions
size_t fa_count_transitions(const struct fa *self);

// tells if a automaton is deterministic
bool fa_is_deterministic(const struct fa *self);

//tells if a automaton is complete
bool fa_is_complete(const struct fa *self);

//makes an automaton complete
void fa_make_complete(const struct fa *self);
