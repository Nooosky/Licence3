#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h> 

int flag = 1;
void handler(int sig) {flag = 0;}

int main () 
{
    if (signal(SIGUSR1, handler) == SIG_ERR)
    {  
        perror("signal" ); 
        exit(1);
    }

    char *message = (char *) malloc(sizeof(char) * 8);

    key_t key; // clé pour la création du segment mémoir partagée
    int shmID; // id du segment mémoir partagée
    char *p; // pointeur sur l'adresse du segment de mémoire partagée
    pid_t pid; // id processus crée

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

            // on attend un signal du père pour lire le message 
            if (flag)
                pause();
            flag = 1;
            
            // on affiche le message du père
            printf("%s\n", p);
            
            // envoie le signal au pere
            if (kill(getppid(), SIGUSR1)) 
            {
                perror("kill fils"); 
                exit(1); 
            }

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

            // donne une valeur
            message = "bonjour";
            strcat(p, message);

            // envoie le signal au fils
            if (kill(pid, SIGUSR1)) 
            {
                perror("kill pere"); 
                exit(1); 
            }

            // on attend un signal du fils pour continuer
            if (flag)
                pause();
            flag = 1;

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
        break;
    }

    return 0;
}