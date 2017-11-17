#include "fa.h"

// crée un automate
void fa_create(struct fa *self, size_t alpha_count, size_t state_count)
{
  if(-1 < (int)alpha_count && (int)alpha_count <= 26)
  {
    if(-1 < (int)state_count)
    {
      self->alpha_count = alpha_count;
      self->state_count = state_count;

      self->states = (struct state *) malloc(self->state_count * sizeof(struct state));
      for (int i = 0; i < self->state_count; ++i)
      {
          self->states[i].is_initial = 0;
          self->states[i].is_final = 0;
      }

      self->transitions = (struct state_set**) malloc(self->alpha_count * sizeof(struct state_set*));
      for (int i = 0; i < self->alpha_count; i++)
          self->transitions[i] = (struct state_set*) malloc(self-> state_count * sizeof(struct state_set));


      for (int i = 0; i < self->alpha_count; ++i)
          for (int j = 0; j < self->state_count; ++j)
          {
              self->transitions[i][j].size = 0;
              self->transitions[i][j].states = NULL;
          }
    }
    else
    {
      perror("ERROR : fa_create() -> state_count");
      exit (1);
    }
  }
  else
  {
    perror("ERROR : fa_create() -> alpha_count");
    exit (1);
  }
}

// détruire un automate
void fa_destroy(struct fa *self)
{
  for (int i = 0; i < self->alpha_count; ++i)
  {
      for (int j = 0; j < self->state_count; ++j)
        free(self->transitions[i][j].states);

      free(self->transitions[i]);
  }
  free(self->transitions);
  free(self->states);
  free(self);
}

//make a state initial
void fa_set_state_initial(struct fa *self, size_t state)
{
    if(-1 < (int)state && state < self->state_count)
      self->states[state].is_initial = 1;
    else
      perror("ERROR : fa_set_state_initial() -> state");
}

//make a state final
void fa_set_state_final(struct fa *self, size_t state)
{
    if(-1 < (int)state && state < self->state_count)
      self->states[state].is_final = 1;
    else
      perror("ERROR : fa_set_state_final() -> state");
}

// ajouter un transition à l'automate
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to)
{
  if(-1 < (int)from && from < self->state_count)
  {
    if(-1 < (alpha - 'a') && (alpha - 'a') < self->alpha_count)
    {
      if(-1 < (int)to && to < self->state_count)
      {
        for (int i = 0; i < self->transitions[alpha - 'a'][from].size; ++i)
            if(self->transitions[alpha - 'a'][from].states[i] == to)
              return;

        ++ self->transitions[alpha - 'a'][from].size;
        self->transitions[alpha - 'a'][from].states = realloc(self->transitions[alpha - 'a'][from].states, self->transitions[alpha - 'a'][from].size * sizeof(size_t));
        self->transitions[alpha - 'a'][from].states[self->transitions[alpha - 'a'][from].size - 1] = to;
      }
      else
        perror("ERROR : fa_add_transition() -> to");

    }
    else
      perror("ERROR : fa_add_transition() -> alpha");
  }
  else
    perror("ERROR : fa_add_transition() -> from");

}

// afficher un automate
void fa_pretty_print(const struct fa *self, FILE *out)
{
  out = fopen("txt/automaton.txt", "w+");
  if(out == NULL)
  {
    perror("ERROR : fa_pretty_print() -> fopen()");
    exit (1);
  }

  fprintf(out, "Initial states:\n\t");
  for (int i = 0; i < (int)self->state_count; ++i)
    if (self->states[i].is_initial)
      fprintf(out, "%d ", i);

  fprintf(out, "\nFinal states:\n\t");
  for (int i = 0; i < (int)self->state_count; ++i)
    if (self->states[i].is_final)
      fprintf(out, "%d ", i);

  fprintf(out, "\nTransitions:\n");
  for (int i = 0; i < (int)self->state_count; ++i)
  {
      fprintf(out, "\tFor state %d:\n", i);
      for (int j = 0; j < (int)self->alpha_count; ++j)
      {
          fprintf(out, "\t\tFor letter %c: ", 'a' + j);
          for (int k = 0; k < (int)self->transitions[j][i].size; ++k)
              fprintf(out, "%d ", (int)self->transitions[j][i].states[k]);
          fprintf(out, "\n");
      }
  }

  fclose(out);
}

