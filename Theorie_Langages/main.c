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
