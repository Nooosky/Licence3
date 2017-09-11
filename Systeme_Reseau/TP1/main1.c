#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main () {

     // défini la structure à partager
    char *message;
   

    key_t key; // clé pour la création du segment mémoir partagée
    int shmID; // id du segment mémoir partagée
    char *p; // pointeur sur l'adresse du segment de mémoire partagée
    pid_t pid; // id processus crée

    // définition de la clé
    // key = 1234;
    key = ftok("./", 'h');

    // création du segment mémoire partagée
    if ((shmID = shmget(key, sizeof(message), IPC_CREAT | 0644)) < 0)
    {
        perror("shmget");
        exit (1);
    }

    switch (pid = fork()) 
    {
        case -1 : // erreur
            perror("fork");
            exit (1);
        break;

        case 0 : // fils
            printf("fils : %d\n", getpid());
            
            // attache le segment de mémoire partagée
            if ((p = (char *) shmat(shmID, NULL, 0)) == (void*) -1)
            {
                perror("shmat");
                exit(1);
            }

            sleep(1);

            printf("%s\n", p);

        break;

        default : // père
            printf("pere : %d\n", getpid());
            
            // alloue de la mémoire et met une valeur dans message
            //p = malloc(sizeof(char) * 7);
            //p = "bonjour";
            sleep(1);
            *message = p;
            *message = '\0';
            strcat(message, "Hello from the child");

            sleep(1);

            // libère la mémoire
            //free(p);

            // détache le segment mémoire
            if (shmdt(p) < 0)
            {
                perror("shmdt");
                exit(1);
            }
            
        break;
    }

    return 0;
}