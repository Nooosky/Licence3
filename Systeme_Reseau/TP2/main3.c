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
  info->ligne = (int *) malloc(sizeof(int) * LARGEUR_MATRICE);

  pthread_t *threadInit = (pthread_t *) malloc(sizeof(pthread_t) * HAUTEUR_MATRICE);
  int i = 0;
  for (i = 0; i < HAUTEUR_MATRICE; ++i)
  {
    info->ligne = matrice[i];
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
  struct info *info = (struct info *) malloc(sizeof(struct info));
  info = (struct info*) ptr;
  int min =  info->aleaMin;
  int max =  info->aleaMax;
  int *ligne = (int *) malloc(sizeof(int) * LARGEUR_MATRICE);
  ligne = info->ligne;

  printf("%d %d", min, max);

  int i = 0;
  for(i = 0; i<LARGEUR_MATRICE; ++i)
      ligne[i] = (rand() % (max - min + 1)) + min;

  free(ligne);
  free(info);
  pthread_exit(NULL);
}
