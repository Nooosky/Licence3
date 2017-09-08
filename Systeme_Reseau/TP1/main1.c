#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main () {

     // défini la structure à partager
    struct Data 
    {
        char* message;
    };

    key_t key; // clé pour la création du segment mémoir partagée
    int shmID; // id du segment mémoir partagée
    struct Data* p; // pointeur sur l'adresse du segment de mémoire partagée
    pid_t pid; // id processus crée

    // définition de la clé
    // key = 1234;
    key = ftok("./", 'h');

    // instancie Data
    struct Data data;

    // création du segment mémorie partagée
    if ((shmID = shmget(key, sizeof(data), IPC_CREAT | 0644)) < 0)
    {
        perror("shmget");
        exit (-1);
    }

    switch (pid = fork()) 
    {
        case -1 : // erreur
            perror("fork");
            exit (-1);
        break;

        case 0 : // fils
            printf("fils : %d\n", getpid());

            sleep(100);
            
            // attache le segment de mémoire partagée
            if ((p = (struct Data *) shmat(shmID, NULL, 0)) == (void*) -1)
            {
                perror("shmat");
                exit(-1);
            }

            printf("%s\n", data.message);

        break;

        default : // père
            printf("pere : %d\n", getpid());
            
            // met une valeur dans message
            p->message = malloc(sizeof(char) * 10);
            p->message = "bonjour";

            sleep(100);

            // détache le segment mémoire
            free( p->message);
            if (shmdt(p) < 0)
            {
                perror("shmdt");
                exit(-1);
            }
            
        break;
    }

    return 0;
}