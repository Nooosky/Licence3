/*
tp3 exercice 1, realise par Jeremy Roussey et Bastien Chanez
Ce programme creer un matrice d'entier de ligne * colonne donne par l'utilisateur
La remplie aleatoirement et calcul la somme des elements de la matrice par passage de
parametre avec des threads en synchronisant avec des mutex
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>


/* macro */


/* prototype */
//verifie le nombre d'arguement passe dans le programme
void testArgument(int argc);
//initialise la matrice
void initMatrice(unsigned int ligne, unsigned int colonne);
//remplie aleatoriement la matrice
void fillMatrice();
//affiche la matrice
void printMatrice();
//calcul la somme des lignes de la matrice
void *calculSomme(void *args);
//affiche le somme des elements de la matrice
void printSommeTotal();


/* variable */
// matrice
struct matrice
{
  unsigned int count_ligne;
  unsigned int count_colonne;
  int **element;
};

pthread_mutex_t mutex;

struct matrice *matrice = NULL;


/* main */
int main(int argc, char *argv[])
{
  srand(time(NULL));

	testArgument(argc);
  unsigned int ligne =  atoi(argv[1]); unsigned int colonne = atoi(argv[2]);

  pthread_t thread_id[colonne];
  int sommeFinal = 0;
  initMatrice(ligne, colonne);
  fillMatrice();

  // init le mutex
  if (pthread_mutex_init(&mutex, NULL) != 0)
  {
    perror("pthread_mutex_init");
    exit(1);
  }

  // cree les thread
  int i = 0;
  for(i = 0; i < colonne; ++i)
      if (pthread_create( &thread_id[i], NULL, calculSomme, &sommeFinal) != 0)
      {
        perror("pthread_create");
        exit(1);
      }

  // attend la fin des thread
  for(i = 0; i < colonne; ++i)
      pthread_join( thread_id[i], NULL);

  // detruit le mutex
  pthread_mutex_destroy(&mutex);

  printSommeTotal();

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

void initMatrice(unsigned int ligne, unsigned int colonne)
{

}

void fillMatrice()
{

}

void printMatrice()
{

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

void printSommeTotal()
{

}
