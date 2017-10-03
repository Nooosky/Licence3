#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define NTHREADS 2
void *CalculateSum(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

#define N 10
#define M 10

int dimensional_array[N][M];

int result = 0;

void *CalculateSum(void *args)
{
    int *argPtr = args;

    int threadindex = *argPtr;

    for (int k = 0; k < 10; ++k) {
        pthread_mutex_lock( &mutex1 );
        result = result + dimensional_array[threadindex][k];
        pthread_mutex_unlock( &mutex1 );
    }
}


int main()
{
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