// affiche en automate en format DOT
void fa_dot_print(const struct fa *self, FILE *out)
{
  out = fopen("img/automaton.dot", "w+");
  if(out == NULL)
  {
    perror("ERROR : fa_dot_print() -> fopen()");
    exit (1);
  }

  fprintf(out, "digraph finite_state_machine {\n");
  fprintf(out, "\trankdir=LR;\n");
  fprintf(out, "\tsize=\"8,5\";\n");
  fprintf(out, "\tnode [shape = doublecircle];");
  for (int i = 0; i < (int)self->state_count; ++i)
    if (self->states[i].is_final)
      fprintf(out, " %d", i);
  fprintf(out, ";\n");
  fprintf(out, "\tnode [shape = circle];\n");
   for (int i = 0; i < (int)self->state_count; ++i)
       for (int j = 0; j < (int)self->alpha_count; ++j)
           for (int k = 0; k < (int)self->transitions[j][i].size; ++k)
               fprintf(out, "\t%d -> %d [ label = \"%c\" ];\n", i, (int)self->transitions[j][i].states[k], 'a' + j);
   fprintf(out, "}");

  fclose(out);
}

// delete a transition
void fa_remove_transition(const struct fa *self, size_t from, char alpha, size_t to)
{
  if(-1 < (int)from && from < self->state_count)
  {
    if(-1 < (alpha - 'a') && (alpha - 'a') < (int)self->alpha_count)
    {
      if(-1 < (int)to && to < self->state_count)
      {
        for (int i = 0; i < (int)self->transitions[alpha - 'a'][from].size; ++i)
          if (self->transitions[alpha - 'a'][from].states[i] == to)
          {
            -- self->transitions[alpha - 'a'][from].size;
            for (int j = i; j < (int)self->transitions[alpha - 'a'][from].size; ++j)
              self->transitions[alpha - 'a'][from].states[j] = self->transitions[alpha - 'a'][from].states[j+1];

            self->transitions[alpha - 'a'][from].states = realloc(self->transitions[alpha - 'a'][from].states, self->transitions[alpha - 'a'][from].size * sizeof(size_t));
            return;
          }
      }
      else
        perror("ERROR : fa_remove_transition() -> to");
    }
    else
      perror("ERROR : fa_remove_transition() -> alpha");
  }
  else
    perror("ERROR : fa_remove_transition() -> from");
}

// delete a state
void fa_remove_state(struct fa *self, size_t state)
{
  if(-1 < (int)state && state < self->state_count)
  {

    for (int i = state; i < (int)self->state_count - 1; ++i)
    {
      self->states[i].is_final = self->states[i+1].is_final;
      self->states[i].is_initial = self->states[i+1].is_initial;
    }

    for (int i = 0; i < (int)state; ++i)
      for (int j = 0; j < (int)self->alpha_count; ++j)
        fa_remove_transition(self, i, (char)('a' + j), state);

    for(int i = 0; i < (int) self->state_count; ++i)
      for(int j = 0; j < (int) self->alpha_count; ++j)
        for(int k = 0; k < (int) self->transitions[j][i].size; ++k)
        {
          if (self->transitions[j][i].states[k] > state)
          --self->transitions[j][i].states[k];
        }

    for(int i = state; i < (int) self->state_count - 1; ++i)
      for(int j = 0; j < (int) self->alpha_count; ++j)
      {
        self->transitions[j][i].size = self->transitions[j][i + 1].size;
        self->transitions[j][i].states = realloc(self->transitions[j][i].states, self->transitions[j][i].size * sizeof(size_t));
        for(int k = 0; k < (int) self->transitions[j][i].size; ++k)
        {
          self->transitions[j][i].states[k] = self->transitions[j][i + 1].states[k];
        }
      }

    for(int i = 0; i < (int) self->alpha_count; ++i)
      free(self->transitions[i][self->state_count - 1].states);

    --self->state_count;
    self->states = realloc(self->states, sizeof(size_t) * self->state_count);
  }
  else
    perror("ERROR : fa_remove_state() -> state");
}

//count transition in an automaton
size_t fa_count_transitions(const struct fa *self)
{
    size_t nbTransitions = 0;

    for (int i = 0; i < self->state_count; ++i)
        for (int j = 0; j < self->alpha_count; ++j)
            if(self->transitions[j][i].size > 0)
                nbTransitions += self->transitions[j][i].size;

    return nbTransitions;
}

