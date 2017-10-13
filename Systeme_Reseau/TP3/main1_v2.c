#include <stdio.h>
#include <pthread.h>

struct shared
{
    int somme;
    pthread_mutex_t mut;
};

struct matrice
{
    /* paramètres */
    int nbLigne;
    int nbColonnes;
    int* elements;

    /* contexte partage' */
    struct shared *psh;
};

static void *task_w (void *p)
{
    if (p != NULL)
    {
        struct matrice *p_matrice = p;

        pthread_mutex_lock (&p_matrice->psh->mut);
        {
            int x = p_matrice->psh->somme;
            x++;
            p_matrice->psh->somme = x;
        }
        printf (" data <- %d\n", p_matrice->psh->somme);
        pthread_mutex_unlock (&p_matrice->psh->mut);
    }
    return NULL;
}


int main (void)
{
    pthread_t ta;
    pthread_t tb;

    struct shared sh =
            {
                    .somme = 0,
                    .mut = PTHREAD_MUTEX_INITIALIZER,
            };

    struct matrice mat =
            {
                    .nbLigne = 2,
                    .nbColonnes = 2,
                    .psh = &sh,
            };


    puts ("main init");

    pthread_create (&ta, NULL, task_w, &mat);
    pthread_create (&tb, NULL, task_w, &mat);

    pthread_join (ta, NULL);
    pthread_join (tb, NULL);

    puts ("main end");

    return 0;
}
