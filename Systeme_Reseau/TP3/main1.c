#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


/* macro */


/* prototype */
//calcul la somme des lignes de la matrice
void *calculSomme(void *args);


/* variable */
// matrice
struct matrice
{
  unsigned int nbLigne;
  unsigned int nbColonne;
  int **element;
};

pthread_mutex_t mutex;

struct matrice *matrice = NULL;


/* main */
int main(int argc, char *argv[])
{
  srand(time(NULL)); // seed pour l'aleatoire
  int i = 0, j = 0; // variable d'incrementation pour les for

  // verifie les arguments
  if (argc != 3)
  {
      fprintf(stderr, "USAGE: ./main <ligne> <colonne>\n");
      exit(1);
  }

  // init la matrice
  matrice = (struct matrice *) malloc(sizeof(struct matrice));
  matrice->nbLigne = atoi(argv[1]);
  matrice->nbColonne = atoi(argv[2]);
  matrice->element =  (int**)malloc(matrice->nbLigne * sizeof(int *));
  for(i = 0; i < matrice->nbLigne; ++i)
    matrice->element[i] = (int *)calloc(matrice->nbColonne, sizeof(int));


  pthread_t thread_id[matrice->nbColonne];
  int sommeFinal = 0;


  // remplie la matrice aleatoirement
  for(i = 0; i < matrice->nbLigne; ++i)
    for(j = 0; j < matrice->nbColonne; ++j)
      matrice->element[i][j] = rand()%10;

  // affiche la matrice
  for(i = 0; i < matrice->nbLigne; ++i)
  {
    for(j = 0; j < matrice->nbColonne; ++j)
    {
      printf("%d ",matrice->element[i][j]);
    }
    printf("\n");
  }

  // init le mutex
  if (pthread_mutex_init(&mutex, NULL) != 0)
  {
    perror("pthread_mutex_init");
    exit(1);
  }

  // cree les thread
  for(i = 0; i < matrice->nbColonne; ++i)
      if (pthread_create( &thread_id[i], NULL, calculSomme, &sommeFinal) != 0)
      {
        perror("pthread_create");
        exit(1);
      }

  // attend la fin des thread
  for(i = 0; i < matrice->nbColonne; ++i)
      pthread_join( thread_id[i], NULL);

  // detruit le mutex
  pthread_mutex_destroy(&mutex);

  // affiche la somme final


  free (matrice);
  return 0;
}


void *calculSomme(void *args)
{
    int *argPtr = args;

    int threadindex = *argPtr;

    for (int k = 0; k < 10; ++k) {
        pthread_mutex_lock( &mutex );
        result = result + dimensional_array[threadindex][k];
        pthread_mutex_unlock( &mutex );
    }

    return NULL;
}