//check if an automaton is deterministic
bool fa_is_deterministic(const struct fa *self)
{
    size_t nbStatesInitiaux = 0;
    for (int i = 0; i < self->state_count; ++i)
        if (self->states[i].is_initial == 1)
          ++nbStatesInitiaux;

    if (nbStatesInitiaux != 1)
      return false;

    for (int i = 0; i < self->state_count; ++i)
        for (int j = 0; j < self->alpha_count; ++j)
          if(self->transitions[j][i].size > 1)
              return false;

    return true;
}

//tells if a automaton is complete
bool fa_is_complete(const struct fa *self)
{
  for (int i = 0; i < self->state_count; ++i)
    for (int j = 0; j < self->alpha_count; ++j)
      if(self->transitions[j][i].size < 1)
        return false;

  return true;
}

//makes an automaton complete
void fa_make_complete(struct fa *self)
{
  for (int i = 0; i < self->state_count; ++i)
    for (int j = 0; j < self->alpha_count; ++j)
      if(self->transitions[j][i].size < 1)
      {
        // add new state
        self->state_count++;
        self->states = realloc(self->states, self->state_count * sizeof(struct state));
        self->states[self->state_count - 1].is_initial = 0;
        self->states[self->state_count - 1].is_final = 0;
        struct state_set new_state_set = {.capacity = 0, .size = 0};

        for (int i = 0; i < self->alpha_count; i++)
          self->transitions[i] = realloc(self->transitions[i], self->state_count*sizeof(struct state_set));

        for (int j = 0; j < self->alpha_count; ++j)
        {
          self->transitions[j][self->state_count - 1] = new_state_set;
          self->transitions[j][self->state_count - 1].states = (size_t *) malloc(sizeof(size_t));
        }

        // add transition to new state
        fa_add_transition(self, i, (char)(j + 97), self->state_count - 1);

        //add all transitions from new state to new state
        for (int k = 0; k < self->alpha_count; ++k)
          fa_add_transition(self, self->state_count - 1, (char)(k + 97), self->state_count - 1);
      }
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

// deletion a graph
void graph_destroy(struct graph *self){
    for (int i = 0; i < self->node_count; ++i) {
        free(self->nodes[i].adjacent_nodes);
    }
    free(self->nodes);
    free(self);
}

// make in depth
void graph_depth_first_search(const struct graph *self, size_t state, bool *visited){
    visited[state] = true;
    for (int i = 0; i < self->nodes[state].nb_adjacent; ++i) {
        if(visited[self->nodes[state].adjacent_nodes[i].number] == false){
            graph_depth_first_search(self, self->nodes[state].adjacent_nodes[i].number, visited);
        }
    }
}

//tells if a path exists in the graph between two states
bool graph_has_path(const struct graph *self, size_t from, size_t to){
    bool *visited = malloc(self->node_count * sizeof(bool));
    graph_depth_first_search(self, from, visited);
    return visited[to];
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
void fa_create_product(struct fa *self, const struct fa *lhs, const struct fa *rhs){

    fa_create(self, ((lhs->alpha_count + rhs->alpha_count)/2), rhs->state_count*lhs->state_count);
    for (int i = 0; i < lhs->state_count; ++i) {
        for (int j = 0; j < rhs->state_count; ++j) {
            if(lhs->states[i].is_initial && rhs->states[j].is_initial){
                fa_set_state_initial(self, (i * rhs->state_count + j));
            }
            if(lhs->states[i].is_final && rhs->states[j].is_final){
                fa_set_state_final(self, (i * rhs->state_count + j));
            }
        }
    }

    for (int k = 0; k < lhs->alpha_count; ++k) {
        for (int i = 0; i < lhs->state_count; ++i) {
            for (int j = 0; j < rhs->alpha_count; ++j) {
                for (int l = 0; l < rhs->state_count; ++l) {
                    if (k == j){
                        for (int m = 0; m < lhs->transitions[k][i].size; ++m) {
                            for (int n = 0; n < rhs->transitions[j][l].size; ++n) {
                                fa_add_transition(self, (i * rhs->state_count + l), (char) (97 + k),
                                (lhs->transitions[k][i].states[m] * rhs->state_count + rhs->transitions[j][l].states[n]));
                            }
                        }
                    }
                }
            }
        }
    }
}
