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
    for (int j = 0; j < self->state_count; ++j)
    {
      printf("\t\tFor letter %c:\n", j);
    }
  }
}

// affiche en automate en format DOT
void fa_dot_print(const struct fa *self, FILE *out)
{
  out = fopen("/img/automaton.dot", "w+");
  if(out == NULL)
  {
    perror("fopen");
    exit (1);
  }

  fprintf(out, "This is testing for fprintf...\n");
  fputs("This is testing for fputs...\n", out);
  fclose(out);

  /*digraph finite_state_machine {
    rankdir=LR;
    size="8,5";
    node [shape = doublecircle]; 0 3 4 8;
    node [shape = circle];
    0 -> 2 [ label = "b" ];
    0 -> 1 [ label = "a" ];
    1 -> 3 [ label = "a" ];
    1 -> 6 [ label = "b" ];
    2 -> 5 [ label = "a" ];
    2 -> 4 [ label = "a" ];
    5 -> 7 [ label = "b" ];
    5 -> 5 [ label = "a" ];
    6 -> 6 [ label = "b" ];
    6 -> 5 [ label = "a" ];
    7 -> 8 [ label = "b" ];
    7 -> 5 [ label = "a" ];
    9 -> 6 [ label = "b" ];
    9 -> 5 [ label = "a" ];
  }*/
}
