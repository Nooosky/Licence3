#include "fa.h"

// crée un automate
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

    self->transitions = (struct state_set**) malloc(self->alpha_count*sizeof(struct state_set*));
    for (int i = 0; i < self->alpha_count; i++)
        self->transitions[i] = (struct state_set*) malloc(self->state_count*sizeof(struct state_set));

    for (int j = 0; j < self->alpha_count; ++j) {
        for (int i = 0; i < self->state_count; ++i) {
            self->transitions[j][i] = new_state_set;
            self->transitions[j][i].states = (size_t *) malloc(sizeof(size_t));
        }
    }
}

// détruire un automate
void fa_destroy(struct fa *self)
{
  for (int j = 0; j < self->alpha_count; ++j)
  {
      for (int i = 0; i < self->state_count; ++i)
        free(self->transitions[j][i].states);

      free(self->transitions[j]);
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
      perror("fa_set_state_initial");
}

//make a state final
void fa_set_state_final(struct fa *self, size_t state)
{
    if(-1 < (int)state && state < self->state_count)
      self->states[state].is_final = 1;
    else
      perror("fa_set_state_final");
}

// ajouter un transition à l'automate
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to)
{
  if(-1 < (int)from && from < self->state_count)
  {
    if(-1 < ((int) alpha - 97) && ((int) alpha - 97) < self->alpha_count)
    {
      if(-1 < (int)to && to < self->state_count)
      {
        int int_alpha = (int) alpha - 97;
        ++ self->transitions[int_alpha][from].size;
        ++ self->transitions[int_alpha][from].capacity;
        self->transitions[int_alpha][from].states[self->transitions[int_alpha][from].size - 1] = to;
      }
      else
        perror("fa_add_transition, to");
    }
    else
      perror("fa_add_transition, alpha");
  }
  else
    perror("fa_add_transition, from");
}

// afficher un automate
void fa_pretty_print(const struct fa *self, FILE *out)
{
  out = fopen("txt/automaton.txt", "w+");
  if(out == NULL)
  {
    perror("fopen");
    exit (1);
  }

  fprintf(out, "Initial states:\n\t");
  for (int i = 0; i < self->state_count; ++i)
    if (self->states[i].is_initial)
      fprintf(out, "%d ", i);

  fprintf(out, "\nFinal states:\n\t");
  for (int i = 0; i < self->state_count; ++i)
    if (self->states[i].is_final)
      fprintf(out, "%d ", i);

 fprintf(out, "\nTransitions:\n");
    for (int i = 0; i < self->state_count; ++i)
    {
        fprintf(out, "\tFor state %d:\n", i);
        for (int j = 0; j < self->alpha_count; ++j)
        {
            fprintf(out, "\t\tFor letter %c: ", 97 + j);
            for (int k = 0; k < self->transitions[j][i].size; ++k)
            {
                fprintf(out, "%d ", (int)self->transitions[j][i].states[k]);
            }
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
    perror("fopen");
    exit (1);
  }

  fprintf(out, "digraph finite_state_machine {\n");
  fprintf(out, "\trankdir=LR;\n");
  fprintf(out, "\tsize=\"8,5\";\n");
  fprintf(out, "\tnode [shape = doublecircle];");
  for (int i = 0; i < self->state_count; ++i)
    if (self->states[i].is_final)
      fprintf(out, " %d", i);
  fprintf(out, ";\n");
  fprintf(out, "\tnode [shape = circle];\n");
   for (int i = 0; i < self->state_count; ++i)
       for (int j = 0; j < self->alpha_count; ++j)
           for (int k = 0; k < self->transitions[j][i].size; ++k)
               fprintf(out, "\t%d -> %d [ label = \"%c\" ];\n", i, (int)self->transitions[j][i].states[k], 97 + j);
   fprintf(out, "}");

  fclose(out);
}

// delete a transition
void fa_remove_transition(const struct fa *self, size_t from, char alpha, size_t to)
{
  if(-1 < (int)from && from < self->state_count)
  {
    if(-1 < ((int) alpha - 97) && ((int) alpha - 97) < self->alpha_count)
    {
      if(-1 < (int)to && to < self->state_count)
      {
        int int_alpha = (int) alpha - 97;
        if (self->transitions[int_alpha][from].states[self->transitions[int_alpha][from].size-1] == to)
        {
          self->transitions[int_alpha][from].states[self->transitions[int_alpha][from].size-1] = 0;
          -- self->transitions[int_alpha][from].size;
          -- self->transitions[int_alpha][from].capacity;
        }
        else
          perror("fa_remove_transition");
      }
      else
        perror("fa_add_transition, to");
    }
    else
      perror("fa_add_transition, alpha");
  }
  else
    perror("fa_add_transition, from");
}

// delete a state
void fa_remove_state(const struct fa *self, size_t state)
{

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
void graph_destroy(struct graph *self)
{

}

// make in depth
void graph_depth_first_search(const struct graph *self, size_t state, bool *visited)
{

}

// find a path between from and to
bool graph_has_path(const struct graph *self, size_t from, size_t to)
{

}

// tells if graph is empty
bool fa_is_language_empty(struct fa *self)
{

}
