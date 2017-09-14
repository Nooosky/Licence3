// crée un automate
void fa_create(struct fa *self, size_t alpha_count, size_t state_count);

// détruire un automate
void fa_destroy(struct fa *self);

// rentre un état initial
void fa_set_state_initial(struct fa *self, size_t state);

// rendre un état final
void fa_set_state_final(struct fa *self, size_t state);

// ajouter un transition à l'automate
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to);

// afficher un automate
void fa_pretty_print(const struct fa *self, FILE *out);

// affiche en automate en format DOT
void fa_dot_print(const struct fa *self, FILE *out);