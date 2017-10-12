/*
tp3 exercice 1, realise par Jeremy Roussey et Bastien Chanez
Ce programme creer un matrice d'entier de ligne * colonne donne par l'utilisateur
La remplie aleatoirement et calcul la somme des elements de la matrice par passage de
parametre avec des threads et en synchronisant avec des mutex
*/
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


/* macro */
#define NTHREADS 2
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


/* prototype */
//verifie le nombre d'arguement passe dans le programme
void testArgument(int argc);
//initialise la matrice
void initMatrice(struct matrice *matrice, unsigned int ligne, unsigned int colonne);
//remplie aleatoriement la matrice
void fillMatrice(struct matrice *matrice);
//affiche la matrice
void printMatrice(struct matrice *matrice);
//calcul la somme des lignes de la matrice
void *calculSomme(void *args);
//affiche le somme des elements de la matrice
void printSommeTotal();


// matrice
struct matrice
{
  unsigned int count_ligne;
  unsigned int count_colonne;
  int **element;
};


/* main */
int main(int argc, char *argv[])
{
  srand(time(NULL));
  
	testArgument(argc);

  int totalSomme = 0;
  struct matrice *matrice = NULL;
  initMatrice(matrice, atoi(argv[1]), atoi(argv[2]));
  fillMatrice(matrice);



  pthread_t thread_id[NTHREADS];
  int thread_args[NTHREADS];
  int i, j;

  pthread_mutex_init(&mutex1, NULL);

  for (i = 0; i <= N - 1; i++ )
      for( j = 0; j <= M - 1; j++)
          dimensional_array[i][j] = i*j;

  for(i=0; i < NTHREADS; i++)
  {
      thread_args[i] = i;
      pthread_create( &thread_id[i], NULL, CalculateSum, &thread_args[i]);
  }

  for(j=0; j < NTHREADS; j++)
  {
      pthread_join( thread_id[j], NULL);
  }

  printf("\x1b[32m" "RESULT : %d\n", result);
  printf("\x1b[0m" "");

  return 0;
}


/* definition des fonctions */
void testArgument(int argc)
{
  if (argc != 3)
  {
      fprintf(stderr, "USAGE: ./main <ligne> <colonne>\n");
      exit(1);
  }
}

void initMatrice(struct matrice *matrice, unsigned int ligne, unsigned int colonne)
{

}

void printMatrice(struct matrice *matrice)
{

}

void *calculSomme(void *args)
{
    int *argPtr = args;

    int threadindex = *argPtr;

    for (int k = 0; k < 10; ++k) {
        pthread_mutex_lock( &mutex1 );
        result = result + dimensional_array[threadindex][k];
        pthread_mutex_unlock( &mutex1 );
    }
}

void printSommeTotal()
{

}
