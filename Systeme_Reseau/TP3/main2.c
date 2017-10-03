#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* somme (void* arg);


int main (void)
{
    srand(time(NULL));
    pthread_t fils;

    struct varShare
    {
        pthread_mutex_t mutex;
        int sPair;
        int sImpairs;
    };

    struct varShare *variable = (struct varShare *) malloc(sizeof(struct varShare));
    pthread_mutex_init ( &variable->mutex, NULL);
    variable->sPair = 0;
    variable->sImpairs = 0;

    // create the thread
    if (pthread_create (&fils, NULL, &somme, &variable))
    {
      perror("pthread_create");
      return EXIT_FAILURE;
    }

    // add to sPairs or sImpairs
    // add to sPairs or sImpairs
    int i = 0, nombre = 0;
    for (i = 0; i < 10; ++i)
    {
        pthread_mutex_lock (&variable->mutex); // lock mutex

        nombre = rand()%10;
        if (nombre % 2 == 0)
          variable->sPair += nombre;
        else
          variable->sImpairs += nombre;
        pthread_mutex_unlock (&variable->mutex); // unlock mutex
        sleep (1);
    }

    // wait end of thread
    if(pthread_join (fils, NULL))
    {
      perror("pthread_join");
      return EXIT_FAILURE;
    }

    return 0;
}


void* somme (void* arg)
{
    // add to sPairs or sImpairs
    int i = 0, nombre = 0;
    for (i = 0; i < 10; ++i)
    {
        pthread_mutex_lock (&((struct varShare *)arg)->mutex); // lock mutex

        nombre = rand()%10;
        if (nombre % 2 == 0)
          ((struct varShare *)arg)->sPair += nombre;
        else
          ((struct varShare *)arg)->sImpairs += nombre;

        pthread_mutex_unlock (&((struct varShare *)arg)->mutex); // unlock mutex
        sleep (1);
    }

    // end of thread
    pthread_exit(NULL);
}
