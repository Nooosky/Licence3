#include "fa.h"

// crée un automate
int fa_create(struct fa *self, size_t alpha_count, size_t state_count)
{
  if(-1 < (int)alpha_count && (int)alpha_count <= 26)
  {
    if(0 < (int)state_count)
    {
      self->alpha_count = alpha_count;
      self->state_count = state_count;

      self->states = (struct state *) malloc(self->state_count * sizeof(struct state));
      for (size_t i = 0; i < self->state_count; ++i)
      {
        self->states[i].is_initial = 0;
        self->states[i].is_final = 0;
      }

      self->transitions = (struct state_set**) malloc(self->alpha_count * sizeof(struct state_set*));
      for (size_t i = 0; i < self->alpha_count; ++i)
      {
        self->transitions[i] = (struct state_set*) malloc(self-> state_count * sizeof(struct state_set));
        for (size_t j = 0; j < self->state_count; ++j)
        {
          self->transitions[i][j].size = 0;
          self->transitions[i][j].states = NULL;
        }
      }
    }
    else
    {
      //perror("ERROR : fa_create() -> state_count");
      return -1;
    }
  }
  else
  {
    //perror("ERROR : fa_create() -> alpha_count");
    return -2;
  }
  return 0;
}

// détruire un automate
int fa_destroy(struct fa *self)
{
  for (size_t i = 0; i < self->alpha_count; ++i)
  {
    for (size_t j = 0; j < self->state_count; ++j)
      free(self->transitions[i][j].states);
    free(self->transitions[i]);
  }
  free(self->transitions);
  free(self->states);
  free(self);
  return 0;
}

//make a state initial
int fa_set_state_initial(struct fa *self, size_t state)
{
  if(-1 < (int) state && state < self->state_count)
  {
    self->states[state].is_initial = 1;
    return 0;
  }else{
    //perror("ERROR : fa_set_state_initial() -> state");
    return -1;
  }
}

//make a state final
int fa_set_state_final(struct fa *self, size_t state)
{
  if(-1 < (int) state && state < self->state_count)
  {
    self->states[state].is_final = 1;
    return 0;
  }else{
    //perror("ERROR : fa_set_state_final() -> state");
    return -1;
  }
}

// ajouter un transition à l'automate
int fa_add_transition(struct fa *self, size_t from, char alpha, size_t to)
{
  if(-1 < (int)from && from < self->state_count)
  {
    if(-1 < (alpha - 'a') && (size_t)(alpha - 'a') < self->alpha_count)
    {
      if(-1 < (int)to && to < self->state_count)
      {
        for (size_t i = 0; i < self->transitions[alpha - 'a'][from].size; ++i)
            if(self->transitions[alpha - 'a'][from].states[i] == to)
              return 1;

        ++ self->transitions[alpha - 'a'][from].size;
        self->transitions[alpha - 'a'][from].states = realloc(self->transitions[alpha - 'a'][from].states, self->transitions[alpha - 'a'][from].size * sizeof(size_t));
        self->transitions[alpha - 'a'][from].states[self->transitions[alpha - 'a'][from].size - 1] = to;
        return 0;
      }
      else
        return -3;
    }
    else
      return -2;
  }
  else
    return -1;
}

// afficher un automate
int fa_pretty_print(const struct fa *self, FILE *out, char * path)
{
  out = fopen(path, "w+");
  //out = fopen("txt/automaton.txt", "w+");
  if(out == NULL)
  {
    perror("ERROR : fa_pretty_print() -> fopen()");
    return -1;
  }

  fprintf(out, "Initial states:\n\t");
  for (size_t i = 0; i < self->state_count; ++i)
    if (self->states[i].is_initial)
      fprintf(out, "%zu ", i);

  fprintf(out, "\nFinal states:\n\t");
  for (size_t i = 0; i < self->state_count; ++i)
    if (self->states[i].is_final)
      fprintf(out, "%zu ", i);

  fprintf(out, "\nTransitions:\n");
  for (size_t i = 0; i < self->state_count; ++i)
  {
      fprintf(out, "\tFor state %zu:\n", i);
      for (size_t j = 0; j < self->alpha_count; ++j)
      {
          fprintf(out, "\t\tFor letter %c: ", (char)('a' + j));
          for (size_t k = 0; k < self->transitions[j][i].size; ++k)
              fprintf(out, "%zu ", self->transitions[j][i].states[k]);
          fprintf(out, "\n");
      }
  }

  fclose(out);
  return 0;
}

