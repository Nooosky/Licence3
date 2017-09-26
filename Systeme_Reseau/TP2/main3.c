#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define LARGEUR_MATRICE 3
#define HAUTEUR_MATRICE 3

struct info
{
  int aleaMin;
  int aleaMax;
  int *ligne;
};

void* initMatrice(void* ptr);

int main (int argc, char *argv[])
{
  srand(time(NULL));

  if (argc != 3)
  {
      fprintf(stderr, "USAGE: ./main <min> <max>\n");
      exit(1);
  }

  int matrice[HAUTEUR_MATRICE][LARGEUR_MATRICE] = {0};

  struct info *info = (struct info *) malloc(sizeof(struct info));
  info->aleaMin = atoi(argv[1]);
  info->aleaMax = atoi(argv[2]);
  info->ligne = (struct int *) malloc(sizeof(struct int) * LARGEUR_MATRICE);
  info->ligne = matrice[0];

  pthread_t *threadInit = (pthread_t *) malloc(sizeof(pthread_t) * HAUTEUR_MATRICE);
  int i = 0;
  for (i = 0; i < HAUTEUR_MATRICE; ++i)
  {
    if(pthread_create(&threadInit[i], NULL, &initMatrice, &info) == -1)
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }
  }

  for (i = 0; i < HAUTEUR_MATRICE; ++i)
  {
    if (pthread_join(threadInit[i], NULL))
    {
      perror("pthread_join");
      return EXIT_FAILURE;
    }
  }

  free(info);

  return EXIT_SUCCESS;
}


void* initMatrice(void* ptr)
{
  struct info info = (struct info*) ptr;
  int min =  ((struct info) ptr).min;
  int max =  ((struct info) ptr).max;
  int matrice = ((struct info) ptr).matrice;

  printf("%d %d", min, max);

  int i = 0, j = 0;
  for(i = 0; i<3; ++i)
    for(j = 0; j<3; ++j)
      matrice[i][j] = (rand() % (max - min + 1)) + min;;

  pthread_exit(NULL);
}
