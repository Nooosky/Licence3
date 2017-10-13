/*
tp3 exercice 1, realise par Jeremy Roussey et Bastien Chanez
Ce programme creer un matrice d'entier de ligne * colonne donne par l'utilisateur
La remplie aleatoirement et calcul la somme des elements de la matrice par passage de
parametre avec des threads en synchronisant avec des mutex
*/

//gcc -Wall -o main main.c -lpthread

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


//shared structure - for the sum
struct shared
{
    int sum;      //sum
    pthread_mutex_t mut;        //mutex for the sum
    int global_index;
};


//matrix structure
struct matrix
{
    /* parameters */
    int nbLines;
    int nbColumns;
    int** elements;

    /* shared context */
    struct shared *psh;
};

//function for the threads
static void *sum_array (void *p);


int main(int argc, char *argv[])
{

    //INITIALIZATION PART ------------

    //random variable seed
    srand(time(NULL));

    //incremental variables for the loops
    int i = 0, j = 0;

    // verifying of the args
    if (argc != 3)
    {
        fprintf(stderr, "USAGE: ./main <lines> <columns>\n");
        exit(1);
    }


    //shared variable structure
    struct shared sh =
            {
                    .sum = 0,
                    .mut = PTHREAD_MUTEX_INITIALIZER,
                    .global_index = 0,
            };

    //matrix structure initialization
    struct matrix mat =
            {
                    .nbLines = atoi(argv[1]),       //first program argument
                    .nbColumns = atoi(argv[2]),    //second program argument
                    .psh = &sh,                     //shared variable structure
            };
    mat.elements =  (int**)malloc(mat.nbLines * sizeof(int *));        //memory allocation for the elements of the matrix
    for(i = 0; i < mat.nbLines; ++i)
        mat.elements[i] = (int *)calloc(mat.nbColumns, sizeof(int));

    //Array of threads
    pthread_t thread_id[mat.nbColumns];

    // Filling the matrix with randoms integers
    for(i = 0; i < mat.nbLines; ++i)
        for(j = 0; j < mat.nbColumns; ++j)
            mat.elements[i][j] = rand()%10;

    // Printing the matrix
    for(i = 0; i < mat.nbLines; ++i)
    {
        for(j = 0; j < mat.nbColumns; ++j)
            printf("%d ",mat.elements[i][j]);
        printf("\n");
    }

    //END OF THE INITIALIZATION PART -------------------

    //Main
    puts ("main init");

    //Creating the threads
    for(i = 0; i < mat.nbLines; ++i)
        if (pthread_create( &thread_id[i], NULL, &sum_array, &mat) != 0)
        {
            perror("pthread_create");
            exit(1);
        }


    // Waiting the end of the threads
    for(i = 0; i < mat.nbLines; ++i)
        pthread_join( thread_id[i], NULL);

    // Printing the final sum
    printf("Final Sum  : %d\n", mat.psh->sum);

    puts ("main end");


    // free memory
    for(i = 0; i < mat.nbLines; ++i)
        free(mat.elements[i]);
    free(mat.elements);

    return 0;
}


//Sum of the array
static void *sum_array(void *p)
{
    if(p != NULL){
        struct matrix *p_matrix = p;

        int local_index, partial_sum = 0;

        do {
            pthread_mutex_lock(&p_matrix->psh->mut);
            local_index = p_matrix->psh->global_index;
            p_matrix->psh->global_index ++;
            pthread_mutex_unlock(&p_matrix->psh->mut);

            if (local_index < p_matrix->nbLines) {
                for (int i = 0; i < p_matrix->nbColumns; ++i) {
                    partial_sum += p_matrix->elements[local_index][i];
                }
            }
        }
        while (local_index < p_matrix->nbLines);

        pthread_mutex_lock(&p_matrix->psh->mut);
        p_matrix->psh->sum += partial_sum;
        pthread_mutex_unlock(&p_matrix->psh->mut);
    }

    return NULL;
}