// affiche en automate en format DOT
int fa_dot_print(const struct fa *self, FILE *out)
{
  out = fopen("img/automaton.dot", "w+");
  if(out == NULL)
  {
    perror("ERROR : fa_dot_print() -> fopen()");
    return -1;
  }

  fprintf(out, "digraph finite_state_machine {\n");
  fprintf(out, "\trankdir=LR;\n");
  fprintf(out, "\tsize=\"8,5\";\n");
  fprintf(out, "\tnode [shape = doublecircle];");
  for (size_t i = 0; i < self->state_count; ++i)
    if (self->states[i].is_final)
      fprintf(out, " %zu", i);
  fprintf(out, ";\n");
  fprintf(out, "\tnode [shape = circle];\n");
   for (size_t i = 0; i < self->state_count; ++i)
       for (size_t j = 0; j < self->alpha_count; ++j)
           for (size_t k = 0; k < self->transitions[j][i].size; ++k)
               fprintf(out, "\t%zu -> %zu [ label = \"%c\" ];\n", i, self->transitions[j][i].states[k], (char)('a' + j));
   fprintf(out, "}");

  fclose(out);
  return 0;
}

// delete a transition
int fa_remove_transition(const struct fa *self, size_t from, char alpha, size_t to)
{
  if(-1 < (int)from && from < self->state_count)
  {
    if(-1 < (alpha - 'a') && (alpha - 'a') < (int)self->alpha_count)
    {
      if(-1 < (int)to && to < self->state_count)
      {
        for (size_t i = 0; i < self->transitions[alpha - 'a'][from].size; ++i)
        {
          if (self->transitions[alpha - 'a'][from].states[i] == to)
          {
            -- self->transitions[alpha - 'a'][from].size;
            for (size_t j = i; j < self->transitions[alpha - 'a'][from].size; ++j)
              self->transitions[alpha - 'a'][from].states[j] = self->transitions[alpha - 'a'][from].states[j+1];

            self->transitions[alpha - 'a'][from].states = realloc(self->transitions[alpha - 'a'][from].states, self->transitions[alpha - 'a'][from].size * sizeof(size_t));
            return 0;
          }
        }
        return -4;
      }
      else
        return -3;
    }
    else
      return -2;
  }
  else
    return -1;
}

// delete a state
int fa_remove_state(struct fa *self, size_t state)
{
  if(-1 < (int)state && state < self->state_count)
  {

    for (size_t i = state; i < self->state_count - 1; ++i)
    {
      self->states[i].is_final = self->states[i+1].is_final;
      self->states[i].is_initial = self->states[i+1].is_initial;
    }

    for (size_t i = 0; i < state; ++i)
      for (size_t j = 0; j < self->alpha_count; ++j)
        fa_remove_transition(self, i, (char)('a' + j), state);

    for(size_t i = 0; i < self->state_count; ++i)
      for(size_t j = 0; j < self->alpha_count; ++j)
        for(size_t k = 0; k < self->transitions[j][i].size; ++k)
        {
          if (self->transitions[j][i].states[k] > state)
            --self->transitions[j][i].states[k];
        }

    for(size_t i = state; i < self->state_count - 1; ++i)
      for(size_t j = 0; j < self->alpha_count; ++j)
      {
        self->transitions[j][i].size = self->transitions[j][i + 1].size;
        self->transitions[j][i].states = realloc(self->transitions[j][i].states, self->transitions[j][i].size * sizeof(size_t));
        for(size_t k = 0; k < self->transitions[j][i].size; ++k)
          self->transitions[j][i].states[k] = self->transitions[j][i + 1].states[k];
      }

    for(size_t i = 0; i < self->alpha_count; ++i)
      free(self->transitions[i][self->state_count - 1].states);

    --self->state_count;
    self->states = realloc(self->states, sizeof(size_t) * self->state_count);
    return 0;
  }
  else
    //perror("ERROR : fa_remove_state() -> state");
    return -1;
}

