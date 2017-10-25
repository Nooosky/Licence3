#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>


int main (int argc, char *argv[]) 
{

    if (argc > 2)
    {
        fprintf(stderr, "USAGE: ./main3 [<shmID>]\n");
        exit(1);
    }

    printf("pid : %d\n", getpid());

    char *message = (char *) malloc(sizeof(char) * 15);
    
    key_t key; // clé pour la création du segment mémoir partagée
    int shmID; // id du segment mémoir partagée
    char *p; // pointeur sur l'adresse du segment de mémoire partagée

    printf("%d\n", argc); 
    if (argc == 2) // 1 argument 
    {
        printf("processus 1 \n");


        shmID = atoi(argv[1]);
        // affichage du shmID du semgent
        printf("shmid segment : %i\n",shmID);

        // attache le segment de mémoire partagée
        if ((p = (char *) shmat(shmID, NULL, 0)) == (void*) -1)
        {
            perror("shmat");
            exit(1);
        }

        // on affiche le message
        printf("%s\n", p);

        // donne une valeur
        message = "Bonjour ";
        strcat(p, message);

        // détache le segment mémoire
        if (shmdt(p) < 0)
        {
            perror("shmdt");
            exit(1);
        }
    }
    else // 0 argument
    {
        printf("processus 2 \n");
                
        // définition de la clé
        // key = 1234;
        key = ftok("./", 'h');

        // création du segment mémoire partagée avec les droits rw r r
        if ((shmID = shmget(key, sizeof(message), IPC_CREAT | 0644)) < 0)
        {
            perror("shmget");
            exit (1);
        }
    
        // affichage du shmID du semgent crée
        printf("shmid segment : %i\n",shmID);


        // attache le segment de mémoire partagée
        if ((p = (char *) shmat(shmID, NULL, 0)) == (void*) -1)
        {
            perror("shmat");
            exit(1);
        }

        // donne une valeur
        message = "John";
        strcat(p, message);

        // temporisation clavier
        printf("temporisation : recevoir message  \n");
        getchar();
        
        // on affiche le message
        printf("%s\n", p);

        // détache le segment mémoire
        if (shmdt(p) < 0)
        {
            perror("shmdt");
            exit(1);
        }
        
        // supprime le segment de mémoire partagée
        if (shmctl(shmID,IPC_RMID,NULL) == -1)
        {
            perror("shmctl") ;
            exit(1) ;
        }
    }

    return 0;
}
