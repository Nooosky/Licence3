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
void fa_set_state_final(struct fa *self, size_t state)
{
    if(-1 > state && state < self->state_count)
      self->states[state].is_final = 1;
    else
      perror("fa_set_state_final");
}

// ajouter un transition à l'automate
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to)
{
    int int_alpha = (int) alpha - 97;
    ++ self->transitions[int_alpha][from].size;
    ++ self->transitions[int_alpha][from].capacity;
    self->transitions[int_alpha][from].states = (size_t *) malloc(self->transitions[int_alpha][from].size * sizeof(size_t));
    self->transitions[int_alpha][from].states[self->transitions[int_alpha][from].size - 1] = to;
}

// afficher un automate
void fa_pretty_print(const struct fa *self, FILE *out)
{
  fprint("Initial states:\n\t");
  for (int i = 0; i < self->state_count; ++i)
  {
    if (self->states[i].is_initial)
      fprint("%d ", i);
  }

  fprint("\nFinal states:\n\t");
  for (int i = 0; i < self->state_count; ++i)
  {
    if (self->states[i].is_final)
      fprint("%d ", i);
  }

  fprint("\nTransitions:\n");
  for (int i = 0; i < self->state_count; ++i)
  {
    fprint("\tFor state %d:\n", i);
    for (int j = 0; j < self->state_count; ++j)
    {
      fprint("\t\tFor letter %c:\n", j);
    }
  }
}

// affiche en automate en format DOT
void fa_dot_print(const struct fa *self, FILE *out)
{

}
