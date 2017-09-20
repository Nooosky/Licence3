#include "fa.h"

// crée un automate
void fa_create(struct fa *self, size_t alpha_count, size_t state_count)
{
    self->alpha_count = alpha_count;
    self->state_count = state_count;

    self->states = (struct state *) malloc(sizeof(struct state) * self->state_count);

    for (int i = 0; i < self->state_count; ++i)
    {
        struct state * new_state = (struct state *) malloc(sizeof(struct state));

        new_state->is_initial = 0;
        new_state->is_final = 0;

        self->states[i] = &new_state;
    }
}

// détruire un automate
void fa_destroy(struct fa *self)
{
  for (int i = 0; i < self->state_count; ++i)
    free(self->states[i]);

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

}

// afficher un automate
void fa_pretty_print(const struct fa *self, FILE *out)
{

}

// affiche en automate en format DOT
void fa_dot_print(const struct fa *self, FILE *out)
{

}
