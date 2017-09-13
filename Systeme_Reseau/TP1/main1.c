#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main () {

    char *message;

    key_t key; // clé pour la création du segment mémoir partagée
    int shmID; // id du segment mémoir partagée
    char *p; // pointeur sur l'adresse du segment de mémoire partagée
    pid_t pid; // id processus crée

    // définition de la clé
    // key = 1234;
    key = ftok("./", 'h');

    // création du segment mémoire partagée avec les droits rw r r
    if ((shmID = shmget(key, sizeof(char), IPC_CREAT | 0644)) < 0)
    {
        perror("shmget");
        exit (1);
    }

    // affichage du shmID du semgent crée
    printf("shmid segment : %i\n",shmID);

    switch (pid = fork()) 
    {
        case -1 : // erreur
            perror("fork");
            exit (1);
        break;

        case 0 : // fils
            printf("pid fils : %d\n", getpid());
            
            // attache le segment de mémoire partagée
            if ((p = (char *) shmat(shmID, NULL, 0)) == (void*) -1)
            {
                perror("shmat");
                exit(1);
            }

            // donne une valeur
            *message = p;
            *message = '\0';
            strcat(message, "bonjour");
            
            // détache le segment mémoire
            if (shmdt(p) < 0)
            {
                perror("shmdt");
                exit(1);
            }
        break;

        default : // père
            printf("pid pere : %d\n", getpid());
            
            // attache le segment de mémoire partagée
            if ((p = (char *) shmat(shmID, NULL, 0)) == (void*) -1)
            {
                perror("shmat");
                exit(1);
            }

            // on attend pour que le fils est le temps d'écrire le message
            sleep(1);

            // on affiche le message du fils
            printf("%s\n", p);

            // détache le segment mémoire
            if (shmdt(p) < 0)
            {
                perror("shmdt");
                exit(1);
            }
            
            /*if (shmctl(shmID,IPC_RMID,NULL) == -1)
            {
                perror("shmctl") ;
                exit(1) ;
            }*/
        break;
    }

    // Q1, on vérifie que le shmId n'existe plus
    system("ipcs -m");

    // Q2, on identifie le segment et on le supprime
   system("ipcs");
   system("ipcrm -m " + key);
   system("ipcs");

    //Q3, on supprime assurément le segment de mémoire partagée

    return 0;
}