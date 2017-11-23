#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



struct state{//state structure
    bool is_initial;
    bool is_final;
} State;

struct fa{
    size_t alpha_count;     //size of the alphabet
    size_t state_count;     //number of states of the automaton

    struct state *states;   //stores the states of the automaton

    struct state_set **transitions;
} Fa;

struct state_set{
    size_t size;
    size_t capacity;
    size_t *states;
}State_set ;


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


void fa_create(struct fa *self, size_t alpha_count, size_t state_count)
{
    self->alpha_count = alpha_count;
    self->state_count = state_count;

    self->states = (struct state *) malloc(sizeof(struct state) * self->state_count);

    for (int i = 0; i < self->state_count; ++i)
    {
        self->states[i].is_initial = 0;
        self->states[i].is_final = 0;
    }

    struct state_set new_state_set = {.capacity = 0, .size = 0};

    self->transitions = (struct state_set**) malloc(alpha_count*sizeof(struct state_set*));
    for (int i = 0; i < alpha_count; i++)
        self->transitions[i] = (struct state_set*) malloc(state_count*sizeof(struct state_set));

    for (int j = 0; j <alpha_count; ++j) {
        for (int i = 0; i < state_count; ++i) {
            self->transitions[j][i] = new_state_set;
            self->transitions[j][i].states = (size_t *) malloc(sizeof(size_t));
        }
    }
}


// détruire un automate
void fa_destroy(struct fa *self)
{
    free(self->states);
    free(self);
}

//make a state initial
void fa_set_state_initial(struct fa *self, size_t state)
{
    if(-1 > state && state < self->state_count)
        self->states[state].is_initial = 1;
    else
        perror("fa_set_state_initial");
}

//make a state final
void fa_set_state_final(struct fa *self, size_t state) {
    if (-1 > state && state < self->state_count)
        self->states[state].is_final = 1;
    else
        perror("fa_set_state_final");
}

void fa_reset_state_final_or_initial(struct fa *self, size_t state) {
    if (-1 > state && state < self->state_count) {
        self->states[state].is_final = 0;
        self->states[state].is_initial = 0;
    } else
        perror("fa_reset_state_final_or_initial");
}

void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to){
    int int_alpha = (int) alpha - 97;
    bool is_already = false;
    if(self->transitions[int_alpha][from].size == 0){
        ++ self->transitions[int_alpha][from].size;
        ++ self->transitions[int_alpha][from].capacity;
        self->transitions[int_alpha][from].states = malloc(sizeof(size_t));
        self->transitions[int_alpha][from].states[0] = to;
    }else{
        for (int i = 0; i < self->transitions[int_alpha][from].size; ++i) {
            if(self->transitions[int_alpha][from].states[i] == to){
                is_already = true;
            }

        }
        if(! is_already){
            ++ self->transitions[int_alpha][from].size;
            ++ self->transitions[int_alpha][from].capacity;
            self->transitions[int_alpha][from].states = realloc(self->transitions[int_alpha][from].states, self->transitions[int_alpha][from].size * sizeof(size_t));
            self->transitions[int_alpha][from].states[self->transitions[int_alpha][from].size - 1] = to;
        }

    }
}

void fa_pretty_print(const struct fa *self, FILE *out)
{
    printf("Initial states:\n\t");
    for (int i = 0; i < self->state_count; ++i)
    {
        if (self->states[i].is_initial)
            printf("%d ", i);
    }

    printf("\nFinal states:\n\t");
    for (int i = 0; i < self->state_count; ++i)
    {
        if (self->states[i].is_final)
            printf("%d ", i);
    }

    printf("\nTransitions:\n");
    for (int i = 0; i < self->state_count; ++i)
    {
        printf("\tFor state %d:\n", i);
        for (int j = 0; j < self->alpha_count; ++j)
        {
            printf("\t\tFor letter %c: ", 97 + j);

            for (int k = 0; k < self->transitions[j][i].size; ++k) {
                printf("%d ", self->transitions[j][i].states[k]);
            }

            printf("\n");
        }
    }


}

size_t fa_count_transitions(const struct fa *self){
    size_t nbTransitions = 0;

    for (int i = 0; i < self->state_count; ++i)
    {
        for (int j = 0; j < self->alpha_count; ++j)
        {
            if(self->transitions[j][i].size > 0){
                nbTransitions = nbTransitions + self->transitions[j][i].size;
            }
        }
    }
    return nbTransitions;
}

