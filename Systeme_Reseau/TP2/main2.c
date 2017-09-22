#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


void* print_fct(void* ptr);


int main (int argc, char *argv[])
{

  if (argc != 2)
  {
      fprintf(stderr, "USAGE: ./main <compte>\n");
      exit(1);
  }

  int nombre = atoi(argv[1]);


  pthread_t thread1, thread2;

  if(pthread_create(&thread1, NULL, &print_fct, &nombre) == -1)
  {
    perror("pthread_create");
    return EXIT_FAILURE;
  }

  if(pthread_create(&thread2, NULL, &print_fct, &nombre) == -1)
  {
    perror("pthread_create");
    return EXIT_FAILURE;
  }

  if (pthread_join(thread1, NULL) && pthread_join(thread2, NULL))
  {
    perror("pthread_join");
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}


void* print_fct(void* ptr)
{
  int nombre =  *((int*)ptr);
  int i = 1;
  for(i = 1; i <= nombre; ++i)
  {
    printf("%li %d\n", (unsigned long int)pthread_self(), i);
    usleep(500 * 1000);
  }

  pthread_exit(NULL);
}