//count transition in an automaton
size_t fa_count_transitions(const struct fa *self)
{
  size_t nbTransitions = 0;
  for (size_t i = 0; i < self->state_count; ++i)
    for (size_t j = 0; j < self->alpha_count; ++j)
      nbTransitions += self->transitions[j][i].size;

  return nbTransitions;
}

//check if an automaton is deterministic
bool fa_is_deterministic(const struct fa *self)
{
  size_t nbStatesInitiaux = 0;
  for (size_t i = 0; i < self->state_count; ++i)
    if (self->states[i].is_initial == 1)
    {
      ++nbStatesInitiaux;
      if (nbStatesInitiaux != 1)
        return false;
    }

  for (size_t i = 0; i < self->state_count; ++i)
    for (size_t j = 0; j < self->alpha_count; ++j)
      if(self->transitions[j][i].size != 1)
        return false;

  return true;
}

//tells if a automaton is complete
bool fa_is_complete(const struct fa *self)
{
  for (size_t i = 0; i < self->state_count; ++i)
    for (size_t j = 0; j < self->alpha_count; ++j)
      if(self->transitions[j][i].size != 1)
        return false;

  return true;
}

//makes an automaton complete
void fa_make_complete(struct fa *self)
{
  if (!fa_is_complete(self))
  {
    bool etatPoubelle = false;
    for (size_t i = 0; i < self->state_count; ++i)
      for (size_t j = 0; j < self->alpha_count; ++j)
        if(self->transitions[j][i].size == 0)
        {
          if (!etatPoubelle)
          {
            self->state_count++;
            self->states = realloc(self->states, self->state_count * sizeof(struct state));
            self->states[self->state_count - 1].is_initial = 0;
            self->states[self->state_count - 1].is_final = 0;

            for (size_t k = 0; k < self->alpha_count; ++k)
            {
              self->transitions[k] = realloc(self->transitions[k], self->state_count*sizeof(struct state_set));
              self->transitions[k][self->state_count - 1].size = 1;
              self->transitions[k][self->state_count - 1].states = (size_t *) malloc(sizeof(size_t));
              self->transitions[k][self->state_count - 1].states[0] = self->state_count - 1;
            }

            etatPoubelle = true;
          }

          fa_add_transition(self, i, (char)(j + 'a'), self->state_count - 1);
        }
  }
}

//create graph with automaton
void graph_create_from_fa(struct graph *self, const struct fa *fa, bool inverted)
{
  self->node_count = fa->state_count;
  self->nodes = (struct node *) malloc(self->node_count * sizeof(struct node));

  for (size_t i = 0; i < fa->state_count; ++i)
  {
    self->nodes[i].number = i;
    self->nodes[i].nb_adjacent = 0;
    self->nodes[i].adjacent_nodes = NULL;
  }

  if (!inverted)
    for (size_t i = 0; i < fa->state_count; ++i)
    {
      size_t valeur = 0;
      for (size_t j = 0; j < fa->alpha_count; ++j)
      {
        self->nodes[i].nb_adjacent += fa->transitions[j][i].size;
        self->nodes[i].adjacent_nodes = realloc(self->nodes[i].adjacent_nodes, self->nodes[i].nb_adjacent * sizeof(struct node));
        for (size_t k = valeur; k < self->nodes[i].nb_adjacent; ++k)
          self->nodes[i].adjacent_nodes[k].number = fa->transitions[j][i].states[k - valeur];
        valeur = fa->transitions[j][i].size;
      }
    }
  else if (inverted)
    for (size_t i = 0; i < fa->state_count; ++i)
      for (size_t j = 0; j < fa->alpha_count; ++j)
        for (size_t k = 0; k < fa->transitions[j][i].size; ++k)
        {
          bool arc = false;
          for (size_t l = 0; l < self->nodes[fa->transitions[j][i].states[k]].nb_adjacent; ++l)
            if(self->nodes[fa->transitions[j][i].states[k]].adjacent_nodes[l].number == i)
            {
              arc = true;
              break;
            }

          if (!arc)
          {
            ++self->nodes[fa->transitions[j][i].states[k]].nb_adjacent;
            self->nodes[fa->transitions[j][i].states[k]].adjacent_nodes = realloc(self->nodes[fa->transitions[j][i].states[k]].adjacent_nodes, self->nodes[fa->transitions[j][i].states[k]].nb_adjacent * sizeof(struct node));
            self->nodes[fa->transitions[j][i].states[k]].adjacent_nodes[self->nodes[fa->transitions[j][i].states[k]].nb_adjacent - 1].number = i;
          }
        }
}