// delete a transition
void fa_remove_transition(struct fa *self, size_t from, char alpha, size_t to)
{
    int int_alpha = (int) alpha - 97;
    for (int i = 0; i < self->transitions[int_alpha][from].size; ++i) {
        if (self->transitions[int_alpha][from].states[i] == to){
            for (int j = i; j < self->transitions[int_alpha][from].size; ++j) {
                if (j< self->transitions[int_alpha][from].size-1){
                    self->transitions[int_alpha][from].states[j] = self->transitions[int_alpha][from].states[j + 1];
                }else{
                    self->transitions[int_alpha][from].states[j] = 0;
                }
            }
        }
    }
    -- self->transitions[int_alpha][from].size;
    -- self->transitions[int_alpha][from].capacity;

    self->transitions[int_alpha][from].states = realloc(self->transitions[int_alpha][from].states, self->transitions[int_alpha][from].size * sizeof(size_t));
}

// delete a state
void fa_remove_state(struct fa *self, size_t state)
{
    for (int i = 0; i < self->state_count; ++i) {
        for (int j = 0; j < self->alpha_count; ++j) {
            if(i == state && self->transitions[j][i].size >0){
                for (int k = 0; k < self->transitions[j][i].size; ++k) {
                    fa_remove_transition(self, state, (char) 97 + j, self->transitions[j][i].states[k]);
                }
            } else {
                for (int k = 0; k < self->transitions[j][i].size; ++k) {
                    if(self->transitions[j][i].states[k] == state){
                        fa_remove_transition(self, i, (char) 97 + j, self->transitions[j][i].states[k]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < self->state_count-1; ++i) {
        if (i >= state) {
            fa_reset_state_final_or_initial(self, i);
            if(self->states[i+1].is_initial){
                fa_set_state_initial(self, i);
            }
            if(self->states[i+1].is_final){
                fa_set_state_final(self, i);
            }
            for (int j = 0; j < self->alpha_count; ++j) {
                for (int l = 0; l < self->transitions[j][i].size; ++l) {
                    fa_remove_transition(self, i, (char) 97 + j, self->transitions[j][i].states[l]);
                }
                for (int k = 0; k < self->transitions[j][i+1].size; ++k) {
                    if(self->transitions[j][i+1].states[k] >= state){
                        printf("%d -- ", self->transitions[j][i+1].states[k]);
                        fa_add_transition(self, i, (char) 97 + j, (size_t) (self->transitions[j][i+1].states[k] - 1));
                    }else{
                        fa_add_transition(self, i, (char) 97 + j, self->transitions[j][i+1].states[k]);
                    }
                }
            }
        } else {
            int old_states_size;
            size_t * old_states;
            for (int j = 0; j < self->alpha_count; ++j) {
                old_states_size = self->transitions[j][i].size;
                old_states = malloc(self->transitions[j][i].size * sizeof(size_t));
                for (int k = 0; k < self->transitions[j][i].size; ++k) {
                    old_states[k] = self->transitions[j][i].states[k];
                }
                for (int l = 0; l < old_states_size; ++l) {
                    printf("------- %d-----\n", old_states[l]);
                    if(old_states[l] >= i){
                        fa_remove_transition(self, i, (char) 97 + j, old_states[l]);
                        fa_add_transition(self, i, (char) 97 + j, old_states[l]-1);
                    }
                }
            }
        }

    }

    self->states = realloc(self->states, sizeof(size_t) * self->state_count-1);
    self->state_count --;

}

bool fa_is_deterministic(const struct fa *self){
    for (int i = 0; i < self->state_count; ++i)
    {
        for (int j = 0; j < self->alpha_count; ++j)
        {
            if(self->transitions[j][i].size < 1){
                return false;
            }
        }
    }

    return true;
}


// deletion a graph
void graph_destroy(struct graph *self){
    for (int i = 0; i < self->node_count; ++i) {
        free(self->nodes[i].adjacent_nodes);
    }
    free(self->nodes);
    free(self);
}


void graph_depth_first_search(const struct graph *self, size_t state, bool *visited){
    visited[state] = true;
    for (int i = 0; i < self->nodes[state].nb_adjacent; ++i) {
        if(visited[self->nodes[state].adjacent_nodes[i].number] == false){
            graph_depth_first_search(self, self->nodes[state].adjacent_nodes[i].number, visited);
        }
    }
}

bool graph_has_path(const struct graph *self, size_t from, size_t to){
    bool *visited = malloc(self->node_count * sizeof(bool));
    graph_depth_first_search(self, from, visited);
    return visited[to];
}

//create graph with automaton
void graph_create_from_fa(struct graph *self, const struct fa *fa, bool inverted)
{
    self->node_count = fa->state_count;

    self->nodes = (struct node *) malloc(self->node_count * sizeof(struct node));


    for (int i = 0; i < fa->state_count; ++i)
    {
        self->nodes->number = i;
        self->nodes->nb_adjacent = 0;
        self->nodes->adjacent_nodes = NULL;

        for (int j = 0; j < fa->alpha_count; ++j)
        {
            for (int k = 0; k < fa->transitions[j][i].size; ++k)
            {
                bool trouver = false;
                for(int l = 0; l < self->nodes->nb_adjacent; ++l)
                    if(self->nodes->adjacent_nodes[l].number == (int)fa->transitions[j][i].states[k])
                        trouver = true;

                if (trouver == false)
                {
                    self->nodes->nb_adjacent++;
                    self->nodes->adjacent_nodes = realloc (self->nodes->adjacent_nodes, self->nodes->nb_adjacent * sizeof(struct node));
                    self->nodes->adjacent_nodes[self->nodes->nb_adjacent - 1].number = (int)fa->transitions[j][i].states[k];
                }
            }
        }
    }
}

//tells if the language of a graph is empty
bool fa_is_language_empty(const struct fa *self){
    struct graph *graph1 = (struct graph *) malloc(sizeof(struct graph));
    graph_create_from_fa(graph1, self, false);

    for (int i = 0; i < self->state_count; ++i) {
        for (int j = 0; j < self->state_count; ++j) {
            if(self->states[i].is_initial && self->states[j].is_final){
                if(graph_has_path(graph1, i, j)){
                    return true;
                }
            }
        }
    }
    free(graph1);
    return false;
}


//remove all non accessible states
void fa_remove_non_accessible_states(struct fa *self){
    size_t * states_to_remove = malloc(self->state_count * sizeof(size_t));

    struct graph *graph1 = (struct graph *) malloc(sizeof(struct graph));
    graph_create_from_fa(graph1, self, false);

    for (int i = 0; i < self->state_count; ++i) {
        for (int j = 0; j < self->state_count; ++j) {
            if(self->states[i].is_initial){
                if(!graph_has_path(graph1, i, j)){
                    states_to_remove[j]++;
                }
            }
        }
    }
    for (int k = 0; k < self->state_count; ++k) {
        if(states_to_remove[k] > 0){
            fa_remove_state(self, k);
        }
    }
    free(states_to_remove);
    free(graph1);
}


//remove all non co accessible states
void fa_remove_non_co_accessible_states(struct fa *self){
    size_t * states_to_remove = malloc(self->state_count * sizeof(size_t));

    struct graph *graph1 = (struct graph *) malloc(sizeof(struct graph));
    graph_create_from_fa(graph1, self, false);

    for (int i = 0; i < self->state_count; ++i) {
        for (int j = 0; j < self->state_count; ++j) {
            if(self->states[j].is_final){
                if(!graph_has_path(graph1, i, j)){
                    states_to_remove[i]++;
                }
            }
        }
    }
    for (int k = 0; k < self->state_count; ++k) {
        if(states_to_remove[k] > 0){
            fa_remove_state(self, k);
        }
    }
    free(states_to_remove);
    free(graph1);
}

void fa_create_product(struct fa *self, const struct fa *lhs, const struct fa *rhs)
{

fa_create(self, ((lhs->alpha_count + rhs->alpha_count)/2), rhs->state_count*lhs->state_count);

for (int i = 0; i < lhs->state_count; ++i)
  for (int j = 0; j < rhs->state_count; ++j)
  {
    if(lhs->states[i].is_initial && rhs->states[j].is_initial)
      fa_set_state_initial(self, (i * rhs->state_count + j));
    if(lhs->states[i].is_final && rhs->states[j].is_final)
      fa_set_state_final(self, (i * rhs->state_count + j));
  }


for (int k = 0; k < lhs->alpha_count; ++k)
  for (int i = 0; i < lhs->state_count; ++i)
    for (int j = 0; j < rhs->alpha_count; ++j)
      for (int l = 0; l < rhs->state_count; ++l)
        if (k == j)
          for (int m = 0; m < lhs->transitions[k][i].size; ++m)
            for (int n = 0; n < rhs->transitions[j][l].size; ++n)
                fa_add_transition(self, (i * rhs->state_count + l), (char) ('a' + k), (lhs->transitions[k][i].states[m] * rhs->state_count + rhs->transitions[j][l].states[n]));
}

bool fa_has_empty_intersection(const struct fa *lhs, const struct fa *rhs){
    struct fa *product = (struct fa *) malloc(sizeof(struct fa));
    fa_create_product(product, lhs, rhs);
    bool result = fa_is_language_empty(product);
    free(product);
    return result;
}


//void fa_create_deterministic(struct fa *self, const struct fa *nfa){
void fa_create_deterministic(const struct fa *nfa){

    struct state_set* new_states = malloc(1* sizeof(struct state_set*));
    new_states[0].size = 0;
    new_states[0].capacity = 0;
    new_states[0].states = malloc(nfa->state_count * sizeof(struct state_set));

    struct state_set new_state_set = {.capacity = 0, .size = 0};

    struct state_set **new_transitions = (struct state_set**) malloc(nfa->alpha_count*sizeof(struct state_set*));
    for (int i = 0; i < nfa->alpha_count; i++)
        new_transitions[i] = (struct state_set*) malloc(1*sizeof(struct state_set));

    for (int j = 0; j <nfa->alpha_count; ++j) {
        for (int i = 0; i < 1; ++i) {
            new_transitions[j][i] = new_state_set;
            new_transitions[j][i].states = (size_t *) malloc(sizeof(size_t));
        }
    }

    int index = 0;


    for (int k = 0; k < nfa->state_count; ++k) {
        if(nfa->states[k].is_initial){
            new_states[index].states[new_states[0].size] = k;
            new_states[index].size++;
        }
    }

    for (int i = 0; i < new_states[index].size; ++i) {
            for (int j = 0; j < nfa->alpha_count; ++j)
            {

                for (int k = 0; k < nfa->transitions[j][i].size; ++k) {
                    //new_transitions[j][i].states[new_transitions[j][i].size] = nfa->transitions[j][i].states[k];
                }
            }
    }

    for (int i = 0; i < new_states[index].size; ++i) {
        for (int j = 0; j < nfa->alpha_count; ++j)
        {

            for (int k = 0; k < nfa->transitions[j][i].size; ++k) {
                //new_transitions[j][i].states[new_transitions[j][i].size] = nfa->transitions[j][i].states[k];
                new_transitions[j][i].states = realloc(new_transitions[j][i].states, new_transitions[j][i].size * sizeof(size_t));

                //new_transitions[j][i].states[new_transitions[j][i].size] = nfa->transitions[j][i].states[k];
                //new_transitions[j][i].size++;
            }
        }
    }


    for (int l = 0; l < new_states[index].size; ++l) {
        printf("%d\n", new_states[index].states[l]);
    }


}

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
    fa_add_transition(self, 3, 'b', 1);
    fa_add_transition(self, 4, 'a', 1);
    fa_add_transition(self, 4, 'a', 2);


    // afficher l'automate
    fa_pretty_print(self, NULL);
    fa_remove_state(self, 1);
    fa_pretty_print(self, NULL);

    //destruction of a automaton
    fa_destroy(self);

    struct fa *prod = (struct fa *) malloc(sizeof(struct fa));
    struct fa *g1 = (struct fa *) malloc(sizeof(struct fa));
    struct fa *g2 = (struct fa *) malloc(sizeof(struct fa));

    //Creation of a automaton
    fa_create(g1, 2, 2);
    fa_create(g2, 2, 2);

    //make states initials
    fa_set_state_initial(g1, 0);
    fa_set_state_initial(g2, 0);

    //make states finals
    fa_set_state_final(g1, 1);
    fa_set_state_final(g2, 0);

    fa_add_transition(g1, 0, 'b', 0);
    fa_add_transition(g1, 0, 'a', 1);
    fa_add_transition(g1, 1, 'a', 0);
    fa_add_transition(g1, 1, 'b', 1);

    fa_add_transition(g2, 0, 'a', 0);
    fa_add_transition(g2, 0, 'b', 0);
    fa_add_transition(g2, 0, 'b', 1);
    fa_add_transition(g2, 1, 'a', 1);
    fa_add_transition(g2, 1, 'b', 1);

    fa_create_product(self, g1, g2);
    fa_set_state_initial(self, 3);


    fa_pretty_print(self, NULL);

    fa_create_deterministic(self);



    printf("Hello, World!\n");
    return 0;
}
