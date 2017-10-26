#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// automaton
struct state //state structure
{
    bool is_initial;
    bool is_final;
};

struct fa
{
    size_t alpha_count;     //size of the alphabet
    size_t state_count;     //number of states of the automaton

    struct state *states;   //stores the states of the automaton

    struct state_set **transitions;
};

struct state_set
{
    size_t size;
    size_t capacity;
    size_t *states;
};

// graph
struct graph
{
  size_t node_count;
  struct node *nodes;
};

struct node
{
  size_t number;
  size_t nb_adjacent;
  struct node *adjacent_nodes;
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

//reset state of a state
void fa_reset_state_final_or_initial(struct fa *self, size_t state);

// delete a state
void fa_remove_state(const struct fa *self, size_t state);

// count transitions
size_t fa_count_transitions(const struct fa *self);

// tells if a automaton is deterministic
bool fa_is_deterministic(const struct fa *self);

//tells if a automaton is complete
bool fa_is_complete(const struct fa *self);

//makes an automaton complete
void fa_make_complete(struct fa *self);

// make in depth
void graph_depth_first_search(const struct graph *self, size_t state, bool *visited);

// find a path between from and to
bool graph_has_path(const struct graph *self, size_t from, size_t to);

//create graph with automaton
void graph_create_from_fa(struct graph *self, const struct fa *fa, bool inverted);

// deletion a graph
void graph_destroy(struct graph *self);

// tells if graph is empty
bool fa_is_language_empty(struct fa *self);

// remove non accessible states
void fa_remove_non_accessible_states(struct fa *self);

// remove non co accesible states
void fa_remove_non_co_accessible_states(struct fa *self);

// product of tho automaton
void fa_create_product(struct fa *self, const struct fa *lhs, const struct fa *rhs);

// if there is a empty intersection
bool fa_has_empty_intersection(const struct fa *lhs, const struct fa * rhs);

// create a automaton deterministic about automaton non deterministic
void fa_create_deterministic(struct fa *self, const struct fa *nfa);

// if a automaton is included into an other automaton
bool fa_is_included(const struct fa *lhs, const struct fa *rhs);

// if two state are equivalent
bool fa_are_nerode_equivalent(const struct fa *self, size_t s1, size_t s2);

// automaton minimal with nerode
void fa_create_minimal_nerode(struct fa *self, const struct fa *other);

// automaton minimal with moore
void fa_create_minimal_moore(struct fa *self, const struct fa *other);

// delet epsilon of an automaton
void fa_create_without_epsilon(struct fa *self, const struct fa *other);