// deletion a graph
void graph_destroy(struct graph *self)
{
    for (size_t i = 0; i < self->node_count; ++i)
        free(self->nodes[i].adjacent_nodes);
    free(self->nodes);
    free(self);
}

// make in depth
int graph_depth_first_search(const struct graph *self, size_t state, bool *visited)
{
  if (state < self->node_count)
  {
      visited[state] = true;
      for (size_t i = 0; i < self->nodes[state].nb_adjacent; ++i)
        if(visited[self->nodes[state].adjacent_nodes[i].number] == false)
          graph_depth_first_search(self, self->nodes[state].adjacent_nodes[i].number, visited);

      return 0;
    }
    else
      return -1;
}

//tells if a path exists in the graph between two states
bool graph_has_path(const struct graph *self, size_t from, size_t to)
{
    if (from < self->node_count)
    {
      if (to < self->node_count)
      {
          bool *visited = malloc(self->node_count * sizeof(bool));
          graph_depth_first_search(self, from, visited);
          return visited[to];
      }
    }
    return false;
}

//tells if the language of a graph is empty
bool fa_is_language_empty(const struct fa *self)
{
    struct graph *graph = (struct graph *) malloc(sizeof(struct graph));
    graph_create_from_fa(graph, self, false);

    for (size_t i = 0; i < self->state_count; ++i)
        for (size_t j = 0; j < self->state_count; ++j)
            if(self->states[i].is_initial && self->states[j].is_final)
                if(graph_has_path(graph, i, j))
                    return false;

    free(graph);
    return true;
}


//remove all non accessible states
void fa_remove_non_accessible_states(struct fa *self)
{
  struct graph *graph = (struct graph *) malloc(sizeof(struct graph));
  graph_create_from_fa(graph, self, false);

  bool tabBool[graph->node_count];
  for (size_t i = 0; i < graph->node_count; ++i)
    tabBool[i] = false;

  graph_depth_first_search(graph, 0, &tabBool);
  for (size_t i = 0; i < graph->node_count; ++i)
    if (!tabBool[i])
      fa_remove_state(self, i);

  free(graph);
}


//remove all non co accessible states
void fa_remove_non_co_accessible_states(struct fa *self)
{
  struct graph *graph = (struct graph *) malloc(sizeof(struct graph));
  graph_create_from_fa(graph, self, false);

  for (size_t i = 0; i < self->state_count; ++i)
    if(self->states[i].is_final)
      for (size_t j = 0; j < self->state_count; ++j)
        if(!graph_has_path(graph, j, i))
          fa_remove_state(self, j);

  free(graph);
}


void fa_create_product(struct fa *self, const struct fa *lhs, const struct fa *rhs)
{
  fa_create(self, (lhs->alpha_count < rhs->alpha_count)?lhs->alpha_count:rhs->alpha_count, rhs->state_count*lhs->state_count);

  for (size_t i = 0; i < lhs->alpha_count; ++i)
    for (size_t j = 0; j < lhs->state_count; ++j)
      for (size_t k = 0; k < rhs->alpha_count; ++k)
        for (size_t l = 0; l < rhs->state_count; ++l)
        {
          if(lhs->states[j].is_initial && rhs->states[l].is_initial)
            fa_set_state_initial(self, (j * rhs->state_count + l));
          if(lhs->states[j].is_final && rhs->states[l].is_final)
            fa_set_state_final(self, (j * rhs->state_count + l));

          if (i == k)
            for (size_t m = 0; m < lhs->transitions[i][j].size; ++m)
              for (size_t n = 0; n < rhs->transitions[k][l].size; ++n)
                  fa_add_transition(self, (j * rhs->state_count + l), (char) ('a' + i), (lhs->transitions[i][j].states[m] * rhs->state_count + rhs->transitions[k][l].states[n]));
        }
}

// tell if the product of two automaton is a empty language
bool fa_has_empty_intersection(const struct fa *lhs, const struct fa *rhs)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create_product(selfFa, lhs,rhs);
  bool variable = fa_is_language_empty(selfFa);
  free (selfFa);
  return variable;
}
